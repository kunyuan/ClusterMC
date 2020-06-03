using StaticArrays
const DIM = 3
const MaxLoopNum = 8
const Mom = MVector{MaxLoopNum,Int}


const I, T, U, S, TC, UC, SC = 1, 2, 3, 4, 5, 6, 7
const IN, OUT = 1, 2
const INL, OUTL, INR, OUTR = 1, 2, 3, 4
const LEFT, RIGHT = 1, 2

function getK(loopidx)
    K = zero(Mom)
    K[loopidx] = 1
    return K
end

function add!(pool, obj)
    idx = findall(x->x == obj, pool)
    @assert length(idx) <= 1 "Multiple elements are found!"
    if length(idx) == 0
        push!(pool, obj)
        return length(pool)
    else
        return idx[1]
    end
end
