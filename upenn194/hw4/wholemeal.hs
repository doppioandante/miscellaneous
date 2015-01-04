fun1' :: [Integer] -> Integer
fun1' = foldl (*) 0 . map (\x -> x - 2) . filter even

fun2' :: Integer -> Integer
fun2' = sum . takeWhile (\x -> x /= 1) . iterate collatz
    where
	collatz n 
	    | even n = n `div` 2
	    | otherwise = 3*n + 1
