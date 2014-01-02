let foldmap f l =
  List.fold_left
    (fun acc v -> List.append acc (f v))
    []
    l
;;

List.fold_left (fun acc v -> (acc + v)) 0 [1;2;3];;

List.fold_left (fun acc v ->
                  List.append acc v)
  []
  [[1;2;3];[4;5;6]]
;;

foldmap (fun v -> v) [[1;2;3];[4;5;6]]

let rec range a b =
  if a > b then
    []
  else
    a :: (range (a + 1) b)
;;


foldmap (fun v -> v) [(range 1 3); (range 4 6)];;

foldmap (fun v -> [v]) (range 1 3);;


type site =
  | Vert of int
  | Horz of int * int
;;

(*Same type, we can put it into the list*)
[(Vert 3); (Horz (4, 5))]
;;


type vert_site = { x: int; y1:int; y2: int};;
type horz_site = { y: int; x1:int; x2: int};;

type site =
  | VertSite of vert_site
  | HorzSite of horz_site
;;

let vert_site1 = { x = 3; y1 = 4; y2 = 5};;
let horz_site1 = { y = 2; x1 = 5; x2 = 7};;

(*Not work, since vert_site1 and horz_site1's types are not the same*)
(*[vert_site1; horz_site1];;*)

(*Work!*)
[(VertSite vert_site1) ; (HorzSite horz_site1)]
;;

(*List partition*)

List.partition
  (fun v -> (v mod 2) = 0)
  (range 1 10)
;;

(*split a list at the pos n*)
let split_at n l =
  let rec split_at_iter i prev l =
    match l with
      | [] -> (prev, [])
      | first::rest ->
          if i = 0 then
            (prev, rest)
          else split_at_iter (i - 1) (first::prev) rest
  in let (prev, rest) = (split_at_iter n [] l) in
    (List.rev prev, rest)
;;

(*
 * split_at 0 [1;2;3];;
 * split_at 1 [1;2;3];;
 * split_at 2 [1;2;3];;
 * split_at 3 [1;2;3];;
 *)

let remove_i i l =
  let (prev, rest) = split_at i l in
    prev @ rest
;;

remove_i 0 [1;2;3]
;;

List.fold_left2
  (fun acc i j ->
     (i + j) :: acc)
  []
  (range 0 10)
  (range 10 20)
;;

let filteri pred l =
  List.fold_left2
    (fun (l1,ids) v i ->
       if pred v then
         (v::l1, i::ids)
       else (l1, ids))
    ([],[])
    l
    (range 0 ((List.length l) - 1))
;;

let split_if pred l =
  let (l1, ids) = filteri pred l in
    List.map2
      (fun v i -> (v, remove_i i l))
      (List.rev l1)
      (List.rev ids)
;;

split_if (fun v -> (v = 2)) (range 0 10)
;;

let string_of_list l =
  List.fold_right
    (fun c s ->
       (String.make 1 c) ^ s)
    l
    ""
;;

string_of_list ['a';'b';'c']
;;
