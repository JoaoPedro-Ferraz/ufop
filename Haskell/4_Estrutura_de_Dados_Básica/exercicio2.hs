primeiros :: [a] -> [a]
primeiros [] = []
primeiros [x] = []
primeiros (x:xs) = x : primeiros xs