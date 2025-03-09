module Main where
main :: IO ()
main = do
    putStrLn "Digite um número: "
    x <- readLn :: IO Int 
    print (fatorialDuplo x)

fatorialDuplo :: Int -> Int 
fatorialDuplo x |x == 0 = 1
                |x == 1 = 1
                |otherwise = x * fatorialDuplo (x - 2)
