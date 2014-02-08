List.range 0 2;;


List.Assoc.add [(2, "a");
                (3, "b")] 2 "c"
;;


let l = [1;2;3] in
List.fold_left l
  ~init:0
  ~f:(fun acc v -> (acc + v))
