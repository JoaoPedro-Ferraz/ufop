metade :: [a] -> ([a], [a])
metade xs = splitAt (length xs `div` 2) xs