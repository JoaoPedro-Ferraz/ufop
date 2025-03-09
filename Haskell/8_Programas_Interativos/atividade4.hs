module Main where
import Text.Printf(printf)
main :: IO ()
main = do
    putStrLn "Digite a temperatura em Fahrenheit: "
    x <- readLn :: IO Double
    printf " A temperatura, em Celsius é:%.2f\n" (converteTemperatura x)

converteTemperatura :: Double -> Double
converteTemperatura x = 5/9 * (x -32)