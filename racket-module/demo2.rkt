#lang racket

; show how to provide struct

(module m racket
  (provide s
           s?)
  (struct s (v)))

(require 'm)

(s? (s 3))
