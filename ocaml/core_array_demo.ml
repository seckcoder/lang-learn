open Core.Std
;;

[|'a';'b';'c'|]

Array.map
  ~f:(fun v -> v)
  [|1;2;3|]
