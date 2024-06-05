#include<stdio.h>
#include<iostream>
#include<Windows.h>
#include<ctime>
#include<string>
#include<fstream>

using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
const int arraySize = 9; //declaring size for arrays
int grid[arraySize][arraySize], solved[arraySize][arraySize] = { 0 };
int generatedGrid[arraySize][arraySize] = { 0 }; // copy grid
bool validityCheck(int row, int col, int num);
bool check();
void mainMenu();
void howToPlay();

bool checkOriginalGrid(int row, int col, int val) {
	if (generatedGrid[row][col] != 0) {
		return true;
	}
	return false;
}

void generateGrid(int grid[arraySize][arraySize]) {
	srand(time(NULL));
	for (int i = 0; i < 40; i++) {
		int random1 = rand() % 10; int random2 = rand() % 10; int random3 = rand() % 10;
		int row, col, val;
		row = random1;
		col = random2;
		val = random3;

		if (random3 == 0) {
			i--;
			continue;
		}
		else if ((row > 0 && row < 10) && (col > 0 && col < 10)) {

			if (validityCheck(row, col, val)) {
				grid[row][col] = val;
				generatedGrid[row][col] = val;
			}
			else {
				continue;
			}
		}
		else {
			i--;
			continue;
		}
	}
}

void saveGame() {
	char saveSlot;
	string fileName = "save",fileName2 = "oGrid";
	SetConsoleTextAttribute(hConsole, 7);
	cout << "Choose slot to save game: ";
	cin >> saveSlot;
	fileName += saveSlot;
	fileName2 += saveSlot;
	fstream save;
	fstream save2;

	save.open(fileName + ".txt", ios::out);
	save2.open(fileName2 + ".txt", ios::out);
	if (save.is_open() && save2.is_open()) {
		for (int i = 0; i < arraySize; i++)
		{
			for (int j = 0; j < arraySize; j++) {
				save << grid[i][j] << " ";
				save2 << generatedGrid[i][j] << " ";
			}
		}
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 2);
		cout << "File saved Sucessfully!" << endl;
		save.close();
		save2.close();
	}
	else {
		SetConsoleTextAttribute(hConsole, 4);
		cout << "File not saved!" << endl;
	}
}
void loadGame() {
	char saveSlot;
	string fileName = "save",fileName2 = "oGrid";
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 7);
	cout << "Choose slot to load game: ";
	cin >> saveSlot;
	fileName += saveSlot;
	fileName2 += saveSlot;
	fstream save,save2;
	save.open(fileName + ".txt", ios::in);
	save2.open(fileName2 + ".txt", ios::in);
	if (save.is_open()&&save2.is_open()) {
		for (int i = 0; i < arraySize; i++)
		{
			for (int j = 0; j < arraySize; j++) {
				save >> grid[i][j];
				save2 >> generatedGrid[i][j];
			}
		}
		SetConsoleTextAttribute(hConsole, 2);
		save.close();
		save2.close();
	}
	else {
		SetConsoleTextAttribute(hConsole, 4);
		cout << "File does not exist!" << endl;
	}
}

bool colCheck(int col, int num, int row) {
	//to check if number is present in col
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 6);
	for (int i = 0; i < arraySize; i++)
		if (grid[i][col] == num && i!=row)
			return true;
	return false;
}
bool rowCheck(int row, int num, int col) {
	//to check if number is present in row
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 6);
	for (int i = 0; i < arraySize; i++)
		if (grid[row][i] == num && i!= col)
			return true;
	return false;
}
bool squareCheck(int rowStart, int colStart, int value) {
	//to check if number is present in the respective 3x3 square
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 6);
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			if (grid[row + rowStart][col + colStart] == value)
				return true;
	return false;
}

bool emptySpaceCheck(int& row, int& col) {
	//checks if there is empty space
	for (row = 0; row < arraySize; row++)
		for (col = 0; col < arraySize; col++)
			if (grid[row][col] == 0) //0 means empty space exists
				return true;
	return false;
}
bool validityCheck(int row, int col, int value) {
	//checks if value is present in row, col and square
	bool valid=false;
	(!rowCheck(row, value, col) && !colCheck(col, value, row) && !squareCheck(row - row % 3,
		col - col % 3, value)) ? valid = true : valid = false;
	return valid;
}

