#lang racket


(define (foo x)
  (call/cc (lambda (k)
    (let ([y  (+ (* x x) 3)])
      (if (> y 20)
        (k "over twenty")
        (- y 4))
      ))))


(let ([k (foo 10)])
  (print k)
  )
