module Main where
main :: IO ()
main = do
    putStrLn "Digite a base"
    putStr "Base: "
    x <- readLn :: IO Int 
    putStrLn "Digite o expoente"
    putStr "Expoente: "
    y <- readLn :: IO Int 
    print (calculaPotencia x y)

calculaPotencia :: Int -> Int -> Int 
calculaPotencia x y |y == 0 = 1
calculaPotencia x y = x * calculaPotencia x (y - 1)