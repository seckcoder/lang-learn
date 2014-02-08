datatype typ = VAR of string | INT | BOOL | ARROW of typ * typ

fun typ2str (VAR a) = "'" ^ a
  | typ2str INT = "int"
  | typ2str BOOL = "bool"
  | typ2str (ARROW(t1 as ARROW(_,_), t2)) =
  "(" ^ typ2str t1 ^ ") -> " ^ typ2str t2
  | typ2str (ARROW(t1,t2)) = typ2str t1 ^ " -> " ^ typ2str t2

fun identity (t : typ) = t

(*replace b with substituion (a,t)*)
fun replace (a, t) (VAR b) =
  if a = b then t else VAR b
  | replace (a, t) (ARROW (t1, t2)) =
  ARROW (replace (a, t) t1, replace (a, t) t2)
  | replace (a, t) t1 = t1

fun occurs (a, VAR b) = (a = b)
  | occurs (a, ARROW(t1, t2)) = occurs (a, t1) orelse occurs (a, t2)
  | occurs
