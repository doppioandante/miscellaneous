{-# LANGUAGE TypeSynonymInstances #-}
{-# LANGUAGE FlexibleInstances #-}
import ExprT
import Parser (parseExp)
import qualified StackVM
import qualified Data.Map as M
import Control.Applicative

eval :: ExprT -> Integer
eval (Lit x) = x
eval (Add e1 e2) = (eval e1) + (eval e2)
eval (Mul e1 e2) = (eval e1) * (eval e2)

evalStr :: String -> Maybe Integer
evalStr = fmap eval . parseExp Lit Add Mul

class Expr a where
    lit :: Integer -> a
    add :: a -> a -> a
    mul :: a -> a -> a

instance Expr ExprT where
    lit = Lit
    add = Add
    mul = Mul

instance Expr Integer where
    lit = id
    add = (+)
    mul = (*)

instance Expr Bool where
    lit = (>0)
    add = (||)
    mul = (&&)

newtype MinMax = MinMax Integer deriving (Eq, Show)

instance Expr MinMax where
    lit = MinMax
    add (MinMax a) (MinMax b) = MinMax $ max a b
    mul (MinMax a) (MinMax b) = MinMax $ min a b

newtype Mod7 = Mod7 Integer deriving (Eq, Show)

instance Expr Mod7 where
    lit x = Mod7 (mod7 x)
    add (Mod7 a) (Mod7 b) = Mod7 $ mod7 $ a + b
    mul (Mod7 a) (Mod7 b) = Mod7 $ mod7 $ a * b

mod7 = (`mod` 7)

testExp :: Expr a => String -> Maybe a
testExp = parseExp lit add mul

testInteger = testExp :: String -> Maybe Integer
testBool = testExp :: String -> Maybe Bool
testMinMax = testExp :: String -> Maybe MinMax
testMod7 = testExp :: String -> Maybe Mod7

instance Expr StackVM.Program where
    lit x = [StackVM.PushI x]
    add x1 x2 = x1 ++ x2 ++ [StackVM.Add]
    mul x1 x2 = x1 ++ x2 ++ [StackVM.Mul]

compile :: String -> Maybe StackVM.Program
compile = parseExp lit add mul


class HasVars a where
    var :: String -> a

data VarExprT = VLit Integer
              | VAdd VarExprT VarExprT
	      | VMul VarExprT VarExprT
	      | VVar String
    deriving (Eq, Show)

instance Expr VarExprT where
    lit = VLit
    add = VAdd
    mul = VMul

instance HasVars VarExprT where
    var = VVar

instance HasVars (M.Map String Integer -> Maybe Integer) where
    var = M.lookup

instance Expr (M.Map String Integer -> Maybe Integer) where
    lit = const . return -- const . Just
    add = liftA2 (liftA2 (+))
    mul = liftA2 (liftA2 (*))

withVars :: [(String, Integer)]
         -> (M.Map String Integer -> Maybe Integer)
	 -> Maybe Integer
withVars vs exp = exp $ M.fromList vs
