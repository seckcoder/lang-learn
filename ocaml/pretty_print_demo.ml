open Format;;

(*Question:
  1. why we need the box stuff?
  2. It seems that it still works even when I don't open the box...*)

type lambda =
  | Lambda of string * lambda
  | Var of string
  | Apply of lambda * lambda
;;

let rec print_exp0 = function
  | Var s -> print_string s
  | lam -> open_hovbox 1; print_string "("; print_lambda lam; print_string ")"; close_box ()
and print_app = function
  | e -> open_hovbox 2; print_other_applications e; close_box ()
and print_other_applications f =
  match f with
    | Apply (f , arg) -> print_app f; print_space (); print_exp0 arg
    | f -> print_exp0 f
and print_lambda = function
  | Lambda (s , lam) ->
      open_hovbox 1;
      print_string "\\";
      print_string s;
      print_string ".";
      print_space ();
      print_lambda lam;
      close_box()
  | e -> print_app e
;;

(*print_exp0 (Apply (Lambda ("a", (Var "b")), (Var "c")));*)

(*Format.printf "@[%s@]@." "hello world";;*)
Format.printf "%i %c %f %s\n" 3 'c' 3.4 "hello world";;
