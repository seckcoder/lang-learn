#lang racket
(define (foo v)
  (match v
    [(? number?) v]))
(define (bar)
  (+ (foo "str") 2))

(module+ test
  ; for racket 5.3.5
  ; The compilation strategy of racket makes it impossible to
  ; find the exact line number where match failed
  ; (For the error msg, note that the compiler can't even provide
  ; the info that error happended in function "foo")
  (+ 1 (bar))
  )
