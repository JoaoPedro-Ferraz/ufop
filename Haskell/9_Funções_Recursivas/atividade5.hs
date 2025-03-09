module Main where 
main :: IO () 
main = do
    putStrLn "Digite um número" 
    putStr "Número: "
    x <- readLn :: IO Int 
    print (calculaRaizAux x)

calculaRaizAux :: Int -> Int
calculaRaizAux x = calculaRaiz x 1

calculaRaiz :: Int -> Int -> Int
calculaRaiz x y | y * y > x =  y -1
                |otherwise = calculaRaiz x (y + 1)