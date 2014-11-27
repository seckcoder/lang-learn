#lang typed/racket

(: filter-even ((Listof Natural) (Listof Natural) -> (Listof Natural)))
(define (filter-even lst accum)
  (let: loop : (Listof Natural)
        ([accum : (Listof Natural) null]
         [lst : (Listof Natural) lst])
        (cond
          [(null? lst) (reverse accum)]
          [(even? (car lst))
           (loop (cons (car lst) accum)
                 (cdr lst))]
          [else (loop accum (cdr lst))])))

(filter-even '(1 2 3 4 5) '())
