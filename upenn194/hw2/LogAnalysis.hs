module LogAnalysis
where

import Log

parseMessage :: String -> LogMessage
parseMessage str@(x:xs) = 
    case x of
	'E' -> parseErrorMessage (words xs)
	'I' -> parseInfoMessage (words xs)
	_   -> Unknown str

parseErrorMessage :: [String] -> LogMessage
parseErrorMessage xs =
    let 
	errorCode = read $ xs !! 0
	timeStamp = read $ xs !! 1
	message = unwords $ drop 2 $ xs
    in
	LogMessage (Error errorCode) timeStamp message

parseInfoMessage :: [String] -> LogMessage
parseInfoMessage xs =
    let
	timeStamp = read $ xs !! 0 
	message = unwords $ drop 1 $ xs
    in
	LogMessage Info timeStamp message

parse :: String -> [LogMessage]
parse = (map parseMessage) . lines

insert :: LogMessage -> MessageTree -> MessageTree
insert msg Leaf = Node Leaf msg Leaf
insert (Unknown _) tree = tree
insert msg@(LogMessage _ timeStamp _) (Node leftChild logMsg@(LogMessage _ nodeTimeStamp _) rightChild) =
    if timeStamp > nodeTimeStamp 
	then Node leftChild logMsg (insert msg rightChild)
	else Node (insert msg leftChild) logMsg rightChild

build :: [LogMessage] -> MessageTree
build = foldr insert Leaf

inOrder :: MessageTree -> [LogMessage]
inOrder Leaf = []
inOrder (Node left msg right) =
    inOrder left ++ [msg] ++ inOrder right

whatWentWrong :: [LogMessage] -> [String]
whatWentWrong =
    map getMsg . filter highSeverity . inOrder . build
    where
	getMsg (LogMessage _ _ msg) = msg
	highSeverity (LogMessage (Error severity) _ _) = severity >= 50
	highSeverity _ = False
