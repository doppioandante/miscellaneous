-- SOLUTION TO http://www.seas.upenn.edu/~cis194/spring13/hw/01-intro.pdf

toDigitsRev :: Integer -> [Integer]
-- assuming n >= 0
toDigitsRev n = (n `mod` 10) : toDigitsRev' (n `div` 10)
toDigitsRev' 0 = []
toDigitsRev' n = toDigitsRev n

toDigits :: Integer -> [Integer]
toDigits = reverse . toDigitsRev

doubleEveryOther :: [Integer] -> [Integer]
doubleEveryOther list = doubleEveryOther' ((`mod` 2) . length $ list) list

doubleEveryOther' _ [] = []
doubleEveryOther' step (x:xs) =
    let newX = if step == 0 then 2*x else x
    in
	newX : doubleEveryOther' ((step + 1) `mod` 2) xs

sumDigits :: [Integer] -> Integer
sumDigits = (foldl (+) 0) . concat . (map toDigits)

validate :: Integer -> Bool
validate = (== 0) . (`mod` 10) . sumDigits . doubleEveryOther . toDigits

