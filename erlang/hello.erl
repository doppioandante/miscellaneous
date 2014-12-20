-module(hello).
-export([get_message/1]).

get_message(Person) ->
    "Hello " ++ Person.
