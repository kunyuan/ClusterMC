module Vertex4
include("global.jl")
using D3Trees

const ChanMap = [I, T, U, S, T, U]
const SymFactor = [1.0, -1.0, 1.0, -0.5, 1.0, -1.0]
const Kpool = Main.pool.K
const Gpool = Main.pool.G
const Verpool = Main.pool.Ver

struct IdxMap
    G0::Int
    Gx::Int
    ver::Int
end

struct Bubble{_Ver4} # template Bubble to avoid mutually recursive struct
    chan::Int
    Lver::_Ver4
    Rver::_Ver4
    map::Vector{IdxMap}

    function Bubble{_Ver4}(ver4::_Ver4, chan::Int, oL::Int) where {_Ver4}
        # printstyled("Bubble creation!\n", color = :red)
        FULL = [I, T, U, S, TC, UC]
        F = [I, U, S, TC, UC]
        VV = [I, T, U, TC, UC]

        Ki = ver4.legKidx
        KinL, KoutL = Kpool[Ki[INL]], Kpool[Ki[OUTL]]
        KinR, KoutR = Kpool[Ki[INR]], Kpool[Ki[OUTR]]
        K0 = getK(ver4.loopidx)
        K0i = add!(Kpool, K0)

        @assert chan == T || chan == U || chan == S "buildBubble only works for T, U, S channel!"
        @assert oL < ver4.loopNum "LVer loopNum must be smaller than the ver4 loopNum"

        lvl = ver4.level + 1
        oR = ver4.loopNum - 1 - oL
        TinLi, TinRi = ver4.Tidx, ver4.Tidx + (oL + 1)
        lloopi, rloopi = ver4.loopidx + 1, ver4.loopidx + 1 + oL
        # println("create left/right vertex4 for channel $chan, loopNum $(ver4.loopNum)")

        if chan == T
            Kxi = add!(Kpool, KoutL .+ K0 .- KinL)
            lKi = (Ki[INL], Ki[OUTL], Kxi, K0i)
            rKi = (K0i, Kxi, Ki[INR], Ki[OUTR])

            Lver = _Ver4(lvl, F, lKi, oL, lloopi, TinLi, LEFT)
            Rver = _Ver4(lvl, FULL, rKi, oR, rloopi, TinRi, RIGHT)
        elseif chan == U
            Kxi = add!(Kpool, KoutR .+ K0 .- KinL)
            lKi = (Ki[INL], Ki[OUTR], Kxi, K0i)
            rKi = (K0i, Kxi, Ki[INR], Ki[OUTL])

            Lver = _Ver4(lvl, F, lKi, oL, lloopi, TinLi, LEFT)
            Rver = _Ver4(lvl, FULL, rKi, oR, rloopi, TinRi, RIGHT)
        elseif chan == S
            Kxi = add!(Kpool, KinL .+ KinR .- K0)
            lKi = (Ki[INL], Kxi, Ki[INR], K0i)
            rKi = (K0i, Ki[OUTL], Kxi, Ki[OUTR])

            Lver = _Ver4(lvl, VV, lKi, oL, lloopi, TinLi, LEFT)
            Rver = _Ver4(lvl, FULL, rKi, oR, rloopi, TinRi, RIGHT)
        end

        # println("para: ", TinLidx, ", ", Lver.Tidx, ", ", ver4.inBox)
        @assert Lver.Tidx == ver4.Tidx "Lver Tidx must be equal to vertex4 Tidx! LoopNum: $(ver4.loopNum), LverLoopNum: $(Lver.loopNum), chan: $chan"

        ############## construct IdxMap ########################################
        map = []
        for (lt, LvT) in enumerate(Lver.T4)
            for (rt, RvT) in enumerate(Rver.T4)
                G0i = add!(Gpool, Main.Green(K0i, (LvT[OUTR], RvT[INL])))
                Gxi, VerTi = (0, 0)

                if chan == T
                    VerTi = add!(ver4.T4, (LvT[INL], LvT[OUTL], RvT[INR], RvT[OUTR]))
                    Gxi = add!(Gpool, Main.Green(Kxi, (RvT[OUTL], LvT[INR])))
                elseif chan == U
                    VerTi = add!(ver4.T4, (LvT[INL], RvT[OUTR], RvT[INR], LvT[OUTL]))
                    Gxi = add!(Gpool, Main.Green(Kxi, (RvT[OUTL], LvT[INR])))
                elseif chan == S
                    # S channel
                    VerTi = add!(ver4.T4, (LvT[INL], RvT[OUTL], LvT[INR], RvT[OUTR]))
                    Gxi = add!(Gpool, Main.Green(Kxi, (LvT[OUTL], RvT[INR])))
                end

                @assert ver4.T4[end][1] == ver4.Tidx "InL Tidx must be the same for all Tpairs in the vertex4"
                push!(map, IdxMap(G0i, Gxi, VerTi))
            end
        end
        return new(chan, Lver, Rver, map)
    end
