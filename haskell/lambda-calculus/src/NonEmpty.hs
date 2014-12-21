{-# LANGUAGE NoImplicitPrelude #-}

module NonEmpty ( NonEmpty(..) ) where

  import GHC.Show

  infixr 5 :|
  data NonEmpty a = a :| [a] deriving (Show)
