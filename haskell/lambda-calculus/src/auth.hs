{-
- A real world example. Showing how to authorize request using Monoid
-}


{-# LANGUAGE NoImplicitPrelude #-}

import GHC.Base
import System.IO
import Semigroup
import Monoid
import GHC.Show


data FailState = NoPrivilege
               | NotLogin deriving (Show)

data State = Success
           | Fail FailState

instance Show State where
  show Success = "Success"
  show (Fail x) = "Failed : " ++ (show x)

instance Semigroup State where
  (Fail x) <> _ = (Fail x)
  _ <> (Fail x) = (Fail x)
  Success <> Success = Success

instance Monoid State where
  mempty = Success

data Role = Admin
          | Visitor
          | NormalUser deriving (Show, Eq)

data User = User { name :: String, role :: Role }
data Request = Request { isAuthenticated :: Bool, user :: User }

isLogin (Request isAuthenticated _) =
  if isAuthenticated
     then Success
     else Fail NotLogin

isAdmin (Request _ user) =
  if (role user) == Admin
     then Success
     else Fail NoPrivilege

main = do
  print (mconcat [isLogin, isAdmin] (Request True (User "WeiLi" Admin)))
  print (mconcat [isLogin, isAdmin] (Request True (User "Seckcoder" NormalUser)))
  print (mconcat [isLogin, isAdmin] (Request False (User "Red A" NormalUser)))
