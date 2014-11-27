#lang racket
(require "do.rkt")

(define (fail)
  '(Nothing))

(define (return-maybe v)
  `(Just ,v))
(define (div-maybe a b)
  (if (= b 0)
    (fail)
    (return-maybe (/ a b))))

(define (bind-maybe ma f)
  (match ma
    ['(Nothing)
     (fail)]
    [`(Just ,v)
      (f v)]))


(do bind-maybe
  (x <- (return-maybe (+ 7 8)))
  (div-maybe x 4))

#|(bind-maybe|#
  ;(return-maybe (+ 7 8))
  ;(lambda (x)
    #|(div-maybe x 4)))|#
