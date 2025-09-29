#include <iostream>
#include <conio.h>

using namespace std;

int PlayerX = 1;
int PlayerY = 1;

int PlayerMinX = 1;
int PlayerMinY = 1;
int PlayerMaxX = 9;
int PlayerMaxY = 9;

char PlayerShape = 'P';
char MonsterShape = 'M';

char sprite[10] = { ' ' };

char World[10][10];

int KeyCode;


void Input()
{
	KeyCode = _getch();
}

void Process()
{
	if (KeyCode == 'W' || KeyCode == 'w')
	{
		PlayerY--;
	}
	else if (KeyCode == 'A' || KeyCode == 'a')
	{
		PlayerX--;
	}
	else if (KeyCode == 'S' || KeyCode == 's')
	{
		PlayerY++;
	}
	else if (KeyCode == 'D' || KeyCode == 'd')
	{
		PlayerX++;
	}

	if (PlayerX < PlayerMinX) {
		PlayerX = PlayerMinX;
	}
	else if (PlayerY < PlayerMinY) {
		PlayerY = PlayerMinY;
	}
	else if (PlayerX > PlayerMaxX) {
		PlayerX = PlayerMaxX;
	}
	else if (PlayerY > PlayerMaxY) {
		PlayerY = PlayerMaxY;
	}
}

void Render()
{
	system("cls");

	cout << MonsterShape;

	for (int Y = 0; Y <= PlayerMaxY; ++Y)
	{
		for (int X = 0; X <= PlayerMaxX; ++X)
		{
			if (PlayerX == X && PlayerY == Y)
			{
				cout << PlayerShape;
			}
			else
			{
				cout << sprite[World[Y][X]];
			}
		}
		cout << "\n";
	}
} //Render

int main()
{
	for(;;)
	{
		Render();
		Input();
		Process();
	}
	
}