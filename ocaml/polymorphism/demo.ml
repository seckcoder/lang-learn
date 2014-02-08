let f = (fun v -> v) in
((fun g ->
    let f = g in
    ((f 3), (f true))) f)

