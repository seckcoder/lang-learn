
import qualified Data.ByteString.Lazy.UTF8 as L
import Data.Char
import Network.Wreq
import Control.Lens
import System.Environment



simpleHttp url = do
  r <- get url
  return (L.toString (r ^. responseBody))

main =
  getArgs >>= simpleHttp . head >>= putStr
