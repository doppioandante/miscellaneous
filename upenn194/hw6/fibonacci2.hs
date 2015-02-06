{-# LANGUAGE FlexibleInstances #-}
{-# OPTIONS_GHC -fno-warn-missing-methods #-}
import Stream

x :: Stream Integer
x = Stream 0 (Stream 1 (streamRepeat 0))

instance Num (Stream Integer) where
    fromInteger n = Stream n (streamRepeat 0)

    negate = streamMap (Prelude.negate)

    (+) (Stream a as) (Stream b bs) = Stream (a+b) (as + bs)

    (*) (Stream a0 a') b@(Stream b0 b') = Stream (a0*b0) ((streamMap (*a0) b') + (a' * b))

instance Fractional (Stream Integer) where
    (/) a@(Stream a0 a') b@(Stream b0 b') =
	let q = a / b
	in Stream (div a0 b0) (streamMap (`div` b0) (a' - q*b'))

fibs3 :: Stream Integer
fibs3 = x/(1-x-x^2)

data Matrix = Matrix Integer Integer Integer Integer

instance Num Matrix where
    (*) (Matrix a b c d) (Matrix e f g h) =
	Matrix (a*e+b*g) (a*f+b*h) (c*e+d*g) (c*f+d*h)

fib4 :: Integer -> Integer
fib4 n = 
    let (Matrix _ fn _ _) = (Matrix 1 1 1 0) ^ n
    in fn
