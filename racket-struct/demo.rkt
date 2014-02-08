#lang racket

(struct posn (x y))

;structure subtype
(struct 3d-posn posn (z))

(3d-posn 1 2 3)


; equal not works for opague struct
(equal? (3d-posn 1 2 3)
        (3d-posn 1 2 3))

; reflection/dynamic evaluation also not works
(struct? 3d-posn)

(define v1 (3d-posn 1 2 3))

; This is interesting
(3d-posn-z v1)
(posn-x v1)
(3d-posn? v1)

(struct lead (width height))

; we want to use equal?
; I didn't get this part

(define (add-bigger-fish lst)
  (struct fish (size))
  (cond
    [(null? lst) (list (fish 1))]
    [else (cons (fish (* 2 (fish-size (car lst))))
                lst)]))

(add-bigger-fish '())
(add-bigger-fish '())
; I didn't get the example. Maybe I should read
; something about contract.
; (add-bigger-fish (add-bigger-fish '()))


(struct t1 (x))
(struct t2 (y))

(match (t2 4)
  [(or (t1 x)
       (t2 x))
   (print x)])
