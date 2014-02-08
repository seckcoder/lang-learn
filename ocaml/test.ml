

List.iter ~f:(fun (len, sites) -> print_sites sites)
  (List.fold_left
     ~f:(fun acc (len, site) ->
           match List.Assoc.find acc len with
             | None -> List.Assoc.add acc len site::[]
             | Some (len, lst) -> List.Assoc.add acc len site::lst)
     ~init:[]
                                                                 (List.map ~f:(function
                                                                                 | HorzSite (x,y,hlen) -> (hlen, (HorzSite (x,y,hlen)))
                                                                                 | VertSite (x,y,vlen) -> (vlen, (VertSite (x,y,vlen))))
                                                                    (make_sites site_map)))

