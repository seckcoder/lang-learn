type 'a mt =
  | MZero
  | Unit of 'a
  | Cons of 'a * (unit -> 'a mt)
;;


val bind : 'a mt -> ('a -> 'a mt) -> 'a mt

val mplus : 'a mt -> (unit -> 'a mt) -> 'a mt

val map : int -> 'a mt -> ('a -> 'a) -> 'a list

val map_inf : 'a mt -> ('a -> 'a) -> 'a list

val take : int -> 'a mt -> 'a list