end

struct Ver4
    level::Int
    chan::Set{Int} # list of channels
    legKidx::Tuple{Int,Int,Int,Int}
    loopNum::Int
    loopidx::Int # initial loop idx
    Tidx::Int # initial Tidx
    side::Int # right side vertex is always a full gamma4

    T4::Vector{Tuple{Int,Int,Int,Int}}
    bubble::Vector{Bubble{Ver4}}

    function Ver4(lvl, chan, legKidx, loopNum, loopidx, tidx, side)
        println(typeof(legKidx))
        ver4 = new(lvl, Set(chan), legKidx, loopNum, loopidx, tidx, side, [], [])
        if loopNum <= 0
            # negative loopNum should never be used in evaluation
            add!(ver4.T4, (tidx, tidx, tidx, tidx))
            return ver4
        end
        for c in chan
            if c == T || c == U || c == S
                for ol = 0:loopNum - 1
                    push!(ver4.bubble, Bubble{Ver4}(ver4, c, ol))
                end
            end
        end
        return ver4
    end
end

function _expandBubble(children, text, style, bub::Bubble, parent)
    push!(children, zeros(Int, 0))
    @assert parent == length(children)
    dict = Dict(
        I => ("I", "yellow"),
        T => ("T", "red"),
        TC => ("Tc", "pink"),
        U => ("U", "blue"),
        UC => ("Uc", "navy"),
        S => ("S", "green"),
    )
    # println("bubble chan ", bub.chan)
    push!(text, "$(dict[bub.chan][1])\n$(bub.Lver.loopNum)-$(bub.Rver.loopNum)")
    push!(style, "fill:$(dict[bub.chan][2])")

    current = length(children) + 1
    push!(children[parent], current)
    _expandVer4(children, text, style, bub.Lver, current) # left vertex 

    current = length(children) + 1
    push!(children[parent], current)
    _expandVer4(children, text, style, bub.Rver, current) # right vertex
end

function _expandVer4(children, text, style, ver4::Ver4, parent)
    push!(children, zeros(Int, 0))
    @assert parent == length(children)
    # println("Ver4: $(ver4.level), Bubble: $(length(ver4.bubble))")
    if ver4.loopNum > 0
        info = "O$(ver4.loopNum)\nT[$(length(ver4.T4))]\n"
        for t in ver4.T4
            info *= "[$(t[1]) $(t[2]) $(t[3]) $(t[4])]\n"
        end
    else
        info = "O$(ver4.loopNum)"
    end
    push!(text, info)

    for bub in ver4.bubble
        # println(bub.chan)
        current = length(children) + 1
        push!(children[parent], current)
        _expandBubble(children, text, style, bub, current)
    end
end

function visualize(ver4::Ver4)
    children, text, style = (Vector{Vector{Int}}(undef, 0), [], [])
    _expandVer4(children, text, style, ver4, 1)

    # text = ["one\n(second line)", "2", "III", "four"]
    # style = ["", "fill:red", "r:14", "opacity:0.7"]
    # link_style = ["", "stroke:blue", "", "stroke-width:10px"]
    tooltip = ["pops", "up", "on", "hover"]
    t = D3Trees.D3Tree(
        children,
        text = text,
        style = style,
        tooltip = tooltip,
        # link_style = link_style,
        title = "Vertex4 Tree",
        init_expand = 2,
    )

    D3Trees.inchrome(t)
end

end
