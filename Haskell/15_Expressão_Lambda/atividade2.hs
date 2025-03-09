module Main where
main :: IO ()
main = do
    insereLados

insereLados :: IO ()
insereLados = do
           putStrLn "Digite os lados do triangulo"
           x <- fmap read getLine
           y <- fmap read getLine
           z <- fmap read getLine
           if verificaLados x y z 
            then do
                putStrLn "Triangulo Valido" 
                calculaArea x y z
            else do
                putStrLn "Triangulo Invalido"
                insereLados

    
verificaLados :: Float -> Float -> Float -> Bool
verificaLados x y z |x < 0 = False
                  |y < 0 = False
                  |z < 0 = False
                  |x + y < z = False
                  |y + z < x = False
                  |x + z < y = False
                  |otherwise = True

calculaArea :: Float -> Float -> Float -> Float
calculaArea a b c =  (b * h) / 2
    where
     cosA = (b^2 + c^2 - a^2) / (2 * b *c)
     sinA = sqrt(1-cosA^2)
     h = c * sinA