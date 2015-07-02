
; infix expression evaluation

(define (filter pred? xs)
  (let loop ((xs xs) (ys '()))
    (cond ((null? xs) (reverse ys))
          ((pred? (car xs))
            (loop (cdr xs) (cons (car xs) ys)))
          (else (loop (cdr xs) ys)))))

; expr -> term | expr + term | expr - term
; term -> factor | term * factor | term / factor
; factor -> number | ( expr )

(define (calc str)
  (let ((xs (filter (lambda (c) (not (char-whitespace? c)))
                    (string->list str))))
    (let-values (((c xs) (expr xs)))
      (if (null? xs) c
        (error 'calc (string-append
          "extra input at " (list->string xs)))))))

(define (expr xs)
  (let-values (((y ys) (term xs)))
    (let loop ((e y) (ys ys))
      (cond ((null? ys)(values e ys))
            ((char=? (car ys) #\+)
              (let-values (((z zs) (term (cdr ys))))
                (loop (+ e z) zs))) 
            ((char=? (car ys) #\-)
              (let-values (((z zs) (term (cdr ys))))
                (loop (- e z) zs)))
            (else (values e ys))))))

(define (term xs)
  (let-values (((y ys) (factor xs)))
    (let loop ((t y) (ys ys))
      (cond ((null? ys) (values t ys))
            ((char=? (car ys) #\*)
              (let-values (((z zs) (factor (cdr ys))))
                (loop (* t z) zs)))
            ((char=? (car ys) #\/)
              (let-values (((z zs) (factor (cdr ys))))
                (loop (/ t z) zs)))
            (else (values t ys))))))

(define (factor xs)
  (define (digit x)
    (- (char->integer x) 48))
  (cond ((null? xs) (error 'factor "unexpected end of input"))
        ((char-numeric? (car xs))
          (let loop ((n (digit (car xs))) (ys (cdr xs)))
            (cond ((null? ys) (values n ys))
                  ((char-numeric? (car ys))
                    (loop (+ (* n 10) (digit (car ys))) (cdr ys)))
                  (else (values n ys)))))
        ((and (pair? (cdr xs)) (char=? (car xs) #\-)
              (char-numeric? (cadr xs)))
          (let loop ((n (digit (cadr xs))) (ys (cddr xs)))
            (cond ((null? ys) (values (- n) ys))
                  ((char-numeric? (car ys))
                    (loop (+ (* n 10) (digit (car ys))) (cdr ys)))
                  (else (values (- n) ys)))))
        ((char=? (car xs) #\()
          (let-values (((y ys) (expr (cdr xs))))
            (cond ((null? ys) (error 'factor (string-append
                    "expected ) at " (list->string ys))))
                  ((char=? (car ys) #\))(values y (cdr ys)))
                  (else (error 'factor (string-append
                    "unexpected character at " (list->string ys)))))))
        (else (error 'factor (string-append
          "unexpected character at " (list->string xs))))))

(define-syntax assert
  (syntax-rules ()
    ((assert expr result)
      (if (not (equal? expr result))
          (for-each display `(
            #\newline "failed assertion:" #\newline
            expr #\newline "expected: " ,result
            #\newline "returned: " ,expr #\newline))))))

(define (test-calc)
  (assert (calc "123") 123)
  (assert (calc "-123") -123)
  (assert (calc "(123)") 123)
  (assert (calc "(((123)))") 123)
  (assert (calc "1 2 3") 123)
  (assert (calc "1+2") (+ 1 2))
  (assert (calc "1+-2") (+ 1 -2))
  (assert (calc "1-2") (- 1 2))
  (assert (calc "1--2") (- 1 -2))
  (assert (calc "2*3") (* 2 3))
  (assert (calc "2*-3") (* 2 -3))
  (assert (calc "2/3") (/ 2 3))
  (assert (calc "2/-3") (/ 2 -3))
  (assert (calc "2*3+4") (+ (* 2 3) 4))
  (assert (calc "2-3*4") (- 2 (* 3 4)))
  (assert (calc "2/3+4") (+ (/ 2 3) 4))
  (assert (calc "2-3/4") (- 2 (/ 3 4)))
  (assert (calc "2*(3+4)") (* 2 (+ 3 4)))
  (assert (calc "(2-3)*4") (* (- 2 3) 4))
  (assert (calc "2/(3+4)") (/ 2 (+ 3 4)))
  (assert (calc "(2-3)/4") (/ (- 2 3) 4))
  (assert (calc "1+2+3+4") (+ 1 2 3 4))
  (assert (calc "1-2-3") (- (- 1 2) 3))
  (assert (calc "1*2*3*4") (* 1 2 3 4))
  (assert (calc "1/2/3") (/ (/ 1 2) 3))
  (assert (calc "123+456*789") (+ 123 (* 456 789))))

(test-calc) ; no news is good news

(display (calc "123 + 456 * 789"))
