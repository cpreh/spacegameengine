module Main where

import Util(walkDirs,scramble)
import System(getArgs)
import System.IO(withFile,hSeek,IOMode(ReadWriteMode),SeekMode(AbsoluteSeek))
import Data.List(isInfixOf,isSuffixOf)
import Debug.Trace(traceShow,trace)
import qualified Data.ByteString.Char8 as BS
import Data.ByteString.Internal(isSpaceChar8)
import Data.ByteString(ByteString)

template = "template.hpp"
keyword = BS.pack "Franklin Street"
keywordfile = "hint.txt"
exclusionfile = "exclusions.txt"

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

updateDate :: ByteString -> ByteString -> ByteString -> ByteString
updateDate keyword tempFile s = iterate scrambled
  where scrambled = makeFile s 
        iterate :: CppFile -> ByteString
        iterate [] = BS.pack ""
        iterate ((Text a):xs) = a `BS.append` (iterate xs)
        iterate ((Comment a):xs) | keyword `BS.isInfixOf` a = tempFile `BS.append` (iterate' xs)
                                 | otherwise = a `BS.append` (iterate xs)
        iterate' [] = BS.pack ""
        iterate' (x:xs) = (stripWhites (extractCpp x)) `BS.append` (iterate xs)
        stripWhites x = (BS.pack "\n") `BS.append` (BS.dropWhile isSpaceChar8 x)

editContents :: ByteString -> ByteString -> ByteString -> ByteString
editContents keyword tempFile xs | keyword `BS.isInfixOf` xs = updateDate keyword tempFile xs
                                 | otherwise = addHeader tempFile xs

addHeader :: ByteString -> ByteString -> ByteString
addHeader tempFile s = tempFile `BS.append` s

editFile :: ByteString -> FilePath -> IO ()
editFile keyword name = do contents <- BS.readFile (trace ("editing file " ++ name) name)
                           tempFile <- BS.readFile template
                           BS.writeFile name (editContents keyword (BS.init tempFile) contents)
{-
editFile name = do withFile name ReadWriteMode editIt
  where editIt h = do contents <- BS.hGetContents h
                      tempFile <- BS.readFile template
                      hSeek h AbsoluteSeek 0
                      BS.hPut h (editContents tempFile contents)
                      -}

cppFilter :: FilePath -> Bool
cppFilter xs = "hpp" `isSuffixOf` xs || "cpp" `isSuffixOf` xs

exclusionFilter :: [FilePath] -> FilePath -> Bool
exclusionFilter paths path = elem path paths

loadExclusions :: FilePath -> IO [FilePath]
loadExclusions path = do contents <- BS.readFile path
                         return $ map BS.unpack (BS.split '\n' contents)

loadKeyword :: FilePath -> IO ByteString
loadKeyword path = BS.readFile path

filterAnd :: (a -> Bool) -> (a -> Bool) -> a -> Bool
filterAnd func1 func2 x = (func1 x) && (func2 x)

main = do args <- getArgs
          keyword <- loadKeyword keywordfile
          exclusions <- loadExclusions exclusionfile
          walkDirs (editFile keyword) (filterAnd cppFilter (exclusionFilter exclusions)) (if null args then ["."] else args)
--          walkDirs putStrLn (if null args then ["."] else args)
