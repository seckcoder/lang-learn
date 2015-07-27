


module LetterCombinationsOfAPhoneNumber (
  letterCombinations,
  digitToLetters
  ) where

    import qualified Data.Vector as V
    import Data.Char
    import Debug.Trace

    letters = V.fromList [
      "abc", "def", "ghi", "jkl", "mno",
      "pqrs", "tuv", "wxyz"
      ]

    digitToLetters :: Char -> [Char]
    digitToLetters c = letters V.! (ord c - ord '2')

    letterCombinations :: [Char] -> [[Char]]
    letterCombinations [] = [[]] -- Note we should not return [] here!
    letterCombinations (c:s) = [c':s' | c' <- digitToLetters c, s' <- letterCombinations s]



    -- Another method using do notation
    -- letterCombinations (c:s) = do
    --   c' <- digitToLetters c
    --   s' <- letterCombinations s
    --   return (c':s')
