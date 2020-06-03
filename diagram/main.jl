include("global.jl")
using StaticArrays

struct Green
    K::Int
    T::Tuple{Int,Int}
end

struct Vertex
    loopNum::Int
    channel::Int
    K::Tuple{Int,Int,Int,Int}
    T::Tuple{Int,Int,Int,Int}
end

struct Pool
    K::Vector{Mom}
    G::Vector{Green}
    Ver::Vector{Vertex}
    Pool() = new([], [], [])
end

pool = Pool()
include("vertex4.jl")

lKidx = add!(pool.K, getK(1))
rKidx = add!(pool.K, getK(1))
LegKidx = (lKidx, lKidx, rKidx, rKidx)
ver = Vertex4.Ver4(1, [I, T, U, S, TC, UC], LegKidx, 3, 3, 1, RIGHT)

printstyled("Building Diagrams...\n", color = :yellow)

Vertex4.visualize(ver)


