let rec even n =
  if n = 0
  then true
  else odd (n - 1)
and odd n =
  if n = 0
  then false
  else even (n - 1)
;;

(*(even 10);;*)

let rec fact n =
  fact_iter n 1
and fact_iter n acc =
    if n = 0 then
      acc
    else
      fact_iter (n - 1) (n * acc)
;;

(*fact 10*)


(*Declaring function with function*)

