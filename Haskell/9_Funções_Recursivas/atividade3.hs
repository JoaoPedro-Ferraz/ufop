module Main where
main :: IO ()
main = do
    putStrLn "Digite o intervalo: "
    putStr "Primeiro número: "
    x <- readLn :: IO Int 
    putStr "Segundo número: "
    y <- readLn :: IO Int
    print(calculaProduto x y)

calculaProduto :: Int -> Int -> Int 
calculaProduto x y |x > y = 1
                   |otherwise = x * calculaProduto(x + 1) y 