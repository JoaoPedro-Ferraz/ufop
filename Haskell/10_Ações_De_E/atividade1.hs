module Main where
main :: IO ()
main = do
    numeros <- lerNumeros
    print (somaNumeros numeros)

lerNumeros :: IO [Int]
lerNumeros = do
    putStr "Digite um número: "
    numero <- readLn :: IO Int 
    if numero == 0
        then return []
        else do
            restante <- lerNumeros
            return (numero : restante)

somaNumeros :: [Int] -> Int
somaNumeros = sum 