void printGrid() {
	//prints sudoku
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 2);
	cout << "\t\t\t\t\ty";
	SetConsoleTextAttribute(hConsole, 5);
	cout << "|";
	SetConsoleTextAttribute(hConsole, 2);
	cout << "x";
	SetConsoleTextAttribute(hConsole, 5);
	cout << "| ";
	SetConsoleTextAttribute(hConsole, 2);
	cout << "0" << " 1" << " 2 ";
	SetConsoleTextAttribute(hConsole, 5);
	cout << " | ";
	SetConsoleTextAttribute(hConsole, 2);
	cout << "3" << " 4" << " 5 ";
	SetConsoleTextAttribute(hConsole, 5);
	cout << " | ";
	SetConsoleTextAttribute(hConsole, 2);
	cout << "6" << " 7" << " 8" << endl;
	SetConsoleTextAttribute(hConsole, 5);
	cout << "\t\t\t\t\t---------------------------\n";
	for (int row = 0; row < arraySize; row++) {
		SetConsoleTextAttribute(hConsole, 2);
		cout << "\t\t\t\t\t" << row;
		SetConsoleTextAttribute(hConsole, 5);
		cout << "  | ";
		for (int col = 0; col < arraySize; col++) {
			if (col == 3 || col == 6)
				cout << " | ";
			if (grid[row][col] == 0) {
				SetConsoleTextAttribute(hConsole, 6);
				cout << "#" << " ";
			}
			else {
				SetConsoleTextAttribute(hConsole, 6);
				cout << grid[row][col] << " ";
			}
		}
		if (row == 2 || row == 5) {
			SetConsoleTextAttribute(hConsole, 6);
			cout << endl;
			cout << "\t\t\t\t\t";
			for (int i = 0; i < arraySize; i++) {
				SetConsoleTextAttribute(hConsole, 5);
				cout << "---";
			}
		}
		cout << endl;
	}
}

bool userSolve() {
	//takes input from user
	int row, col, val;
	char options;
	system("cls");
	while(1){
	startAgain:
	printGrid();
	cout << endl;

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 3);
	answer: cout << "Enter row(y), column(x) and value respectively ";
		SetConsoleTextAttribute(hConsole, 2);
		cout << "(Press 10 for more options): ";
		SetConsoleTextAttribute(hConsole, 6);
	    cin >> row;
		if (row == 10) {
			SetConsoleTextAttribute(hConsole, 3);
			cout << "s = Save Game\n";
			SetConsoleTextAttribute(hConsole, 5);
			cout << "m = Main Menu\n";
			SetConsoleTextAttribute(hConsole, 8);
			cout << "h = How To Play\n";
			SetConsoleTextAttribute(hConsole, 6);
			cin >> options;
			if (options == 's') {
				saveGame();
				system("cls");
				goto startAgain;
			}
			else if (options == 'm') {
				system("cls");
				mainMenu();
			}
			else if (options == 'h') {
				system("cls");
				howToPlay();
				goto startAgain;
			}
			else {
				SetConsoleTextAttribute(hConsole, 4);
				cout << "Invalid input. ";
				goto startAgain;
			}
		}
		else if (row > 10 || row < 0 || row == 9) {
			SetConsoleTextAttribute(hConsole, 4);
			cout << "Invalid row input. Enter value between 0-8 or 10 for more options.\n";goto answer;
		}
		SetConsoleTextAttribute(hConsole, 6);
		cin >> col >> val;
		if (col > 8 || col < 0) {
			SetConsoleTextAttribute(hConsole, 4);
			cout << "Invalid column input. Value must be between 0-8.\n";goto answer;
		}
		if (val > 10 || val < 0) {
			SetConsoleTextAttribute(hConsole, 4);
			cout << "Invalid value input. Value should be between 1-9.\n"; goto answer;
		}
		if (!checkOriginalGrid(row, col, val)) {
			grid[row][col] = val;
		}
		else {
			SetConsoleTextAttribute(hConsole, 4);
			cout << "Invalid input location. You can not insert data in any position where value is already given." << endl;
			system("pause");
		}
		system("cls");
		if (!emptySpaceCheck(row, col)){
			break;
		}
	}
	if (!emptySpaceCheck(row, col)){
		return true;
	}
	else {
		userSolve();
	}
}

