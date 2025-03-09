numRaizes :: (Floating a, Ord a) => a -> a -> a -> IO ()
numRaizes a b c |delta > 0 = putStrLn "Duas raizes reais"
                |delta == 0 = putStrLn "Uma raiz real"
                |delta < 0 = putStrLn "Nenhuma raiz real"
    where
        delta = b^2 -4*a*c