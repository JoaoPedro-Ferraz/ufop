module Main where
main :: IO ()
main = do
    putStrLn "Digite um número: "
    x <-readLn :: IO Int 
    print (fatorial x)

fatorial :: Int -> Int
fatorial x | x == 0 = 1
fatorial x = fatorial x * (x-1)