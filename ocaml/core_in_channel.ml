open Core.Std;;


let print_strings l =
  List.iter l ~f:(fun line -> (print_endline line))

let readfile fname =
  let lines = In_channel.read_lines fname in
  let filter_f = (fun line ->
                    (String.strip line) <> "") in
  let (lines1, lines2) = List.split_while lines ~f:filter_f in
  let lines2 = List.filter lines2 ~f:filter_f in
  let lines1 = List.filter lines1 ~f:filter_f in
    (lines1, lines2)

let (lines1, lines2) = readfile "./p7_09a.dat" in
  (print_strings lines1);
  (print_endline "-----------------");
  (print_strings lines2);
  (print_endline "-----------------")
