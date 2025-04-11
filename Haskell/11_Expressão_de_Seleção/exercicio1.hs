module Main where
main :: IO()
main = do
    putStr "Digite o numero de termos pegos"
    num <- readLn :: IO Int 
    putStr "digite a lista"
    lista <- leituraLista
    putStrLn " "
    print (prefixo num lista)

prefixo :: Int -> [Int] -> [Int]
prefixo num (x : xs) |num == 0 = []
                     |otherwise = x : prefixo (num -1) xs

leituraLista :: IO [Int]
leituraLista = do
    num <- readLn :: IO Int
    if num < 0
        then 
            return []
        else do
            restante <- leituraLista
            return (num : restante)