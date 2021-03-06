
module Algo.Pretty () where

  data Doc = Empty
           | Char Char
           | Text String
           | Line
           | Concat Doc Doc
           | Union Doc Doc
           deriving (Show, Eq)

  import Data.Monoid

  char :: Char -> Doc
  char c = Char c

  text :: String -> Doc
  text "" = Empty
  text s = Text s

  double :: Double -> Doc
  double d = text (show d)

  line :: Doc
  line = Line

  string :: String -> Doc
  string = enclose '"' '"' . mconcat . map oneChar

  enclose :: Char -> Char -> Doc -> Doc
  enclose left right x = char left <> x <> char right

  oneChar :: Char -> Doc
  oneChar c = case lookup c simpleEscapes of
                   Just r -> text r
                   Nothing | mustEscape c -> hexEscape c
                           | otherwise -> char c
                             where mustEscape c = c < ' ' || c == '\x7f' || c > '\xff'

  simpleEscapes :: [(Char, String)]
  simpleEscapes = zipWith (\ a b -> (a, ['\\',b])) "\b\n\f\r\t\\\"/" "bnfrt\\\"/"

  hexEscape :: char -> Doc
  hexEscape c
    | d < 0x10000 = smallHex d
    | otherwise = astral (d - 0x10000)

  astral n = smallHex (a + 0xd800) <> smallHex (b + 0xdc00)
    where a = (n `shiftR` 10) .&. 0x3ff
          b = n .&. 0x3ff

  smallHex :: Int -> Doc
  smallHex x = text "\\u" <> text (replicate (4 - length h) '0') <> text h

  instance Monoid Doc where
    mempty = Empty
    mappend = Concat

  prettify :: JValue -> Doc
  prettify (JString s) = string s
  prettify (JNumber n) = double n
  prettify b@(JBool _) = text (show b)
  prettify nv@JNull = text (show nv)
  prettify (JObject o) = series '{' '}' field o
    where field (name,val) = string name <> text ": " <> prettify val
  prettify (JArray a) = series '[' ']' prettify a

  series :: Char -> Char -> (a -> Doc) -> [a] -> Doc
  series open close item = enclose open close . fsep . punctuate (char ',') . map item
  fsep xs = undefined
  punctuate :: Doc -> [Doc] -> [Doc]
  punctuate p [] = []
  punctuate p [d] = [d]
  punctuate p (d:ds) = (d <> p) : punctuate p ds
