precoRetrato :: Integer -> String -> Double 
precoRetrato pessoas dia = precoFinal
    where 
        precoBase   
            |pessoas == 1 = 100.0 
            |pessoas == 2 = 130.0
            |pessoas == 3 = 150.0
            |pessoas == 4 = 165.0
            |pessoas == 5 = 175.0
            |pessoas == 6 = 180.0
            |otherwise = 185.0
        precoFinal
            |dia == "sábado" || dia == "domingo" = precoBase * 1.20
            |otherwise = precoBase
 