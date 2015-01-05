data Stream a = Stream a (Stream a)
    deriving (Eq)

streamToList :: Stream a -> [a]
streamToList (Stream value next) = value : streamToList next

instance Show a => Show (Stream a) where
    show = show . take 21 . streamToList

streamRepeat :: a -> Stream a
streamRepeat val = Stream val (streamRepeat val)

streamMap :: (a -> b) -> Stream a -> Stream b
streamMap f (Stream value next) = Stream (f value) (streamMap f next)

streamFromSeed :: (a -> a) -> a -> Stream a
streamFromSeed rule seed = Stream seed (streamFromSeed rule (rule seed))

nats :: Stream Integer
nats = streamFromSeed (+1) 0

