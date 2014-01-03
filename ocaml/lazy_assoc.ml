(*lazy association use lazy monad*)

let rec sassoc l v =
  match l with
    | [] -> Lazymonad.MZero
    | (a,b)::rest when a = v ->
        Lazymonad.mplus (Lazymonad.Unit b) (fun () ->
                                    sassoc rest v)
    | _::rest -> sassoc rest v
;;

let l = [(1,"a"); (2,"b"); (3,"c"); (4,"b"); (3,"e"); (6,"d"); (3,"k")] in
  Lazymonad.take 2 (sassoc l 3)
