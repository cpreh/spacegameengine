module Main where

import Util(walkDirs,scramble)
import System(getArgs)
import System.IO(withFile,hSeek,IOMode(ReadWriteMode),SeekMode(AbsoluteSeek))
import Data.List(isInfixOf,isSuffixOf)
import Debug.Trace(traceShow,trace)
import qualified Data.ByteString.Char8 as BS
import Data.ByteString(ByteString)

keyword = BS.pack "Franklin Street"
template = "template.hpp"

data CppData = Text ByteString | Comment ByteString
type CppFile = [CppData]

makeFile :: ByteString -> CppFile
makeFile s = makeCpp scrambled
  where scrambled = scramble (commentBegin,commentEnd) s
        commentBegin = BS.pack "/*"
        commentEnd = BS.pack "*/"
        makeCpp :: [ByteString] -> CppFile
        makeCpp = makeCpp' 0
        makeCpp' _ [] = []
        makeCpp' a (x:xs) | even a = Text x : rest
                          | otherwise = Comment x : rest
          where rest = makeCpp' (a+1) xs

updateDate :: ByteString -> ByteString -> ByteString
updateDate tempFile s = BS.concat $ map edit scrambled
  where scrambled = makeFile s 
        edit :: CppData -> ByteString
        edit (Text a) = a
        edit (Comment a) | keyword `BS.isInfixOf` a = tempFile
                         | otherwise = a

editContents :: ByteString -> ByteString -> ByteString
editContents tempFile xs | keyword `BS.isInfixOf` xs = updateDate tempFile xs
                         | otherwise = addHeader tempFile xs

addHeader :: ByteString -> ByteString -> ByteString
addHeader tempFile s = tempFile `BS.append` s

editFile :: FilePath -> IO ()
editFile name = do contents <- BS.readFile (trace ("editing file " ++ name) name)
                   tempFile <- BS.readFile template
                   BS.writeFile name (editContents tempFile contents)
{-
editFile name = do withFile name ReadWriteMode editIt
  where editIt h = do contents <- BS.hGetContents h
                      tempFile <- BS.readFile template
                      hSeek h AbsoluteSeek 0
                      BS.hPut h (editContents tempFile contents)
                      -}

cppFilter :: FilePath -> Bool
cppFilter xs = "hpp" `isSuffixOf` xs || "cpp" `isSuffixOf` xs

main = do args <- getArgs
          walkDirs editFile cppFilter (if null args then ["."] else args)
--          walkDirs putStrLn (if null args then ["."] else args)
