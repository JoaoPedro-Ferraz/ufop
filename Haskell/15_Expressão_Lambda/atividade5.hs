module Main where
main :: IO ()
main = do
    x <- readLn :: IO Int 
    print ((\x -> x + x) x)