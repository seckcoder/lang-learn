type 'a mt =
  | MZero
  | Unit of 'a
  | Cons of 'a * (unit -> 'a mt)

let rec mplus ma get_ma =
  match ma with
    | MZero -> get_ma ()
    | Unit a -> Cons (a, get_ma)
    | Cons (a, get_ma0) ->
        Cons (a, (fun () -> 
                    (mplus (get_ma0 ())
                       get_ma)))

let rec bind ma f =
  match ma with
    | MZero -> MZero
    | Unit a -> f a
    | Cons (a, get_ma) ->
        mplus (f a) (fun () ->
                       (bind (get_ma ()) f))

let rec map n ma f =
  match ma with
    | MZero -> []
    | Unit a -> [f a]
    | Cons (a, get_ma) ->
        (f a) :: (if n < 0 then
                    map n (get_ma ()) f
                  else if n > 1 then
                    map (n-1) (get_ma ()) f
                  else
                    [])

let map_inf ma f =
  map (-1) ma f

let take n ma =
  map n ma (fun v -> v)
