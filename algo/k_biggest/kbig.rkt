#lang racket

(define (split lst base cmp)
  (foldl
    (match-lambda*
      [(list v (list greater equal less))
        (case (cmp v base)
          [(>) (list (cons v greater) equal less)]
          [(=) (list greater (cons v equal) less)]
          [(<) (list greater equal (cons v less))])])
    (list '() '() '())
    lst))
  
(define (kbig lst k cmp)
  (cond
    [(= k 0) '()]
    [(<= (length lst) k) lst]
    [else
      (let ([base (car lst)])
        (match (split lst base cmp)
          [(list greater equal less)
            (cond
              [(> (length greater) k)
               (kbig greater k cmp)]
              [(= (length greater) k) greater]
              [(> (+ (length greater)
                     (length equal)) k)
               (append greater (kbig equal
                                     (- k (length greater))
                                     cmp))]
              [(= (+ (length greater)
                     (length equal)) k)
               (append greater equal)]
              [else
                (append (append greater equal)
                        (kbig less
                              (- k (length greater) (length equal))
                              cmp))])]))]))

(kbig '(10 7 32 5 2 8 29 16 83 51 47) 5 (lambda (v1 v2)
                                          (cond
                                            [(> v1 v2) '>]
                                            [(= v1 v2) '=]
                                            [(< v1 v2) '<])))
