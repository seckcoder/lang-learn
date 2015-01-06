{-# LANGUAGE NoImplicitPrelude #-}


module Foldable (
  Foldable(..)
  ) where

    import Prelude ((.), id, flip)
    import Maybe
    import Either
    import Monoid
    import qualified Data.List as List

    class Foldable t where
      fold :: Monoid m => t m -> m
      fold = foldMap id

      -- foldMap's default combination order is from right to left
      foldMap :: Monoid m => (a -> m) -> t a -> m
      foldMap f = foldr (mappend . f) mempty

      -- b is type of initial value
      foldr :: (a -> b -> b) -> b -> t a -> b
      foldr f z t = appEndo (foldMap (Endo . f) t) z

      -- Dual reverse the combination order
      foldl :: (b -> a -> b) -> b -> t a -> b
      foldl f z t = appEndo (getDual (foldMap (Dual . Endo . flip f) t)) z

      {-# MINIMAL foldMap | foldr #-}

    instance Foldable Maybe where
      foldr _ z Nothing = z
      foldr f z (Just x) = f x z

      foldl _ z Nothing = z
      foldl f z (Just x) = f z x

    instance Foldable [] where
      foldr = List.foldr
      foldl = List.foldl

    instance Foldable (Either e) where
      foldMap _ (Left _) = mempty
      foldMap f (Right y) = f y

      foldr _ z (Left _) = z
      foldr f z (Right y) = f y z
