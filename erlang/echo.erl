-module(echo).
-export([start/0, print/1, stop/0, loop/0]).

start() ->
    register(echo_server, spawn(?MODULE, loop, [])),
    ok.

loop() ->
    receive
	{print, Msg} -> io:format(Msg), loop();
	stop -> ok
    end.

print(Msg) ->
    echo_server ! {print, Msg},
    ok.

stop() ->
    echo_server ! stop,
    ok.
