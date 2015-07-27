
module LongestPalindromicSubstring (
  longestPalindrome,
  samples
  ) where

    import Data.Vector ((!))
    import qualified Data.Vector as V
    import qualified Data.List as L
    import Data.List (maximumBy)
    import Debug.Trace

    longestPalindrome :: [Char] -> [Char]
    longestPalindrome s = maximumBy (\ a b -> compare (length a) (length b)) $ (map oddPal [0..n-1]) ++ (map evenPal [0..n-2])
      where n = length s
            refStr = (!) (V.fromList s)
            refEq (u,v) = refStr u == refStr v
            oddPal i = let pal = L.takeWhile refEq  $ zip [i-1, i-2 .. 0] [i+1 .. n-1]
                        in map (refStr . fst) (reverse pal) ++ [refStr i] ++ map (refStr . snd) pal
            evenPal i = let pal = L.takeWhile refEq $ zip [i,i-1..0] [i+1..n-1]
                         in map (refStr . fst) (reverse pal) ++ map (refStr . snd) pal


    samples = [
      longestPalindrome "aba",
      longestPalindrome "ababac",
      longestPalindrome "abaaba"
      ]
