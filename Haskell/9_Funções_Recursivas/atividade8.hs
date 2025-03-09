module Main where 
main :: IO ()
main = do
    let lista = [0, 2 ..30]
    putStr (show lista)