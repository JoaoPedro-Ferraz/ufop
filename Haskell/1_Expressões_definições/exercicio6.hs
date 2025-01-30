ladosTriangulo :: Float -> Float -> Float -> Bool
ladosTriangulo a b c = 
    a + b > c &&
    b + c > a &&
    c + a > c

