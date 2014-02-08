open Core.Std
open Format

let line_stream_of_channel channel =
  Stream.from (fun _ ->
                 try Some (input_line channel)
                 with End_of_file ->
                   None);;

let rec range a b =
  if a > b then
    []
  else
    a :: (range (a + 1) b)
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

let remove_i i l =
  let (prev, rest) = split_at i l in
    prev @ rest
;;

let rec collect_words strm =
  let line = Stream.next strm in
    if String.strip line = "" then
      []
    else line :: (collect_words strm)
;;

let rec collect_sites strm =
  try
    let line = (Stream.next strm) in
      (String.to_array line):: (collect_sites strm)
  with Stream.Failure ->
    []
;;

type site =
  | HorzSite of (int * int * int)  (*x y hlen*)
  | VertSite of (int * int * int)  (*x y vlen*)
;;

let row site_map i =
  site_map.(i)
;;

let maprowi f site_map =
  List.mapi
    ~f:f
    site_map
;;

let replace_str s1 x len s2 =
  let new_s1 = (String.copy s1) in
    String.blit s2 0 new_s1 x len;
    new_s1;
;;

let replace_str1 s x c =
  replace_str s x 1 (String.make 1 c)
;;

let replace_row site_map (x, y, hlen) word =
  maprowi
    (fun i s ->
          if i = y then
            replace_str s x hlen word
          else s)
    site_map
;;

let replace_col site_map (x, y, vlen) word =
  maprowi
    (fun i s ->
       if (i >= y) && (i < (y + vlen)) then
         replace_str1 s x word.[(i-y)]
       else s)
    site_map
;;

let string_of_list l =
  List.fold_right
    ~f:(fun c s ->
          (String.make 1 c) ^ s)
    ~init:""
    l
;;

(*TODO: more efficient representation of site_map*)
let col site_map i =
  (Array.map
    ~f:(fun site_s -> site_s.[i])
    site_map)
;;

let rec lookup_site site_map a_site =
  match a_site with
    | HorzSite (x, y, hlen) ->
        Array.sub (row site_map y) x hlen
    | VertSite (x, y, vlen) ->
        Array.sub (col site_map x) y vlen
;;

let word_match_site word site_s =
  if (String.length word) <> (String.length site_s) then
    false
  else 
    List.for_all2
      (fun wi si ->
         let (wc, sc) = (word.[wi], site_s.[si]) in
           if (sc = '.') || (wc = sc) then
             true
           else false)
      (range 0 ((String.length word) - 1))
      (range 0 ((String.length site_s) - 1))
;;

(*site_s: string representation of site*)
let lookup_word words site_s =
  None
;;

let fill_map site_map a_site word =
  match a_site with
    | HorzSite site_v -> replace_row site_map site_v word
    | VertSite site_v -> replace_col site_map site_v word
;;

let rec solve words sites site_map =
  match sites with
    | [] -> Lazymonad.Unit site_map
    | a_site :: rest_sites ->
        let site_s = (lookup_site site_map a_site) in
          match (lookup_word words site_s) with
            | None -> None
            | Some pairs ->
                try
                  List.find
                    (function
                       | None -> false
                       | Some site_map -> true)
                    (List.map
                       (fun (word, rest_words) ->
                          solve
                            rest_words
                            rest_sites (fill_map site_map a_site word))
                       pairs)
                with Not_found ->
                  None
;;

(*nrows * ncols*)
let dim site_map =
  (Array.length site_map , String.length (row site_map 0))
;;

let flatmap f l =
  List.fold_left
    (fun acc v -> List.append acc (f v))
    []
    l
;;

(*get the start and end index of substring in s of whose characters
 all pass pred*)
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
  else if pred s.(i) then
    1 + (consective_from1 (i + 1) s pred)
  else 0
;;

let make_sites site_map =
  let (nrows, ncols) = dim site_map in
    (List.append
      (flatmap
        (fun y -> (List.map
                     (fun (x, hlen) -> (HorzSite (x, y, hlen)))
                     (consective (row site_map y) (fun c -> c <> ' '))))
        (range 0 (nrows - 1)))
      (flatmap
         (fun x -> (List.map
                      (fun (y, vlen) -> (VertSite (x, y, vlen)))
                      (consective (col site_map x) (fun c -> c <> ' '))))
         (range 0 (ncols - 1))))
;;

let print_sites sites =
  List.iter (function
               | HorzSite (x, y, len) ->
                   Format.printf "%i %i %i\n" x y len
               | VertSite (x, y, len) ->
                   Format.printf "%i %i %i\n" x y len)
    sites
;;

let c_arr_to_string c_arr =
  String.of_list (Array.to_list c_arr)

let print_site_map site_map =
  Array.iter
    (fun c_arr -> print_endline (c_arr_to_string c_arr))
    site_map
;;

let c = open_in "p7_09c.dat" in
  try
    let strm = (line_stream_of_channel c) in
    let words = (collect_words strm) in
    let site_map = Array.of_list (collect_sites strm) in
      print_site_map site_map;
    let sites = make_sites site_map in
      (*print_bool (word_match_site "xxx" "x.x");*)
      (*match solve words sites site_map with
        | None -> print_endline "no solution"
        | Some site_map -> print_site_map site_map;*)
      print_sites sites;
      (*print_site_map (replace_row site_map (6, 5, 2) "..");*)
      (*print_site_map (replace_col site_map (8, 4, 2) "..");*)
      close_in c
  with e ->
    close_in c;
    raise e
;;
