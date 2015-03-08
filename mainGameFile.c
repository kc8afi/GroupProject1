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
int MazeTraversal(char array[][22], int rows, int cols, int timeLimit, WINDOW *window);
int Random(int Max);
void DiceRoll(WINDOW *enemyWindow,struct Enemy in);

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

	//trying to set up a timer for the maze. once it works, set up a switch case for different time limits depending on which maze is being called
	int timeLimit = 20;
	int completionStatus = MazeTraversal(mazeOne, mazeRows, mazeCols, timeLimit, mazeWindow);
	if (completionStatus != 0)
	{
		wprintw(mazeWindow, "You succeeded!\n");
	}
	else
	{
		wprintw(mazeWindow, "You failed!\n");
	}

	PrintEnemy(enemyNine, enemyRows, enemyCols, enemyWindow);
	wrefresh(enemyWindow);
	DiceRoll(enemyWindow, enemyNine);
	wrefresh(enemyWindow);
	wgetch(mazeWindow);
	delwin(mazeWindow);
	delwin(enemyWindow);
	endwin();
	return 0;

}

void PrintMaze(char array[][22], int rows, int cols, WINDOW *window)
{
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

int MazeTraversal(char array[][22], int rows, int cols, int timeLimit, WINDOW *window)
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
		mvwprintw(window, 0, 0, "Use the arrow keys to navigate the X through the maze\n");
		PrintMaze(array, rows, cols, window);
		int input = wgetch(window);
		switch (input)
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

int Random(int Max)
{
	return ( rand() % Max)+ 1;
}

void DiceRoll(WINDOW *enemyWindow,struct Enemy in)
{
	wprintw(enemyWindow,"Rolling 3 Dice\n") ;
	srand( time( NULL ) ) ;
	int d1=Random(6) ;
	int d2=Random(6) ;
	int d3=Random(6) ;
	int total=d1+d2+d3;
        wprintw(enemyWindow,"DIE1  DIE2  DIE3  TOTAL\n");
        wprintw(enemyWindow," %d  +  %d  +  %d  =  %d",d1,d2,d3,total);
	 if (total<in.power)
        {
            wprintw(enemyWindow,"\nYou lost\n");
        }
        else if(total>in.power)
        {
             wprintw(enemyWindow,"\nYou win\n");
        }
}
