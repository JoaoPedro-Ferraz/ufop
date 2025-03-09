doisPrimeiros :: [a] -> [a]
doisPrimeiros = take 2 

tresUltimos :: [a] -> [a]
tresUltimos x = reverse(take 3(reverse x))