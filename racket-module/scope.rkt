#lang racket

(struct s (v))

(define (bar)
  (print "bar"))

(module* M racket
  (provide foo)
  (require (submod ".."))
  (define t (s 3))
  (define (foo)
    (match t
      ; Not lexical scope
      [(s v)
       (print v)]))
  )
