module Main where
main :: IO () 
main = do
    putStrLn "Digite 2 números para se calcula o MDC"
    putStr "Primeiro número: "
    x <- readLn :: IO Int 
    putStr "Segundo número: "
    y <- readLn :: IO Int
    putStrLn("Mdc: " ++ show(calculaMdc x y))

calculaMdc :: Int -> Int -> Int
calculaMdc a b |b == 0 = a
               |b > 0 = calculaMdc b (a `mod` b) 
               |b < 0 = calculaMdc a (-b)