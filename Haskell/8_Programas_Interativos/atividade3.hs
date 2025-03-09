module Main where
main :: IO ()
main = do
    putStrLn "Digite uma frase"
    x <- getLine
    print (palindrome x)

palindrome :: String -> Bool
palindrome x |x == reverse x = True
             |otherwise = False