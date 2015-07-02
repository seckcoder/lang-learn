
data Point a = Point a a deriving Show

instance Eq a => Eq (Point a) where
  Point x1 y1 == Point x2 y2 = (x1 == x2) && (y1 == y2)


