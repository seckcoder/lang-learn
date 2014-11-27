
data IOAction a = Return a
                | Put String (IOAction a)
                | Get (String -> IOAction a)

get = Get (\s -> Return s)
put s = Put s (Return ())

-- why construct the monad like this?
seqio (Return a) f = f a
seqio (Get g) f    = Get (\s -> seqio (g s) f)
seqio (Put s io) f = Put s (seqio io f)

hello = put "What's your name?" ` seqio ` \_    ->
        get ` seqio ` \name ->
        put "What is your age?" ` seqio ` \_    ->
        get ` seqio ` \age  ->
        put ("Hello " ++ name ++ "!") ` seqio ` \_    ->
        put ("You are " ++ age ++ " years old")


hello2 = do put "What's your name?"
            name <- get
            put "What is your age?"
            age <- get
            put ("Hello," ++ name ++"!")
            put ("You are " ++ name ++ " years old!")

instance Monad IOAction where
    return = Return
    (>>=)  = seqio

instance Show a => Show (IOAction a) where
  show io = go 0 0 io
    where
      go m n (Return a) = ind m "Return " ++ show a
      go m n (Put s io) = ind m "Put " ++ show s ++ " (\n" ++ go (m+2) n io ++ "\n" ++ ind m ")"
      go m n (Get g)    = let i = "$" ++ show n
                          in ind m "Get (" ++ i ++ " -> \n" ++ go (m+2) (n+1) (g i) ++ "\n" ++ ind m ")"

      ind m s = replicate m ' ' ++ s


mapio :: (a -> b) -> IOAction a -> IOAction b
mapio f (Return a) = Return (f a)
mapio f (Put s io) = Put s (mapio f io)
mapio f (Get g)    = Get (\s -> mapio f (g s))

instance Functor IOAction where
    fmap = mapio

run (Return a) = return a
run (Put s io) = putStrLn s >> run io
run (Get f)    = getLine >>= run . f

-- haskell's io is pure since all the functions involved are pure. This is obvious
-- based on the above implementation. However, when does IO take effect?
