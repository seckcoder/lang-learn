module type ID = sig
  type t
  val of_string : string -> t
  val to_string : t -> string
end

module Genid = struct
  type t
  let of_string (x:string) = x
  let to_string (x:t) = "abc"
end


(*Note that opaque type declaration in module sig and module struct is different
type even they are of the same name*)
(*module Username : ID = Genid*)
