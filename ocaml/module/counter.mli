open Core.Std

type t

val empty : t

val to_list : t -> (string * int) list
  
val touch : t -> string -> t
