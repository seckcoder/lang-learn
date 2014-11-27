#lang racket

(require "do.rkt")

(define return-writer
  (lambda (a)
    `(,a)))

(define bind-writer
  (lambda (ma f)
    (let [(mb (f (car ma)))]
      `(,(car mb)
         ,(append (cdr ma) (cdr mb))))))

(define tell-writer
  (lambda (msg)
    `(,msg)))


(define reciprocals
  (lambda (l)
    (cond
      [(null? l) (return-writer '())]
      [(zero? (car l))
       (do bind-writer
         (tell-writer "zero-value")
         (reciprocals (cdr l)))]
      [else
        (do bind-writer
          (d <- (reciprocals (cdr l)))
          (return-writer
            (cons (/ 1 (car l)) d)))])))

(reciprocals '[1 2 0 3 2])
