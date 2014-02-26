#lang racket

; find an index in vec that equals to v.
; this is simple.
; loop invariant: i in [low, high], low <= high, break on low>high
(define (bin-search vec v)
  (let loop ([low 0]
             [high (sub1 (vector-length vec))])
    (if (> low high)
      -1
      (let ([mid (quotient (+ low high) 2)])
        (cond
          [(= (vector-ref vec mid) v)
           ; find one , return
           mid]
          [(< (vector-ref vec mid) v)
           ; i in [low,high], a[mid] < v, too small, so we expect
           ; i > mid
           (loop (add1 mid) high)]
          [(> (vector-ref vec mid) v)
           ; i in [low,high], a[mid] > v, too big, so we expect
           ; i < mid
           (loop low (sub1 mid))])))))

(bin-search (vector 1 2 2 3) 2)


; find a range:[a,b] in vec, that equals to v
; invariant: i in (low,high), with (low+1) < high(assume there's at least one value)
; break if (low+1)>=high.
(define (bin-search-range vec v)
  (letrec ([search-low (lambda ()
                         ; search for the lowest idx
                         (let loop ([low -1]
                                    [high (vector-length vec)])
                           (if (>= (add1 low) high)
                             high ; high is maintaind to equal to the lowest idx if found
                             (let ([mid (quotient (+ low high) 2)])
                               (cond
                                 [(= (vector-ref vec mid) v)
                                  ; a[mid] = v, as we look for the lowest idx,
                                  ; we set high as mid
                                  (loop low mid)]
                                 [(< (vector-ref vec mid) v)
                                  ; a[mid] < v, as i in (low,high),
                                  ; we expect i > mid
                                  (loop mid high)]
                                 [(> (vector-ref vec mid) v)
                                  ; a[mid] > v, as i in (low,high)
                                  ; we expect i < mid
                                  (loop low mid)])))))]
           [search-high (lambda ()
                          (let loop ([low -1]
                                     [high (vector-length vec)])
                            (if (>= (add1 low) high)
                              low
                              (let ([mid (quotient (+ low high) 2)])
                                (cond
                                  [(= (vector-ref vec mid) v)
                                   (loop mid high)]
                                  [(< (vector-ref vec mid) v)
                                   (loop mid high)]
                                  [(> (vector-ref vec mid) v)
                                   (loop low mid)])))))])
    (list (search-low)
          (search-high))))

(bin-search-range (vector 1 2 2 3) 2)
