ultimo :: [a] -> a
ultimo[x] = x
ultimo(_:xs) = ultimo xs 