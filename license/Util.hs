module Util(walkDir,walkDirs,scramble) where

import System.Directory(getDirectoryContents,doesDirectoryExist,doesFileExist)
import Control.Monad(filterM)
import Debug.Trace(traceShow,trace)
import System.FilePath.Posix(takeFileName)

import qualified Data.ByteString.Char8 as BS
import Data.ByteString(ByteString)

validDirectory :: FilePath -> IO Bool
validDirectory x = do exists <- doesDirectoryExist (trace ("analyzing directory " ++ show x) x)
                      return $ exists && edited /= "." && edited /= ".."
  where edited = takeFileName x

validFile :: (FilePath -> Bool) -> FilePath -> IO Bool
validFile f x = do exists <- doesFileExist (trace ("analyzing file " ++ show x) x)
                   return $ exists && (f x)

walkDir :: (FilePath -> IO ()) -> (FilePath -> Bool) -> FilePath -> IO ()
walkDir f g dir = do contents <- getDirectoryContents dir
                     dircontents <- (getDirectories (edited contents))
                     filecontents <- (getFiles (edited contents))
                     walkDirs f g dircontents
                     mapM_ f filecontents
  where edited :: [FilePath] -> [FilePath]
        edited xs = map (dir </>) xs
        getDirectories :: [FilePath] -> IO [FilePath]
        getDirectories xs = filterM validDirectory xs
        getFiles :: [FilePath] -> IO [FilePath]
        getFiles xs = filterM (validFile g) xs

walkDirs :: (FilePath -> IO ()) -> (FilePath -> Bool) -> [FilePath] -> IO ()
walkDirs f g dirs = do mapM_ (walkDir f g) dirs

ternary :: (ByteString,ByteString) -> ByteString -> (ByteString,ByteString,ByteString)
ternary (dbegin,dend) haystack = (before,inside,end)
  where (before,inside'') = BS.breakSubstring dbegin haystack
        (inside',end') = BS.breakSubstring dend inside''
        (inside,end) = (inside' `BS.append` dend,BS.drop (BS.length dend) end')

scramble :: (ByteString,ByteString) -> ByteString -> [ByteString]
scramble delims@(dbegin,dend) haystack 
  | dbegin `BS.isInfixOf` haystack && dend `BS.isInfixOf` haystack = scrambled
  | otherwise = [haystack]
    where (begin,inside,end) = ternary delims haystack
          scrambled = begin : inside : (scramble delims end)
