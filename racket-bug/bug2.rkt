
; the expected result should be #f, #f
; but racket 5.9 takes it wrong
(display (eq? "a" "a"))
(display (eq? (string #\a) (string #\a)))
