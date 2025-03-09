module Main where
main :: IO ()
main = do
    putStrLn "Digite 3 números"
    a <- prompt "Primeiro número: "
    b <- prompt "Segundo número: "
    c <- prompt "Terceiro número: "
    let resposta = a * b * c
    print resposta

prompt msg = do
    putStr msg 
    readLn :: IO Float