module Main where 

data ShopItem = ShopItem{
    nome :: String, 
    quantidade :: Int, 
    valor :: Double 
} deriving (Show)

main :: IO() 
main = do
    compras <- lerItens
    putStr "Total Compras: "
    print (totalCompra compras)


adicionarItem = do 
    putStr "Digite o nome do produto: " 
    nome <- getLine 
    putStr "digite a quantidade: " 
    quant <- readLn :: IO Int 
    putStr "Digite o valor: " 
    valor <- readLn :: IO Double 
    return (ShopItem nome quant valor)

lerItens = do 
    putStr "deseja adicionar um item? " 
    x <- getLine 
    if x == "s"
        then do 
            item <- adicionarItem 
            itens <- lerItens 
            return (item : itens) 
        else 
            return []

totalCompra compras = sum [valor item * fromIntegral (quantidade item) | item <- compras]
