module Main where
import System.IO (hSetBuffering, stdout, BufferMode(NoBuffering))
main :: IO()
main = do
    hSetBuffering stdout NoBuffering
    trabLab <- prompt "Nota Laboratório"
    avalSem <- prompt "avalição Semestral"
    examFinal <- prompt "Exame Final"
    let c = calculaConceito trabLab avalSem examFinal
    if c == 'F'
        then putStrLn "Entrada Invalida"
        else print c

calculaConceito :: Float -> Float -> Float -> Char
calculaConceito a b c
        |media >= 0.0 && media < 5.0 = 'E'
        |media >= 5.0 && media < 6.0 = 'D'
        |media >= 6.0 && media < 7.0 = 'C'
        |media >= 7.0 && media < 8.0 = 'B'
        |media >= 8.0 && media <= 10.0 = 'A'
        |otherwise = 'F'
    where
        media = (a + b + c) / 2
prompt msg =
    do 
        putStr msg
        readLn :: IO Float