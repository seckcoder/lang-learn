open Core.Std

(*confusing different kinds of identifiers
is a very real source of bugs, and the
approach of minting abstract types for
different classes of identifiers is an
effective way of avoiding such issues.*)

(*module Username : sig
  type t
  [>interface<]
  val of_string : string -> t
  val to_string : t -> string 
end = struct
  [>representation<]
  type t = string
  let of_string x = x
  let to_string x = x
end


let uname = Username.of_string "xx" in
  print_endline (Username.to_string uname)*)

module type ID = sig
  type t
  val of_string : string -> t
  val to_string : t -> string
  val print_t : t -> unit
end

module String_id = struct
  type t = string
  let of_string x = x
  let to_string x = x
  let print_t x =
    print_string x
end

module Int_id = struct
  type t = int
  let of_string x = Int.of_string x
  let to_string x = Int.to_string x
  let print_t x =
    print_int x
end

module Username : ID = String_id
module Hostname : ID = String_id
module UserId : ID = Int_id

(*The following exp won't compile*)
(*print_str (Username.of_string "str")*)
Username.print_t (Username.of_string "str")
;;

UserId.print_t (UserId.of_string "3")
;;

(*local open*)

let average x y =
  let open Int64 in
    x + y / of_int 2
;;

(*This function just shadow the above function*)
(*The order of declarations in the ml mostly
matters insofar as it affects which values
are shadowed. If we wanted to replace a function
in List with a new function of the same name,
the declaration of that function in the ml
would have to come after the include List declaration.*)
let average x y =
  Int64.(x + y / of_int 2)
;;

average (Int64.of_int 2) (Int64.of_int 3)

module type ModType = sig
  type t
  val f : int -> t
end

module M1 : ModType = struct
  let f x = x
end

