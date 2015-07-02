{-# LANGUAGE MultiParamTypeClasses #-}
{-# LANGUAGE FlexibleInstances #-}

import Data.Maybe
import Control.Monad.Identity

data OR a b = L a | R b deriving Show

class SubType sub sup where
  inj :: sub -> sup
  prj :: sup -> Maybe sub

instance SubType a (OR a b) where
  inj = L
  prj (L x) = Just x
  prj _ = Nothing


instance SubType a b => SubType a (OR c b) where
  inj = R . inj
  prj (R a) = prj a
  prj _ = Nothing

type InterpM = Identity

type Value = OR Int (OR Fun ())
type Fun = InterpM Value -> InterpM Value




