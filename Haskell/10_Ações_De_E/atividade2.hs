module Main where
main :: IO ()
main = do
    num <- leituraNumeros 
    let x = fromIntegral (length num)
    let resposta = (/) (sum num)  x
    print resposta
    
    

leituraNumeros :: IO [Double]
leituraNumeros = do
    num <- readLn :: IO Double 
    if num < 0
        then return []
        else do
            resto <- leituraNumeros 
            return (num : resto)