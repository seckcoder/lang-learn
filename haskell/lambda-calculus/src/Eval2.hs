
import qualified Data.Map as Map

data OR a b = L a | R b deriving (Show)

class SubType sub sup | sup -> sub where
  inj :: sub -> sup
  prj :: sup -> Maybe sub


instance SubType a (OR a b) where
  inj = L
  prj (L a) = Just a
  prj _ = Nothing

type InterpM = StateT Store (EnvT Env (ContT Answer (StateT String (ErrorT []))))

type Env = Map Name (InterpM Value)

lookupEnv :: Name -> Env -> Maybe (InterpM Value)
lookupEnv = Map.lookup

extendEnv :: Name -> (InterpM Value) -> Env -> Env
extendEnv = Map.insert



type Value = OR Int ( OR Fun ())
type Fun = InterpM Value -> InterpM Value

class InterpC t where
  interp :: t -> InterpM Value

instance (InterpC t1, InterpC t2) => InterpC (OR t1 t2) where
  interp (L t) = interp t
  interp (R t) = interp t

type Term = OR TermA (OR TermF OR (TermR OR (TermL OR (TermT OR (TermC TermN)))))

data TermA = Num Int
           | Add Term Term

instance InterpC TermA where
  interp (Num x) = unitInj x
  interp (Add x y) = interp x `bindPrj` \i ->
    interp y `bindPrj` \j ->
      unitInj (i+j)

unitInj = return . inj
m `bindPrj` k = m >>= \a -> case (prj a) of
                                 Just x -> k x
                                 Nothing -> err "runtime type error"

type Name = String
data TermF = Var Name
           | LambdaV Name Term -- call by value
           | LambdaN Name Term -- call by name
           | App Term Term

instance InterpC TermF where
  interp (Var v) = rdEnv >>=
    \env -> case lookupEnv v env of
                 Just val -> val
                 Nothing -> err ("unbound variables " ++ v)

  interp (LambdaV s t) = rdEnv >>=
    \env -> unitInj (\arg -> arg >>= \argv -> inEnv (extendEnv s (return argv) env) (interp t))

  interp (LambdaN s t) = rdEnv >>=
    \env -> unitInj (\arg -> inEnv (extendEnv s arg env) (interp t))

  interp (App e1 e2) = interp e1 `bindPrj` \f ->
    rdEnv >>= \env ->
      f (inEnv env (interp e2))


data TermR = Ref Term
           | Deref Term
           | Assign Term Term

instance InterpC TermR where
  interp (Ref x) = (interp x) >>= \val ->
    allocLoc >>= \loc ->
      updateLoc loc (return val) >> (unitInj loc)

  interp (Deref x) = (interp x) `bindProj` \loc -> lookupLoc loc

  interp (Assign lhs rhs) = (interp lhs) `bindProj` \loc ->
    (interp rhs) `bindProj` \val ->
      updateLoc loc (return val) >> (return val)

data TermL = LambdaL Name Term

instance InterpC TermL where
  interp (LambdaL s t) =
    rdEnv >>= \env ->
      unitInj (\arg ->
        allocLoc >>= loc ->
          let thunk = arg >>= v ->
            updateLoc loc (return v) env >> (return v)
            in updateLoc loc (return thunk) >> (inEnv (extendEnv s (lookupLoc loc) env) (interp t))



data TermT = Trace String Term

instance InterpC TermT where
  interp (Trace s t) =
    write  ("enter " ++ l) >>
      interp t >>= \v ->
        write ("leave " ++ l ++ " with: " ++ (show v)) >>
          (return v)



