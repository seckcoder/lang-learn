module Data.SimpleJson () where


data JValue = JString String
            | JNumber Double
            | JBool Bool
            | JNull
            | JObject [(String, JValue)]
            | JArray [JValue]
            deriving (Eq, Ord, Show)



instance Show JValue where
  show (JString s) = show s
  show (JNumber n) = show n
  show (JBool True) = "true"
  show (JBool False) = "false"
  show JNull = "null"

  show (JObject o) = "{" ++ pairs o ++ "}"
    where pairs [] = ""
          pairs ps = intercalate ", " (map renderPair ps)
          renderPair (s,v) = s ++ ": " ++ (show v)

  show (JArray a) = "[" ++ values a ++ "["
    where values [] = ""
          values vs = intercalate "," (map show vs)

