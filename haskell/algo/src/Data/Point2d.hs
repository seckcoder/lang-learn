


module Data.Point2d (
  Point2d(..),
  align,
  fromTuple
  ) where

    data Point2d a = Point2d { getx :: a, gety :: a } deriving (Show, Eq)

    align :: (Eq a, Num a) => Point2d a -> Point2d a -> Bool
    align (Point2d x1 y1) (Point2d x2 y2) = (x1 == x2) || (y1 == y2) || (abs(x1 - x2) == abs(y1 - y2))

    fromTuple (x,y) = Point2d x y
