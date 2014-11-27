#lang racket


#|(call-with-input-file|#
  ;"test.txt"
  ;(lambda (in)
    ;(let loop ([line (read-line in 'any)])
      ;(unless (eof-object? line)
        ;(display
          ;(map
            ;string->number
            ;(string-split line)))(newline)
        #|(loop (read-line in 'any))))))|#
