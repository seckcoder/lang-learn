(*string operation demo for ocaml*)


(*string append*)
let str_cons c s = (String.make 1 c) ^ s;;
let str_append_c s c = s ^ (String.make 1 c);;

(*This func may be O(n)*)
let str_cdr s = String.sub s 1 ((String.length s) - 1);;


str_cons 'a' "abc";;
str_append_c "abc" 'a';;
str_cdr "abc";;



(*get the start and end index of substring in s of whose characters
all pass pred*)
let rec consective s pred =
  consective_from 0 s pred
and consective_from i s pred =
    if i >= (String.length s) then
      []
    else match consective_from1 i s pred with
      | 0 -> consective_from (i+1) s pred
      | n -> (i,n) :: (consective_from (i+n+1) s pred)
and consective_from1 i s pred =
  (*just get one*)
  if i >= (String.length s) then
    0
  else if pred s.[i] then
    1 + (consective_from1 (i + 1) s pred)
  else 0
;;


consective "  ... ..." (fun c -> c = '.');;
consective "" (fun c -> c = '.');;
consective "." (fun c -> c = '.');;

(*string blit*)
let s1 = "abc";;
let s2 = "cdef";;
String.blit s1 0 s2 1 3;;
s2;;
