module Paths_samples (
    version,
    getBinDir, getLibDir, getDataDir, getLibexecDir,
    getDataFileName, getSysconfDir
  ) where

import qualified Control.Exception as Exception
import Data.Version (Version(..))
import System.Environment (getEnv)
import Prelude

catchIO :: IO a -> (Exception.IOException -> IO a) -> IO a
catchIO = Exception.catch


version :: Version
version = Version {versionBranch = [0,1,0,0], versionTags = []}
bindir, libdir, datadir, libexecdir, sysconfdir :: FilePath

bindir     = "/Users/seckcoder/code/lang-learn/haskell/samples/.cabal-sandbox/bin"
libdir     = "/Users/seckcoder/code/lang-learn/haskell/samples/.cabal-sandbox/lib/x86_64-osx-ghc-7.8.3/samples-0.1.0.0"
datadir    = "/Users/seckcoder/code/lang-learn/haskell/samples/.cabal-sandbox/share/x86_64-osx-ghc-7.8.3/samples-0.1.0.0"
libexecdir = "/Users/seckcoder/code/lang-learn/haskell/samples/.cabal-sandbox/libexec"
sysconfdir = "/Users/seckcoder/code/lang-learn/haskell/samples/.cabal-sandbox/etc"

getBinDir, getLibDir, getDataDir, getLibexecDir, getSysconfDir :: IO FilePath
getBinDir = catchIO (getEnv "samples_bindir") (\_ -> return bindir)
getLibDir = catchIO (getEnv "samples_libdir") (\_ -> return libdir)
getDataDir = catchIO (getEnv "samples_datadir") (\_ -> return datadir)
getLibexecDir = catchIO (getEnv "samples_libexecdir") (\_ -> return libexecdir)
getSysconfDir = catchIO (getEnv "samples_sysconfdir") (\_ -> return sysconfdir)

getDataFileName :: FilePath -> IO FilePath
getDataFileName name = do
  dir <- getDataDir
  return (dir ++ "/" ++ name)
