#lang racket

(define (take* f n lst)
  (cond
    [(null? lst) null]
    [(< (length lst) n)
     (f (expand n lst))]
    [else
     (let-values ([(left rest) (split-at lst n)])
       (f left)
    
    
    
