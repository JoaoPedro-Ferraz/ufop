module Main where 
main :: IO () 
main = do
    putStrLn "Digite o divisor e o dividendo"
    putStr "Divisor: "
    x <- readLn :: IO Int
    putStr "Dividendo: "
    y <- readLn :: IO Int  
    let z = calculaDivisaoAux x y
    putStrLn ("Quociente: " ++ show z)
    putStrLn ("Resto: " ++ show (calculaResto x (y * z)))
    
calculaDivisaoAux :: Int -> Int -> Int
calculaDivisaoAux x y = calculaDivisao x y 1

calculaDivisao :: Int -> Int -> Int -> Int
calculaDivisao x y z |y > x = 0
                     |x - (y * z) == 0 = z
                     |x - (y * z) /= 0 && z * y > x = z-1
calculaDivisao x y z = calculaDivisao x y (z + 1)

calculaResto :: Int -> Int -> Int 
calculaResto x y = x - y