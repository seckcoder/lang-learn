; right shift for k
; shift by reversion
(define (shift! vec k)
  (let* ([len (vector-length vec)]
         [k (remainder k len)])
    (reverse-vec! vec 0 k)
    (reverse-vec! vec k len)
    (reverse-vec! vec 0 len)
  vec))

; reverse [start, end)
(define (reverse-vec! vec start end)
  (let ([mid (quotient (+ end start) 2)])
    (printf "~a-~a-~a\n" start mid end)
    ; mid = (end + start) / 2, with range[start,end)
    ; i in [start,mid). This will bring the least number of swap.
    ; ie, it will avoid the middle one when there is even number of ele
    ; in [start,end)
    (for ([i (in-range start mid)])
      (swap-vec! vec i (- end (- i start) 1)))))


(define (swap-vec! vec i j)
  (printf "~a ~a\n" i j)
  (let ([tmp (vector-ref vec i)])
    (vector-set! vec i (vector-ref vec j))
    (vector-set! vec j tmp)))

(shift! (vector 1 2 3 4 5 6) 7)
