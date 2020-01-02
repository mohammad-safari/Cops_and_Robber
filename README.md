                                         Cops_and_Robber(version_1)


This game is my(Mohammad Safari) midterm project of first term in Amirkabir University of Technology and the first version, completely performs in C. In this version of game, in a two dimensional environment there will be some police stations (between 0 and 10) with some cops (between 0 and 10) in connection to each other (in each station) searching for one robber with some simple rules.

The process is as such, that it first gets data about dimension size and police stations. Then the board will be initialized with cops (showed by digits from 1 to 9 and highlighted with blue) and the robber(showed by character R and highlighted with red) accidentally and board will be printed at time zero(in each time first cops can move to one of eight neighbor houses or stay there and then the robber does so)!
Each cop can see up to two houses around it's (houses highlighted with green) and reports to other co-station cops if there was any robber, and then they (co-station cops) will move toward the -last- report location. If there was not any report to one station all cops of the station move random!

Also the robber can look around (up to two houses around it's) and decide where is better to run away! Actually finds a house which is out of cops' sight, or if not possible, not to stand exactly beside a cop(because this made the game finish)!, and in the worst situtation, if not any of that two possible, inevitably start moving random or statying there!;D

This will continue until a cop stands exactly beside the robber and then the robber will be caught on next move but the board will be printed (only near cop moves)and game will head to menu asking you to start a new game or changing dimension sizes or police numbers (both stations and each stations cops) or exiting the game!

p.s: this game was compiled by gcc therefore I needed to rewrite getch function! consider if you want to compile by mvc (you can also use getchar or scanf if you decide! - refer to main.c: line 12) , and under Linux then you may change command 'clear' to 'cls' under Windows OS(refer to main.c: line 10).ِYet, to Experience Best Performance Run on LINUX or MAC.
