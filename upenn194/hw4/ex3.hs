import Data.List ((\\))

xor :: [Bool] -> Bool
xor = foldr flipBool False
    where 
	flipBool x False = x
	flipBool x True = not x

map' :: (a -> b) -> [] a -> [] b
map' f = foldr ((:) . f) []

-- foldr :: (a -> b -> b) -> b -> [a] -> b
myFoldl :: (a -> b -> a) -> a -> [b] -> a
myFoldl f base xs = foldr (flip f) base xs

cartProd xs ys = [(x,y) | x <- xs, y <- ys]

sundaramSieve :: Integer -> [Integer]
sundaramSieve = undefined
--sundaramSieve = map ((+1) . (*2)) . ((flip (\\)) (map (\(i, j) -> i+j+2*i*j) $ cartProd [1..] [1..]))
