module Main (main) where
main :: IO ()
main = do 
    putStrLn "digite dois números: "
    x <- readLn
    y <- readLn
    let s = x + y
    putStrLn ("soma: " ++ show s)