#lang typed/racket

(require math/array)

(require/typed racket
               [string-split
                (case->
                 [String -> (Listof String)]
                 [String (U String Regexp) -> (Listof String)])])

(require "nb.rkt")

(: string->number/safe : String -> Number)
(define (string->number/safe str)
  (assert (string->number str) number?))

(: parse-input (String -> (U (List (Vectorof Number) Natural Natural) Nothing)))
(define (parse-input fname)
  (: string->numbers (String -> (Listof Number)))
  (define (string->numbers line)
    (map string->number/safe (string-split line)))
  (: make-ds (Integer Integer -> In-Indexes))
  (define (make-ds d1 d2)
    (ann (vector d1 d2) In-Indexes))
  (: parse-input-rec ((Listof Number) Natural Input-Port -> (U (List (Vectorof Number) Natural Natural) Nothing)))
  (define (parse-input-rec acc d2 in)
    (let ([line (read-line in 'any)])
      (if (eof-object? line)
          (list acc (make-ds (length line) d2))
          (let ([cur-nums (string->numbers line)])
            (if (= (length cur-nums) d2)
                (parse-input-rec (cons (string->numbers line) 
                                 acc)
                                 d2
                                 in)
                (error "Wrong Input Format"))))))
  (call-with-input-file
      fname
    (lambda: ([in : Input-Port])
      (let: ([line (read-line in 'any)])
        (if (eof-object? line)
            (error "empty data set")
            (let ([init (string->numbers line)])
              (parse-input-rec init (length init) in)))))))
      

(: shape-of-lst-2d : (All (A) (Listof (Listof A)) -> In-Indexes))
(define (shape-of-lst-2d lst)
  (let ([d1 (length lst)]
        [d2 (length
              (apply (inst car (Listof A) (Listof A))
                     (list lst)))])
    (ann ((inst vector Index) d1 d2) In-Indexes)))

;(define-values (data d1 d2) (parse-input "test.txt"))
