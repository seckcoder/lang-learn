OCaml's let polymorphism implementation

I'm confused about let polymorphism in OCaml. 

Consider the following code:

```
A: 
let f = (fun v -> v) in
((f 3), (f true))

B:
let f = (fun v -> v) in
((fun g -> g)
    ) f)

C:
let f = (fun v -> v) in
((fun g ->
    let f = g in
    ((f 3), (f true))) f)

```

For A and B, there is no problem. But for C,
OCaml reports error:

```
Error: This expression has type bool but an expression was expected of type
         int
```

So for A, when evaluating `((f 3), (f true))`, `f` has type `'a -> 'a`,
for B, when evaluating `let f = g in f`, `f` has type `'a -> 'a`.
But for C, when evaluating `((f 3), (f true))`, `f` got type `int -> int`.

Why C's f doesn't have type `'a -> 'a`?

I have difficulty in understanding the implementation of `OCaml`'s
`let polymorphism`, I'll appreciate it a lot if anyone can give a concise
description of it with respect to the question.
