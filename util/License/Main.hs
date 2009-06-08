module Main where

import Util(walkDirs,scramble)
import System(getArgs)
import System.IO(withFile,hSeek,IOMode(ReadWriteMode),SeekMode(AbsoluteSeek))
import Data.List(isInfixOf,isSuffixOf)
import Debug.Trace(traceShow,trace)
import qualified Data.ByteString.Char8 as BS
import Data.ByteString.Internal(isSpaceChar8)
import Data.ByteString(ByteString)
import Control.Monad.Reader

data Env = Env {
  envKeyword :: ByteString,
  envTemplate :: FilePath
}

env = Env { envKeyword = BS.pack "Franklin Street", envTemplate = "template.hpp"  }

type EnvReader = Reader Env

data CppData = Text ByteString | Comment ByteString
type CppFile = [CppData]

extractCpp :: CppData -> ByteString
extractCpp (Text a) = a
extractCpp (Comment a) = a

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
updateDate tempFile s = iterate scrambled
  where scrambled = makeFile s 
        iterate :: CppFile -> ByteString
        iterate [] = BS.pack ""
        iterate ((Text a):xs) = a `BS.append` (iterate xs)
        iterate ((Comment a):xs) | keyword `BS.isInfixOf` a = tempFile `BS.append` (iterate' xs)
                                 | otherwise = a `BS.append` (iterate xs)
        iterate' [] = BS.pack ""
        iterate' (x:xs) = (stripWhites (extractCpp x)) `BS.append` (iterate xs)
        stripWhites x = (BS.pack "\n") `BS.append` (BS.dropWhile isSpaceChar8 x)

editContents :: ByteString -> ByteString -> ByteString
editContents tempFile xs | keyword `BS.isInfixOf` xs = updateDate tempFile xs
                         | otherwise = addHeader tempFile xs

addHeader :: ByteString -> ByteString -> ByteString
addHeader tempFile s = tempFile `BS.append` s

editFile :: FilePath -> IO ()
editFile name = do contents <- BS.readFile (trace ("editing file " ++ name) name)
                   tempFile <- BS.readFile template
                   BS.writeFile name (runReader (editContents (BS.init tempFile) contents) env)
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
