module Main where
main :: IO()
main = do
    putStrLn "Classe eleitoral"
    putStrLn "----------------------------"
    putStr "Digite a idade da pessoa: "
    x <- readLn :: IO Int 
    verificaIdade x

verificaIdade :: Int -> IO()
verificaIdade x |x < 16 = putStrLn "Não eleitor" 
                |x >= 16 && x < 18 || x >= 65 = putStrLn "Eleitor facultativo"
                |otherwise = putStrLn "Eleitor obrigatório"