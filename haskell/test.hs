{-# LANGUAGE MultiParamTypeClasses #-}
class Collection e ce where
  emptyColl :: ce
  insert :: e -> ce -> ce
  member :: e -> ce -> Bool

