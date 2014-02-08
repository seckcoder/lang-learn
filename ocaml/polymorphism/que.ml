(*(fun v -> v)
  ('a -> 'a)

('a -> 'a) -> ('a -> 'a)*)

(*let f = (fun v -> v) in
(f f)*)


(fun g ->
   ((g 3), (g true)))

