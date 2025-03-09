module Main where
main :: IO()
main = do
    putStrLn "Análise de crédito"
    putStrLn "----------------------------------"
    x <- readLn :: IO Float 
    y <- readLn :: IO Float
    putStrLn ("Salario bruto: " ++ show x)
    putStrLn ("Valor da prestação" ++ show y)
    verificaCredito x y

verificaCredito :: Float -> Float -> IO ()
verificaCredito x y|y > x * 0.3 = putStrLn "O emprestimo não pode ser consedido"
                   |otherwise = putStrLn "O emprestimo pode ser consedido"