# Game2048
2048 famous game reproduced with the chance to choose a initial configuration written in a txt file read by the program.
If the input file can not be read by the program the game will start with the initial configuration:

0 0 0 0

0 0 0 0

0 0 0 0

0 0 0 2

Moves allowed are :

'a' : merging everything left

's' : merging everything down

'd' : merging everything right

'w' : merging everything up

If the program reads an invalid input character it will print the sentence: "enter a valid move: ".
If the input character is valid but the move does not cause a merge due to the position of the numbers in the grid the program will not print again the grid with a '2' added in a random position, but it will just print again the sentence: "enter a move: ".
If the input character is valid and generates a  merge the program will print the merged grid with a '2' added in a random position and the sentence: "enter a move: ", in order to continue the game.
Finally if no moves are allowed the program will print the sentence: "GAME OVER" and quit.
