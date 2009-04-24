module Main where

import Util(walkDir)
import qualified Data.ByteString.Char8 as BS
import Data.ByteString(ByteString,breakSubstring)
import System.FilePath.Posix(makeRelative)
import Data.Char(toUpper)
import Data.List(isSuffixOf)
import Data.Word(Word8)
import Debug.Trace(trace)
import System(getArgs)

fileFilter :: FilePath -> Bool
fileFilter xs = "hpp" `isSuffixOf` xs

replaceRange :: String -> Char -> ByteString -> ByteString
replaceRange needle replace haystack = BS.map helper haystack
  where helper :: Char -> Char
        helper a = if a `elem` needle 
                     then replace 
                     else a

editName :: ByteString -> ByteString -> ByteString
editName prefix = (prefix `BS.append`) . (`BS.append` (BS.pack "_INCLUDED")) . (replaceRange "/." '_') . (BS.map toUpper)

count :: ByteString -> ByteString -> Integer
count needle haystack | BS.null after = 0
                      | otherwise = 1 + count needle (BS.drop (BS.length needle) after)
  where (before,after) = BS.breakSubstring needle haystack

checkContents :: ByteString -> ByteString -> ByteString -> IO ()
checkContents prefix fileName contents = do
  if found >= 2
    then do return ()
    else do putStrLn $ (BS.unpack fileName) ++ ": Search for " ++ (BS.unpack search) ++ " returned " ++ show found
    where search = editName prefix fileName
          found = count search contents

checkFile :: ByteString -> FilePath -> FilePath -> IO ()
checkFile prefix first fp = do 
 -- contents <- BS.readFile (trace ("analyzing " ++ (BS.unpack edited)) fp)
  contents <- BS.readFile fp
  checkContents prefix edited contents
    where edited = BS.pack (makeRelative first fp)

walkDirs :: [FilePath] -> IO ()
walkDirs xs = mapM_ (helper . BS.pack) xs
  where helper :: ByteString -> IO ()
        helper x = walkDir (checkFile prefix realname) fileFilter realname
                 where (prefix,realname) = generatePair x

generatePair :: ByteString -> (ByteString,FilePath)
generatePair xs = helper $ BS.span (/= ':') xs
  where helper (a,b) | BS.null b = (BS.empty,BS.unpack a)
                     | otherwise = (a,BS.unpack $ BS.tail b)

main = do args <- getArgs
          walkDirs args
