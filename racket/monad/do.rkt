#lang racket

(provide do)

(define-syntax do
  (syntax-rules (<-)
    [(_ bind e) e]
    [(_ bind (v0 <- e0) e e* ...)
     (bind e0 (lambda (v0)
                (do bind e e* ...)))]
    [(_ bind e0 e e* ...)
     (bind e0 (lambda (_)
                (do bind e e* ...)))]))
