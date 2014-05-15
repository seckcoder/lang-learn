
(define root 'uninitialized)
(define k 'uninitialized)

(define (trav r)
  (set! root r)
  (set! k (lambda (vec) vec))
  (trav/k))

(define (trav/k)
  (if (is-leaf? root)
    (k '())
    (begin
      (let ([root-left (get-left root)]
            [root-right (get-right root)]
            [orig-root (copy-node root)])
        (set! root root-left)
        (set! k (lambda (vec_left)
                  (set! root root-right)
                  (set! k (lambda (vec_right)
                            (append
                              vec_left
                              vec_right
                              (list (get-value orig-root)))))
                  (trav/k)))
        (trav/k)))))

(define (trav/k)
  (if (is-leaf? root)
    (k '())
    (begin
      (let ([root-left (get-left root)]
            [root-right (get-right root)]
            [orig-root (copy-node root)])
        (set! root root-left)
        (set! k (lambda (vec_left)
                  (set! root root-right)
                  (set! k (lambda (vec_right)
                            (append
                              vec_left
                              vec_right
                              (list (get-value orig-root)))))
                  (trav/k)))
        (trav/k)))))


(define (trav r)
  (trav/k r (lambda (vec) vec)))

(define (trav/k r k)
  (if (is-leaf? r)
    (k '())
    (trav/k (get-left r)
            (lambda (vec_left)
              (trav/k (get-right r)
                      (lambda (vec_right)
                        (append
                          vec_left
                          vec_right
                          (list (get-value r)))))))))

(define (trav/k r k)
  (if (is-leaf? r)
    (k '())
    (trav-left/k (get-left r) r left_k)))

(define (trav-left/k r parent)
  (if (is-leaf? r)
    (left_k '() parent)
    (begin
      (trav-left/k (get-left r) r (lambda (vec_left)
                                    (vec_left ...))))))

(define (left_k vec_left r)
  (trav/k (get-right r) right_k))

(define (right_k vec_right vec_left r)
  (append
    vec_left
    vec_right
    (list (get-value r))))


(define (trav r)
  (if (is-leaf? r)
    '()
    (append (trav (get-left r))
            (trav (get-right r))
            (list (get-value r)))))

(define (trav/k r k)
  (if (is-leaf? r)
    (k '())
    (trav/k (get-left r)
            (lambda (vec_left)
              (trav/k (get-right r)
                      (lambda (vec_right)
                        (append
                          vec_left
                          vec_right
                          (list (get-value r)))))))))

(define (trav/k r k)
  (if (is-leaf? r)
    (k '() '() r)
    (trav/k (get-left r) left-k)))
            (lambda (vec_left _ r)
              (trav/k (get-right r)
                      (lambda (vec_right vec_left r)
                        (append
                          vec_left
                          vec_right
                          (list (get-value r))))))