bool check() {
	//checks the entire board in the end
	if (userSolve()) {
		for (int row = 1; row < 9; row++) {
			for (int col = 0; col < 9; col++) {
				if (validityCheck(row, col, grid[row][col])) { //check validation
					continue;
				}
				else {
					return false;
				}
			}

		}
	}
	for (int row = 1; row < 9; row++) { // checks if there is any 0 present in array
		for (int col = 0; col < 9; col++) {
			if (grid[row][col] == 0)
				return false;
		}
	}
}

void howToPlay() { //displays instructions
	SetConsoleTextAttribute(hConsole, 4);
	cout << "--------------------------------------------";
	SetConsoleTextAttribute(hConsole, 7);
	cout << "SUDOKU";
	SetConsoleTextAttribute(hConsole, 4);
	cout << "---------------------------------------------" << endl;
	SetConsoleTextAttribute(hConsole, 5);
	cout << "                INSTRUCTIONS         " << endl;
	SetConsoleTextAttribute(hConsole, 4);
	cout << "---------------------------------------------------------------------------------------" << endl;
	SetConsoleTextAttribute(hConsole, 7);
	cout << "\t> Sudoku puzzle consists of a 9x9 grid, you have to fill the empty squares using the numbers 1 to 9.\n"
		<< "\t> Use the 1-9 keys in your keybord to fill the sudoku puzzle.\n "
		<< "\t> To play, first type the co-ordinates given beside the suduko board and then enter your value\n"
		<< "\t> Enter value as 0 to clear the number selected in the sudoku puzzle. \n"
		<< "\t> Once you fill all the spaces in sudoku puzzle, it will automatically check your puzzle.\n"
		<< "\t> You can save or quit the game by opening the option menu if you are having a hard time.\n";
	SetConsoleTextAttribute(hConsole, 4);
}
void mainMenu() {
	char ans;
	SetConsoleTextAttribute(hConsole, 7);
menu: cout << "\tMENU\n";
	SetConsoleTextAttribute(hConsole, 9);
	cout << "n = New game\n";
	SetConsoleTextAttribute(hConsole, 2);
	cout << "l = Load game\n";
	SetConsoleTextAttribute(hConsole, 8);
	cout << "h = How to Play\n";
	SetConsoleTextAttribute(hConsole, 5);
	cout << "e = Exit game\n";
	SetConsoleTextAttribute(hConsole, 6);
	cin >> ans;
	if (ans == 'n') {
		system("cls");
		if (check()) {
			system("cls");
			SetConsoleTextAttribute(hConsole, 2);
			cout << "\t\t Congratulations! You have solved the game!\n";
			printGrid();
		}
		else {
			SetConsoleTextAttribute(hConsole, 4);
			cout << "Too bad! You've lost....";
		}
	}
	else if (ans == 'l') {
		loadGame();
		if (check()) {
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 2);
			cout << "\t\t Congratulations! You have solved the game!\n";
			printGrid();
		}
		else
		{
			SetConsoleTextAttribute(hConsole, 4);
			cout << "Too bad! You've lost....";
		}
	}
	else if (ans == 'h') {
		system("cls");
		howToPlay();
	}
	else if (ans == 'e')
		exit(0);
	else
	{
		SetConsoleTextAttribute(hConsole, 4);
		cout << "Invalid input! Enter again.\n"; goto menu;
	}
}

void start() {
	generateGrid(grid);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 4);
	cout << "\n\n\n\n\n\n\n\n\n\n\n\t---------------------------------------";
	SetConsoleTextAttribute(hConsole, 7);
	cout << "SUDOKU";
	SetConsoleTextAttribute(hConsole, 4);
	cout << "---------------------------------------" << endl;
	Sleep(2000);
	system("cls");
	SetConsoleTextAttribute(hConsole, 7);
	cout << "\n\n\n\n\n\n\n\n\t\t\tMADE BY:\n\n\t\t\t\t\tNAILA AWAN (22L-7950)\n\n\t\t\t\t\tFATIMA KHAN (22L-7890)";
	Sleep(2000);
	system("cls");
	mainMenu();
}
int main() {
	start();
	system("pause");
	return 0;
}