#lang racket

(require racket/match)

(define r "str")

(define (foo v)
  2)

(match r
  [(? foo)
   (printf "here")]
  ["str"
   (printf "there")])
