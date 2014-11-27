#lang racket


Ma >>= (a->Mb) ->Mb
return : a -> Ma

(return x) >>= f  === f x
m >>= return === m
(m >>= f) >>= g === m >>= (lambda x -> (f x) >>= g)


fmap (t->u) -> Mt -> Mu
return : a->Ma



