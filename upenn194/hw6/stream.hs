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

interleaveStreams :: Stream a -> Stream a -> Stream a
interleaveStreams (Stream v1 nextStream) stream2 = 
    Stream v1 (interleaveStreams stream2 nextStream) 

-- all numbers are divided by 2^0, but even ones are divided by 2^1
-- all even numbers are divided by 2^1, but every two of them are divided by 2^2
-- ...
-- Still I'm not so sure why this works. But I wrote it!
ruler :: Stream Integer
ruler = interleaveStreams (streamRepeat 0) (streamMap (+1) ruler)
