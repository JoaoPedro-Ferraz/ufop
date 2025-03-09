module Main where
main :: IO ()
main = do
    putStrLn "Digite a altura:"
    altura <- readLn :: IO Float
    putStrLn "Digite o sexo:" 
    sexo <- getLine
    let peso = calculaPeso altura sexo
    print peso

calculaPeso :: Float -> String -> Float
calculaPeso a s   
    |s == "feminino" = 62.1 * a - 44.7
    |s == "masculino" = 72.7 * a - 58
    |otherwise = error "Sexo invalido"