

{-# LANGUAGE ScopedTypeVariables #-}

f :: forall a. a -> a
f x =
    let x' = x :: a
    in x'



mkpair1 :: forall a b. a -> b -> (a,b)
mkpair1 aa bb = (ida aa, bb)
    where
      ida :: a -> a -- This refers to a in the function's type signature
      ida = id

mkpair2 :: forall a b. a -> b -> (a,b)
mkpair2 aa bb = (ida aa, bb)
    where
      ida :: b -> b -- Illegal, because refers to b in type signature
      ida = id

mkpair3 :: a -> b -> (a,b)
mkpair3 aa bb = (ida aa, bb)
    where
      ida :: b -> b -- Legal, because b is now a free variable
      ida = id
