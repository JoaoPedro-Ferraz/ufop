calculaMelhora :: [Int] -> [Int] -> String
calculaMelhora x y = 
    if a < b then "Melhorou" else "Piorou"
    where
        a = sum x
        b = sum y