open Core.Std

module type X_int = sig
  val x : int
end


(*module Modname (ModArg) : ModType*)
module Increment (M : X_int) : X_int = struct
  let x = M.x + 1
end

module Three = struct let x = 3 end

module Four = Increment(Three)

module type Comparable = sig
  type t
  val compare: t -> t -> int
end

module type Interval_intf = sig
  type t
  type endpoint
  val create : endpoint -> endpoint -> t
  val is_empty : t -> bool
  val contains : t -> endpoint -> bool
  val intersect : t -> t -> t
end

(*Question: why we have to add this constraint? it seems
the type system actually can infer the type endpoint*)
module Make_interval(Endpoint: Comparable) :
  (Interval_intf with type endpoint = Endpoint.t) = struct
  (*Interval_intf = struct*)

  type t = | Interval of Endpoint.t * Endpoint.t
           | Empty

  type endpoint = Endpoint.t

  let create low high =
    if Endpoint.compare low high > 0 then Empty
    else Interval (low, high)

  let is_empty = function
    | Empty -> true
    | Interval _ -> false

  let contains t x =
    match t with
    | Empty -> false
    | Interval (low, high) -> Endpoint.compare low x <= 0 &&
                              Endpoint.compare x high <= 0

  let intersect t1 t2 =
    let min x y = if Endpoint.compare x y <= 0 then x else y in
    let max x y = if Endpoint.compare x y >=0 then x else y in
    match t1,t2 with
    | Empty,_ | _, Empty -> Empty
    | Interval (l1,h1), Interval (l2,h2) ->
      create (max l1 l2) (min h1 h2)
end

module Int_interval = Make_interval(Int)

module String_interval = Make_interval(String)

module Rev_int_interval = Make_interval(struct
    type t = int
    let compare x y = Int.compare y x
  end)

(*Int_interval.create 3 4*)
