module Ast ( Exp(..), Value(..), Env(..) ) where

  import Data.Map

  type Name = String
  data Exp = Lit Integer
           | Var Name
           | Plus Exp Exp
           | Lambda Name Exp
           | App Exp Exp
           deriving Show


  data Value = IntVal Integer
             | FunVal Env Name Exp
             deriving Show

  type Env = Map Name Value
