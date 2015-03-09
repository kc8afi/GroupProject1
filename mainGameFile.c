/*
Austin Dhiraj Dave
CS240
Group Project 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>

struct Enemy
{
	int power;
	char name[10];
	char array[10][11];
};

void PrintMaze(char array[][22], int rows, int cols, WINDOW *window);
void StoreMaze(char array[][22], int rows, int cols, FILE *file);
void PrintEnemy(struct Enemy in, int rows, int cols, WINDOW *window);
void StoreEnemy(struct Enemy* in, int rows, int cols, FILE *file);
int MazeTraversal(char array[][22], int rows, int cols, int timeLimit, WINDOW *window, int userLevel);
int Random();
int DiceRoll(WINDOW *window, struct Enemy in);
void StartMenu(WINDOW *window);
int MazeCall(WINDOW *mazeWindow, int mazeRows, int mazeCols, int timeLimit[10], int userLevel, char mazeOne[][22], char mazeTwo[][22], char mazeThree[][22], char mazeFour[][22], char mazeFive[][22], char mazeSix[][22], char mazeSeven[][22], char mazeEight[][22], char mazeNine[][22], char mazeTen[][22]);


int main()
{
	int mazeCols = 22;
	int mazeRows = 21;
	int enemyCols = 11;
	int enemyRows = 10;
	//Open up the file, read in the text file data into an array, print the array, and close the file as we won't need it again
	FILE *file1 = fopen("maze1.txt", "r");
	char mazeOne[mazeRows][mazeCols];
	StoreMaze(mazeOne, mazeRows, mazeCols, file1);
	fclose(file1);
	FILE *file2 = fopen("maze2.txt", "r");
	char mazeTwo[mazeRows][mazeCols];
	StoreMaze(mazeTwo, mazeRows, mazeCols, file2);
	fclose(file2);
	FILE *file3 = fopen("maze3.txt", "r");
	char mazeThree[mazeRows][mazeCols];
	StoreMaze(mazeThree, mazeRows, mazeCols, file3);
	fclose(file3);
	FILE *file4 = fopen("maze4.txt", "r");
	char mazeFour[mazeRows][mazeCols];
	StoreMaze(mazeFour, mazeRows, mazeCols, file4);
	fclose(file4);
	FILE *file5 = fopen("maze5.txt", "r");
	char mazeFive[mazeRows][mazeCols];
	StoreMaze(mazeFive, mazeRows, mazeCols, file5);
	fclose(file5);
	FILE *file6 = fopen("maze6.txt", "r");
	char mazeSix[mazeRows][mazeCols];
	StoreMaze(mazeSix, mazeRows, mazeCols, file6);
	fclose(file6);
	FILE *file7 = fopen("maze7.txt", "r");
	char mazeSeven[mazeRows][mazeCols];
	StoreMaze(mazeSeven, mazeRows, mazeCols, file7);
	fclose(file7);
	FILE *file8 = fopen("maze8.txt", "r");
	char mazeEight[mazeRows][mazeCols];
	StoreMaze(mazeEight, mazeRows, mazeCols, file8);
	fclose(file8);
	FILE *file9 = fopen("maze9.txt", "r");
	char mazeNine[mazeRows][mazeCols];
	StoreMaze(mazeNine, mazeRows, mazeCols, file9);
	fclose(file9);
	FILE *file10 = fopen("maze10.txt", "r");
	char mazeTen[mazeRows][mazeCols];
	StoreMaze(mazeTen, mazeRows, mazeCols, file10);
	fclose(file10);

	//Read in enemy graphics files
	FILE *enemy1 = fopen("enemy1.txt", "r");
	struct Enemy enemyOne;
	StoreEnemy(&enemyOne, enemyRows, enemyCols, enemy1);
	fclose(enemy1);
	FILE *enemy2 = fopen("enemy2.txt", "r");
	struct Enemy enemyTwo;
	StoreEnemy(&enemyTwo, enemyRows, enemyCols, enemy2);
	fclose(enemy2);
	FILE *enemy3 = fopen("enemy3.txt", "r");
	struct Enemy enemyThree;
	StoreEnemy(&enemyThree, enemyRows, enemyCols, enemy3);
	fclose(enemy3);
	FILE *enemy4 = fopen("enemy4.txt", "r");
	struct Enemy enemyFour;
	StoreEnemy(&enemyFour, enemyRows, enemyCols, enemy4);
	fclose(enemy4);
	FILE *enemy5 = fopen("enemy5.txt", "r");
	struct Enemy enemyFive;
	StoreEnemy(&enemyFive, enemyRows, enemyCols, enemy5);
	fclose(enemy5);
	FILE *enemy6 = fopen("enemy6.txt", "r");
	struct Enemy enemySix;
	StoreEnemy(&enemySix, enemyRows, enemyCols, enemy6);
	fclose(enemy6);
	FILE *enemy7 = fopen("enemy7.txt", "r");
	struct Enemy enemySeven;
	StoreEnemy(&enemySeven, enemyRows, enemyCols, enemy7);
	fclose(enemy7);
	FILE *enemy8 = fopen("enemy8.txt", "r");
	struct Enemy enemyEight;
	StoreEnemy(&enemyEight, enemyRows, enemyCols, enemy8);
	fclose(enemy8);
	FILE *enemy9 = fopen("enemy9.txt", "r");
	struct Enemy enemyNine;
	StoreEnemy(&enemyNine, enemyRows, enemyCols, enemy9);
	fclose(enemy9);
	FILE *enemy10 = fopen("enemy10.txt", "r");
	struct Enemy enemyTen;
	StoreEnemy(&enemyTen, enemyRows, enemyCols, enemy10);
	fclose(enemy10);

	//Initialize the screen, set the cursor to invisible, auto return values with getch, allow special characters, and don't show keyboard input
	initscr();
	curs_set(0);
	noecho();
	cbreak();

	WINDOW* mazeWindow = NULL;
	WINDOW* enemyWindow = NULL;
	int screenHeight = getmaxy(stdscr);
	int screenWidth = getmaxy(stdscr);
	mazeWindow = newwin(screenHeight, screenWidth, 0, 0);
	enemyWindow = newwin(screenHeight, screenWidth, 0, screenWidth);
	keypad(mazeWindow, TRUE);
	wrefresh(stdscr);
	StartMenu(mazeWindow);
	//Start main game loop
	int userLevel = 1;
	int timeLimit[10] = {50, 47, 44, 41, 38, 35, 32, 29, 26, 23};
	int success = 0;
	while (1)
	{
		success = MazeCall(mazeWindow, mazeRows, mazeCols, timeLimit, userLevel, mazeOne, mazeTwo, mazeThree, mazeFour, mazeFive, mazeSix, mazeSeven, mazeEight, mazeNine, mazeTen);
		if (success != 0)
		{
			wprintw(mazeWindow, "You made it through the maze in time!");
			success = EnemyCall(enemyWindow, enemyRows, enemyCols, userLevel, enemyOne, enemyTwo, enemyThree, enemyFour, enemyFive, enemySix, enemySeven, enemyEight, enemyNine, enemyTen);
			wrefresh(enemyWindow);
			wprintw(enemyWindow, "\n(press any key to continue)\n");
			wgetch(enemyWindow);
			if (success == 0)
			{
				break;
			}
			else
			{
				userLevel++;
			}
		}
		else
		{
			wprintw(mazeWindow, "You didn't make it in time!\n(press any key to continue)");
			wgetch(mazeWindow);
			break;
		}
		if (userLevel > 10)
		{
			break;
		}
		wclear(mazeWindow);
		wclear(enemyWindow);
		wrefresh(mazeWindow);
		wrefresh(enemyWindow);
	}
	wclear(mazeWindow);
	wclear(enemyWindow);
	wrefresh(mazeWindow);
	wrefresh(enemyWindow);
	if (success != 0)
	{
		int counter = 0;
		while (counter < 10)
		{
			wprintw(mazeWindow, "YOU WON THE GAME!\n");
			wprintw(enemyWindow, "YOU WON THE GAME!\n");
			counter++;
		}
	}
	else
	{
		int counter = 0;
		while (counter < 10)
		{
			wprintw(mazeWindow, "YOU LOST THE GAME!\n");
			wprintw(enemyWindow, "YOU LOST THE GAME!\n");
			counter++;
		}
	}
	wprintw(mazeWindow, "\n(press any key to quit the game)\n");
	wprintw(enemyWindow, "\n(press any key to quit the game)\n");
	//wait to conclude the game until the user enters in a key, then delete the windows
	wgetch(mazeWindow);
	delwin(mazeWindow);
	delwin(enemyWindow);
	endwin();
	return 0;

}

void PrintMaze(char array[][22], int rows, int cols, WINDOW *window)
{
	//simply go through the 2d array one element at a time and print that element to a window
	int counter1 = 0;
	while (counter1 < rows)
	{
		int counter2 = 0;
		while (counter2 < cols)
		{
			wprintw(window, "%c", array[counter1][counter2]);
			counter2++;
		}
		counter1++;
	}
	wprintw(window, "\n\n");
	wrefresh(window);
}

void StoreMaze(char array[][22], int rows, int cols, FILE *file)
{
	//go through a maze .txt file and store the values in an array
	int counter1 = 0;
	while (counter1 < rows)
	{
		int counter2 = 0;
		while (counter2 < cols)
		{
			array[counter1][counter2] = fgetc(file);
			counter2++;
		}
		counter1++;
	}
}

void PrintEnemy(struct Enemy in, int rows, int cols, WINDOW *window)
{
	//print out the enemy's power, name, and graphics array
	wprintw(window, "Enemy level: %d\n", in.power);
	int counter1 = 0;
	wprintw(window, "Name: ");
	while (counter1 < 10)
	{
		wprintw(window, "%c", in.name[counter1]);
		counter1 ++;
	}
	counter1 = 0;
	while (counter1 < rows)
	{
		int counter2 = 0;
		while (counter2 < cols)
		{
			wprintw(window, "%c", in.array[counter1][counter2]);
			counter2++;
		}
		counter1++;
	}
	wrefresh(window);
	wprintw(window, "\n\n");
}

void StoreEnemy(struct Enemy* in, int rows, int cols, FILE *file)
{
	//read in the enemy text file and store the first int as the enemy's power, the next bit of text as it's name, and the rest as the 2d graphic array
	in->power = fgetc(file) - '0';
	in->power = in->power +5;//add 5 to the level to increase difficulty
	fgets(in->name, 11, file);
	int counter1 = 0;
	while (counter1 < rows)
	{
		int counter2 = 0;
		while (counter2 < cols)
		{
			in->array[counter1][counter2] = fgetc(file);
			counter2++;
		}
		counter1++;
	}
}

int MazeTraversal(char array[][22], int rows, int cols, int timeLimit, WINDOW *window, int userLevel)
{
	//allow the user to traverse through the maze
	int success = 0; //if zero, then the user failed. if nonzero, the user succeeded

	//Create variables for starting and ending position and then figure out what they should be set to
	int curRow = 0;
	int curCol = 0;
	int endRow = 0;
	int endCol = 0;
	int counter1 = 0;
	while (counter1 < rows)
	{
		int counter2 = 0;
		while (counter2 < cols)
		{
			if (array[counter1][counter2] == 'X')
			{
				curRow = counter1;
				curCol = counter2;
			}
			if (array[counter1][counter2] == 'O')
			{
				endRow = counter1;
				endCol = counter2;
			}

			counter2++;
		}
		counter1++;
	}
	//Run the loop that will contain the maze movement operations
	time_t startTime, endTime;
	time(&startTime);
	while (1)
	{
		wprintw(window, "LEVEL: %d\n\n", userLevel);
		wprintw(window, "Use the arrow keys to navigate the X through the maze\n");
		PrintMaze(array, rows, cols, window);
		int input = wgetch(window);
		switch (input) //use a switch case to check if arrow keys have been input for movement
		{
			case KEY_UP:
				if (curRow > 1)
				{
					if (array[curRow-1][curCol] == ' ')
					{
						if (array[curRow-2][curCol] == ' ' || array[curRow-2][curCol] == 'O')
						{
							array[curRow][curCol] = ' ';
							array[curRow-2][curCol] = 'X';
							curRow = curRow - 2;
						}
					}
				}
				break;
			case KEY_RIGHT:
				if (curCol < 19)
				{
					if (array[curRow][curCol+1] == ' ')
					{
						if (array[curRow][curCol+2] == ' ' || array[curRow][curCol+2] == 'O')
						{
							array[curRow][curCol] = ' ';
							array[curRow][curCol+2] = 'X';
							curCol = curCol + 2;
						}
					}
				}
				break;
			case KEY_DOWN:
				if (curRow < 19)
				{
					if (array[curRow+1][curCol] == ' ')
					{
						if (array[curRow+2][curCol] == ' ' || array[curRow+2][curCol] == 'O')
						{
							array[curRow][curCol] = ' ';
							array[curRow+2][curCol] = 'X';
							curRow = curRow + 2;
						}
					}
				}
				break;
			case KEY_LEFT:
				if (curCol > 1)
				{
					if (array[curRow][curCol-1] == ' ')
					{
						if (array[curRow][curCol-2] == ' ' || array[curRow][curCol-2] == 'O')
						{
							array[curRow][curCol] = ' ';
							array[curRow][curCol-2] = 'X';
							curCol = curCol - 2;
						}
					}
				}
				break;
			default:
				break;
		}
		if (curRow == endRow)
		{
			if (curCol == endCol)
			{
				//if the user has completed progression, break out of traversal loop
				wclear(window);
				wrefresh(window);
				PrintMaze(array, rows, cols, window);
				break;
			}
		}
		wclear(window);
		wrefresh(window);
	}
	time(&endTime);
	double totalTime = difftime(endTime, startTime);
	if (totalTime <= timeLimit)
	{
		success = 1;
	}
	return success;
}

int Random()
{
	//calculate a random int from 1-6 to use for dice rolls
	int max = 6;
	return ( rand() % max)+ 1;
}

int DiceRoll(WINDOW *window,struct Enemy in)
{
	//set up 3 int values to store dice rolls. print the values and compare the total to the enemy power to see if they won
	int success = 0;
	wprintw(window, "Press any key to roll the dice\n");
	wgetch(window);
	wprintw(window, "Rolling 3 Dice\n") ;
	srand( time( NULL ) ) ;
	int d1 = Random();
	int d2 = Random();
	int d3 = Random();
	int total = d1 + d2 + d3;
	wprintw(window,"DIE1  DIE2  DIE3  TOTAL\n");
	wprintw(window, " %d  +  %d  +  %d  =  %d", d1, d2, d3, total);
	if (total >= in.power)
	{
		success = 1;
		wprintw(window,"\nYou won!\n");
	}
	else
	{
		success = 0;
		wprintw(window, "\nYou lost!\n");
	}
	wrefresh(window);
	return success;
}

void StartMenu(WINDOW *window)
{
	//run an infinite loop to display the start menu until the user wants to start the game
	while (1)
	{
		wprintw(window, "    MAZES AND MEN\n\nStart Game (press 's')\nInstructions (press 'i')\n\n");
		int input = wgetch(window);
		if (input == 's')
		{
			break;
		}
		else if (input == 'i')
		{
			wclear(window);
			wrefresh(window);
			wprintw(window, "This is Mazes and Men. The goal is to\ntraverse through all ten mazes and then defeat\nall ten men. To traverse through the mazes you\nuse the arrow keys to navigate. Each subsequent\nmaze will have less time available for you to\ncomplete it successfully. When fighting the men\nyou will roll three dice and if the sum of your\nrolls is greater than the or equal to the\nenemy's power then you will win and progress\nto the next level.\n\nPress any key to return to the main menu.");
			wgetch(window);
		}
		wclear(window);
		wrefresh(window);
	}
	wclear(window);
	wrefresh(window);
}

int MazeCall(WINDOW *mazeWindow, int mazeRows, int mazeCols, int timeLimit[], int userLevel, char mazeOne[][22], char mazeTwo[][22], char mazeThree[][22], char mazeFour[][22], char mazeFive[][22], char mazeSix[][22], char mazeSeven[][22], char mazeEight[][22], char mazeNine[][22], char mazeTen[][22])
{
	int completionStatus = 0;
	switch (userLevel)
	{
		case 1:
			completionStatus = MazeTraversal(mazeOne, mazeRows, mazeCols, timeLimit[userLevel -1], mazeWindow, userLevel);
			break;
		case 2:
			completionStatus = MazeTraversal(mazeTwo, mazeRows, mazeCols, timeLimit[userLevel - 1], mazeWindow, userLevel);
			break;
		case 3:
			completionStatus = MazeTraversal(mazeThree, mazeRows, mazeCols, timeLimit[userLevel - 1], mazeWindow, userLevel);
			break;
		case 4:
			completionStatus = MazeTraversal(mazeFour, mazeRows, mazeCols, timeLimit[userLevel - 1], mazeWindow, userLevel);
			break;
		case 5:
			completionStatus = MazeTraversal(mazeFive, mazeRows, mazeCols, timeLimit[userLevel - 1], mazeWindow, userLevel);
			break;
		case 6:
			completionStatus = MazeTraversal(mazeSix, mazeRows, mazeCols, timeLimit[userLevel - 1], mazeWindow, userLevel);
			break;
		case 7:
			completionStatus = MazeTraversal(mazeSeven, mazeRows, mazeCols, timeLimit[userLevel - 1], mazeWindow, userLevel);
			break;
		case 8:
			completionStatus = MazeTraversal(mazeEight, mazeRows, mazeCols, timeLimit[userLevel - 1], mazeWindow, userLevel);
			break;
		case 9:
			completionStatus = MazeTraversal(mazeNine, mazeRows, mazeCols, timeLimit[userLevel - 1], mazeWindow, userLevel);
			break;
		case 10:
			completionStatus = MazeTraversal(mazeTen, mazeRows, mazeCols, timeLimit[userLevel - 1], mazeWindow, userLevel);
			break;
		default:
			break;
	}
	return completionStatus;
}
int EnemyCall(WINDOW *enemyWindow, int enemyRows, int enemyCols, int userLevel, struct Enemy enemyOne, struct Enemy enemyTwo, struct Enemy enemyThree, struct Enemy enemyFour, struct Enemy enemyFive, struct Enemy enemySix, struct Enemy enemySeven, struct Enemy enemyEight, struct Enemy enemyNine, struct Enemy enemyTen)
{
	//set up a variable to return whether or not the user had a sufficient dice roll. Use a switch case to determine which enemy to call
	int rollStatus = 0;
	switch (userLevel)
	{
		case 1:
			PrintEnemy(enemyOne, enemyRows, enemyCols, enemyWindow);
			rollStatus = DiceRoll(enemyWindow, enemyOne);
			break;
		case 2:
			PrintEnemy(enemyTwo, enemyRows, enemyCols, enemyWindow);
			rollStatus = DiceRoll(enemyWindow, enemyTwo);
			break;
		case 3:
			PrintEnemy(enemyThree, enemyRows, enemyCols, enemyWindow);
			rollStatus = DiceRoll(enemyWindow, enemyThree);
			break;
		case 4:
			PrintEnemy(enemyFour, enemyRows, enemyCols, enemyWindow);
			rollStatus = DiceRoll(enemyWindow, enemyFour);
			break;
		case 5:
			PrintEnemy(enemyFive, enemyRows, enemyCols, enemyWindow);
			rollStatus = DiceRoll(enemyWindow, enemyFive);
			break;
		case 6:
			PrintEnemy(enemySix, enemyRows, enemyCols, enemyWindow);
			rollStatus = DiceRoll(enemyWindow, enemySix);
			break;
		case 7:
			PrintEnemy(enemySeven, enemyRows, enemyCols, enemyWindow);
			rollStatus = DiceRoll(enemyWindow, enemySeven);
			break;
		case 8:
			PrintEnemy(enemyEight, enemyRows, enemyCols, enemyWindow);
			rollStatus = DiceRoll(enemyWindow, enemyEight);
			break;
		case 9:
			PrintEnemy(enemyNine, enemyRows, enemyCols, enemyWindow);
			rollStatus = DiceRoll(enemyWindow, enemyNine);
			break;
		case 10:
			PrintEnemy(enemyTen, enemyRows, enemyCols, enemyWindow);
			rollStatus = DiceRoll(enemyWindow, enemyTen);
			break;
		default:
			break;
	}
	return rollStatus;
}
