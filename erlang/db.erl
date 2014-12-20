-module(db).
-export([new/0, destroy/1, write/3, delete/2, read/2, match/2]).

new() -> {[], []}.

destroy(_Db) -> ok.

write(Key, Element, Db) -> write_acc(Key, Element, Db, {[], []}).

write_acc(Key, Element, {[], []}, {RKeys, RElements}) ->
    {[Key|RKeys], [Element|RElements]};

write_acc(Key, Element, {[Key|Keys], [_|Elements]}, {RKeys, RElements}) ->
    {[Key|Keys] ++ RKeys, [Element|Elements] ++ RElements};

write_acc(Key, Element, {[AKey|Keys], [AElement|Elements]}, {RKeys, RElements}) ->
    write_acc(Key, Element, {Keys, Elements}, {[AKey|RKeys], [AElement|RElements]}).

delete(Key, Db) -> delete_acc(Key, Db, {[], []}).

delete_acc(_Key, {[], []}, Acc) -> Acc;

delete_acc(Key, {[Key|Keys], [_|Elements]}, {AccKeys, AccElements}) ->
    {Keys ++ AccKeys, Elements ++ AccElements};

delete_acc(Key, {[AKey|Keys], [AElement|Elements]}, {AccKeys, AccElements}) ->
    delete_acc(Key, {Keys, Elements}, {[AKey|AccKeys], [AElement|AccElements]}).

read(_Key, {[], []}) -> {error, instance};
read(Key, {[Key|_], [Element|_]}) ->
    {ok, Element};
read(Key, {[_|Keys], [_|Elements]}) ->
    read(Key, {Keys, Elements}).

match(Element, Db) -> match_acc(Element, Db, []).

match_acc(_Element, {[], []}, Acc) -> Acc;
match_acc(Element, {[Key|Keys], [Element|Elements]}, Acc) -> 
    match_acc(Element, {Keys, Elements}, [Key|Acc]);
match_acc(Element, {[_|Keys], [_|Elements]}, Acc) ->
    match_acc(Element, {Keys, Elements}, Acc).
