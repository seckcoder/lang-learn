
import Data.HashMap

type FilePath = String

alphanum = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'"

data Freq = Freq HashMap Int

instance Monad Freq where
  return = (empty 0)
  (Freq hmap acc) >>= k = k hmap acc

statWordsRec "" word
  | strNull word = Freq empty 0
  | otherwise = Freq (HashMap word 1) 1
statWordsRec (c:xs) ""
  | c `notElem` alphanum = statWordsRec xs ""
  | otherwise = statWordsRec xs c:""
statWordsRec (c:xs) word
  | c `notElem` alphanum =
    do

    insertWith (\ new_value old_value -> new_value + old_value) word 1 statWordsRec xs ""
  | otherwise = statWordsRec xs c:word

statWords str = statWordsRec str ""


main = do
  (fpath,_) <- getArgs
  fs <- readFile fpath
  word_freq <- statWords fs
  putWordFreq word_freq
