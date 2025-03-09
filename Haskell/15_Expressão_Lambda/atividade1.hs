module Main where
main :: IO ()
main = do
    x <- fmap read getLine
    y <- fmap read getLine
    putStr (show (calculaProduto x y))

calculaProduto :: Int -> Int -> Int
calculaProduto m n |m+1 >= n = 1
                   |otherwise =  (m+1) * calculaProduto (m + 1) n 