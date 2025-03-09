module Main where
main :: IO()
main = do   
    insereLados

insereLados = do
    lado1 <- prompt "Primeiro Lado"
    lado2 <- prompt "Segundo Lado"
    lado3 <- prompt "Terceiro Lado"
    if validaTriangulo lado1 lado2 lado3
        then somaLados lado1 lado2 lado3
        else do putStrLn "Triangulo inválido"
                insereLados

validaTriangulo :: (Ord a, Num a) => a -> a -> a-> Bool
validaTriangulo a b c =
    a > 0 && b > 0 && c > 0 &&
    a + b > c &&
    b + c > a &&
    c + a > b 

somaLados lado1 lado2 lado3 = putStrLn("Soma lados : " ++ show(lado1 +lado2 +lado3))

prompt msg = 
    do putStr msg
       readLn :: IO Int 