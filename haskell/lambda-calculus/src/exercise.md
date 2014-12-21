Functors

  Implement fmap for Either e, ((,) e) and ((->) e).
  Write a function with type signature Functor f => (a -> b) -> f (f a) -> f (f b). If you are stuck, try writing the function for a specific instance of functor. Can this type signature be generalized?
  What is the type of fmap fmap? Specify both using Functor f => and explicitly. Remember that all functions in Haskell are automatically curried.
  What is the type of fmap fmap fmap?
  Pointed
  Implement pure for [] and ((->) e).
  Assuming a well-behaved functor that follows the laws fmap id = id and fmap (g . h) = fmap g . fmap h, prove that fmap g . pure = pure . g for all definitions of pure. (Nota bene: a rigorous treatment of this question may require Wadler's theorems for free, which is not for the lighthearted.)

Applicative

  What symbols are used for the infix version of fmap?
  Implement <*> for Maybe, [] and ZipList.
  Implement <*> for ((->) e). This is tricky.
  What is the value of [(+1), (+2)] <*> [4, 5]?
  What is the type of const <*> id? Rewrite this expression in a form that makes this obvious from the applicative law fmap g x = pure g <*> x.
  What is the value of ((+) <*> (+3)) 5?
  Write fmap with pure and <*>.
  Write liftA2 :: Applicative f => (a -> b -> c) -> f a -> f b -> f c with only <$> and <*>.

