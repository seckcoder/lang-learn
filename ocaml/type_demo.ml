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
