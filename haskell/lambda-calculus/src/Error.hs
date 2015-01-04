{-# LANGUAGE NoImplicitPrelude #-}

module Error (
  Error(..)
  ) where

    import Data.String

    class Error a where
      noMsg :: a
      strMsg :: String -> a
      noMsg = strMsg ""
      strMsg _ = noMsg
