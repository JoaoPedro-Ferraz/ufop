module Main where
main :: IO ()
main = do
    x <- leituraNum 

leituraNum :: IO [Int]
leituraNum = do
    putStr "Digite um número: "
    num <- readLn :: IO Int 
    if()