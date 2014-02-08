(module m1 racket
  ; The name of module doens't matter
  (provide talk)
  (define (talk)
    (printf "I'm cake\n")
    ))

; We can only define a module in a file

#|(module m2 racket
  (provide talk2)
  (define (talk2)
    (printf "I'm not a cake\n")
    ))|#
