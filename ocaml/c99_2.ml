open Core.Std
open Format

let readfile fname =
  let lines = In_channel.read_lines fname in
  let filter_f = (fun line ->
      (String.strip line) <> "") in
  let (lines1, lines2) = List.split_while lines ~f:filter_f in
  let lines2 = List.filter lines2 ~f:filter_f in
  let lines1 = List.filter lines1 ~f:filter_f in
  (lines1, lines2)

type site =
  | HorzSite of (int * int * int)  (*x y hlen*)
  | VertSite of (int * int * int)  (*x y vlen*)
;;

let row site_map i =
  site_map.(i)
;;

let col site_map i =
  (Array.map
     ~f:(fun site_s -> site_s.(i))
     site_map)
;;

let dim site_map =
  (Array.length site_map , Array.length (row site_map 0))
;;

let flatmap f l =
  List.fold_left
    ~f:(fun acc v -> List.append acc (f v))
    ~init:[]
    l
;;


let rec consective s pred =
  consective_from 0 s pred
and consective_from i s pred =
  if i >= (Array.length s) then
    []
  else match consective_from1 i s pred with
    | 0 -> consective_from (i+1) s pred
    | 1 -> consective_from (i+2) s pred
    | n -> (i,n) :: (consective_from (i+n+1) s pred)
and consective_from1 i s pred =
  if i >= (Array.length s) then
    0
  else if pred (Array.get s i) then
    1 + (consective_from1 (i + 1) s pred)
  else 0
;;

let make_site_map sites =
  List.to_array
    (List.map
       sites
       ~f:(fun site -> String.to_array site))

let make_sites site_map =
  let (nrows, ncols) = dim site_map in
  (List.append
     (flatmap
        (fun y -> (List.map
                     ~f:(fun (x, hlen) -> (HorzSite (x, y, hlen)))
                     (consective (row site_map y) (fun c -> c <> ' '))))
        (List.range 0 nrows)
     )
     (flatmap
        (fun x -> (List.map
                     ~f:(fun (y, vlen) -> (VertSite (x, y, vlen)))
                     (consective (col site_map x) (fun c -> c <> ' '))))
        (List.range 0 ncols)
     ))
;;

let print_sites sites =
  List.iter ~f:(function
      | HorzSite (x, y, len) ->
        printf "%i %i %i\n" x y len
      | VertSite (x, y, len) ->
        printf "%i %i %i\n" x y len)
    sites
  ;
  printf "\n"
;;

let c_arr_to_string c_arr =
  String.of_char_list (Array.to_list c_arr)

let print_site_map site_map =
  Array.iter
    ~f:(fun c_arr -> print_endline (c_arr_to_string c_arr))
    site_map
;;


let words,sites = readfile "p7_09a.dat" in
let site_map = make_site_map sites in
print_site_map site_map;
print_endline "------------";
let sites =
  make_sites site_map
  |> List.map ~f:(function
      | HorzSite (x,y,hlen) -> (hlen, (HorzSite (x,y,hlen)))
      | VertSite (x,y,vlen) -> (vlen, (VertSite (x,y,vlen))))
  |> List.fold
    ~init:[]
    ~f:(fun acc (len, site) ->
        match List.Assoc.find acc len with
        | None -> List.Assoc.add acc len [site]
        | Some lst -> List.Assoc.add acc len (site::lst)
      )
  |> List.sort
    ~cmp:(fun (len1, site1) (len2, site2) ->
        if len1 < len2 then -1
        else if len1 > len2 then 1
        else 0) in 
let word_map = 
  words
  |> List.mapi ~f:(fun i word -> (i,word)
;;
