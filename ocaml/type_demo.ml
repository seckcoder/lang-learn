type point2d = {x:int; y:int};;


let x = 2 in
let y = 3 in
  {x = x; y = y}
;;


type vartype =
  | Type1 of int * string
  | Type2 of int
;;



(*Note point2d and vert_site is the same type since
* they are constructed from the same expr *)
type vert_site = {x : int; y: int};;


{x = 3; y = 4};;


(*polymophism*)
type 'a mt =
  | MZero
  | Unit of 'a
  | Cons of 'a * (unit -> 'a mt)
;;

let rec mplus ma get_ma =
  match ma with
    | MZero -> get_ma ()
    | Unit a -> Cons (a, get_ma)
    | Cons (a, get_ma0) ->
        Cons (a, (fun () -> 
                    (mplus (get_ma0 ())
                       get_ma)))
;;


