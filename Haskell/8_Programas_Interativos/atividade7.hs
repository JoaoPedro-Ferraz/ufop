module Main where
main :: IO ()
main = do
    putStrLn "-------------------------------"
    putStrLn "Opções"
    putStrLn "-------------------------------"
    putStrLn "1. Imposto"
    putStrLn "2. Novo salário"
    putStrLn "3. Classificação"
    putStrLn "-------------------------------"
    putStr "Digite a opção desejada"
    x <- readLn :: IO Float
    menuOpcoes x

menuOpcoes :: Float -> IO ()
menuOpcoes x | x == 1 = do
    putStrLn "Calculo do imposto: "
    putStr "Digite o salário: "
    x <- readLn :: IO Float
    putStrLn ("Imposto calculado: " ++ show(opcaoUm x))
             | x == 2 = do
    putStrLn "Calculo do novo salário: "
    putStr "Digite o salário: "
    putStrLn ("Novo salário: " ++ show (opcaoDois x))
             | x == 3 = do
    putStrLn "Classificação do salário: "
    putStr "Digite o salário: "
    putStr "Classificação obtida: "
    opcaoTres x
             |otherwise = putStrLn "Opção inválida"

opcaoUm :: Float -> Float
opcaoUm x |x < 500.00 = x * 0.05
          |x >= 500.00 && x > 850.00 = x * 0.1
          |otherwise = x * 0.15  

opcaoDois :: Float -> Float
opcaoDois x |x > 1500.00 = x + 25.00
            |x >= 750.00 && x <= 1500.00 = x + 50.00 
            |x >= 450.00 && x < 750 = x + 100.00
            |otherwise = x + 100.00

opcaoTres :: Float -> IO ()
opcaoTres x = do
    putStrLn "Classificação do salário: "
    putStrLn "Digite o salário: "
    x <- readLn :: IO Float 
    if x <= 750.00 then
        putStrLn "Mal remunerado"
        else 
            putStrLn "Bem remunerado"
