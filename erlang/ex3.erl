-module(ex3).
-export([sum/1, sum/2, create/1, create_reverse/1, print_integers/1, print_even_integers/1, filter/2, reverse/1, concatenate/1, flatten/1, quicksort/1, mergesort/1]).

sum(0) -> 0;
sum(N) -> N + sum(N-1).

sum(N, M) when N =< M ->
    sum(M) - sum(N) + N;
sum(_N, _M) -> exit("Bad arguments").

create_reverse(0) -> [];
create_reverse(N) -> [N|create_reverse(N-1)].

create(N) -> lists:reverse(create_reverse(N)).

print_integers(N) ->
    print_elements(create(N)).

print_elements([]) -> ok;
print_elements([H|T]) ->
    io:format("Number:~p~n", [H]),
    print_elements(T).

print_even_integers(N) -> print_elements(filter_even(create(N))).

filter_even(List) -> filter_even_acc(List, []).

filter_even_acc([], Result) -> Result;
filter_even_acc([Head|Tail], Result) when Head rem 2 == 0 ->
    filter_even_acc(Tail, Result ++ [Head]);
filter_even_acc([_Head|Tail], Result) -> filter_even_acc(Tail, Result).

filter([], _) -> [];
filter([Head|Tail], Value) when Head =< Value -> [Head|filter(Tail, Value)];
filter([_Head|Tail], Value) -> filter(Tail, Value).

reverse(Array) -> reverse_acc(Array, []).
reverse_acc([], Acc) -> Acc;
reverse_acc([H|T], Acc) -> reverse_acc(T, [H|Acc]).

concatenate(Lists) -> concatenate_acc(Lists, []).
concatenate_acc([], Acc) -> Acc;
concatenate_acc([H|T], Acc) -> concatenate_acc(T, Acc ++ H).

flatten([]) -> [];
flatten([List]) -> flatten(List);
flatten([H|T]) -> concatenate([flatten(H), flatten(T)]);
flatten(E) -> [E].

quicksort([]) -> [];
quicksort([Pivot|Tail]) ->
    quicksort(filter_less_equal_than(Pivot, Tail)) ++ [Pivot] ++ quicksort(filter_greater_than(Pivot, Tail)).

filter_less_equal_than(Element, List) -> filter(List, Element).

filter_greater_than(_, []) -> [];
filter_greater_than(Element, [Head|Tail]) when Head > Element -> [Head|filter_greater_than(Element, Tail)];
filter_greater_than(Element, [_Head|Tail]) -> filter_greater_than(Element, Tail).

mergesort(List) when length(List) =< 1 -> List;
mergesort(List) ->
    {Left, Right} = lists:split(length(List) div 2, List),
    merge(mergesort(Left), mergesort(Right)).

merge([], Right) -> Right;
merge(Left, []) -> Left;
merge(Left, Right) ->
    {[E1|TLeft], [E2|TRight]} = {Left, Right},
    if
	E1 =< E2 -> [E1|merge(TLeft, Right)];
	true	 -> [E2|merge(Left, TRight)]
    end.
