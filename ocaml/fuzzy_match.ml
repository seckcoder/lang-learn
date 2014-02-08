open Core.Std;;
open Format;;

let rec bin_search1 arr v i j cmp =
  if (i = j) && (cmp (Array.get arr i) v) = 0 then
    i
  else if ( i >= j ) then
     -1
  else let mid = (i + j) / 2 in
  let cmpres = (cmp (Array.get arr mid) v) in
    if cmpres = 0 then
      bin_search1 arr v i mid cmp
    else if cmpres = 1 then
      bin_search1 arr v i (mid-1) cmp
    else
      bin_search1 arr v (mid+1) j cmp
and bin_search2 arr v i j cmp =
  if ( i > j ) then
    i
  else let mid = (i + j) / 2 in
  let cmpres = (cmp (Array.get arr mid) v) in
    if cmpres = 0 then
      bin_search2 arr v (mid+1) j cmp
    else if cmpres = 1 then
      bin_search2 arr v i (mid-1) cmp
    else
      bin_search2 arr v (mid+1) j cmp
and bin_search arr v cmp =
  ((bin_search1 arr v 0 ((Array.length arr) - 1) cmp),
   (bin_search2 arr v 0 ((Array.length arr) - 1) cmp))


let cmp_string site_s word =
  let len_s = String.length site_s in
  let len_w = String.length word in
    if len_s < len_w then
      -1
    else if len_s > len_w then
      1
    else 
      let rec iter i =
        if i >= len_s then 0
        else if site_s.[i] = '.' then
          iter (i + 1)
        else if site_s.[i] = word.[i] then
          iter (i + 1)
        else if site_s.[i] < word.[i] then
      -1
        else 1
      in
        iter 0
;;


let fuzzy_match words ids s =
  let (low, high) = bin_search ids s (fun i sj ->
                                        let si = words.(i) in
                                          cmp_string si sj) in
    if low = -1 then
      Lazymonad.MZero
    else 
      let rec iter low high =
        if low = high then
          Lazymonad.Unit low
        else Lazymonad.mplus (Lazymonad.Unit low) (fun () ->
                                                     (iter (low + 1) high))
      in iter low (high-1)
;;


(*let _ =
 Lazymonad.take 2
 (Lazymonad.bind (fuzzy_match [|"abc"; "bcd"; "b.d"; "edc"|] [|0;1;2;3|] "bcd")
 (fun id ->
 printf "%d\n" id;
 Lazymonad.Unit id))*)
