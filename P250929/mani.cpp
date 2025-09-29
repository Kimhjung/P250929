#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

enum ERenderScreenBuffer
{
	FrontBuffer = 0,
	BackBuffer = 1,
};

int CurrentBufferIndex = FrontBuffer;

struct FCharacter
{
	int X;
	int Y;
	string Shape;
};

FCharacter Characters[3];

int KeyCode;

HANDLE FrontBufferHandle;
HANDLE BackBufferHandle;

void Input()
{
	KeyCode = _getch();
}


//const: 상수 - 원본 값 바꾸지 않겠다 선언
//C++, C#
void RenderCharacter(const FCharacter* InData)
{
	COORD Position;
	Position.X = (SHORT)InData->X;
	//Position.Y = (SHORT)(*InData).Y;
	Position.Y = (SHORT)InData->Y;

	//더블버퍼링 해결
	if(CurrentBufferIndex == FrontBuffer)
	{
		SetConsoleCursorPosition(FrontBufferHandle, Position);
		WriteConsole(FrontBufferHandle, InData->Shape.c_str(), 1, NULL, NULL);
	}
	else
	{
		SetConsoleCursorPosition(BackBufferHandle, Position);
		WriteConsole(BackBufferHandle, InData->Shape.c_str(), 1, NULL, NULL);
	}
	CurrentBufferIndex++;
	CurrentBufferIndex = CurrentBufferIndex % 2;
}

void Render()
{
	system("cls");
	for (int i = 0; i < 3; ++i)
	{
		RenderCharacter(&Characters[i]);
	}
}

//초기화
void Init()
{
	//형변환, Casting
	srand((unsigned int)time(nullptr));

	Characters[0].X = 1;
	Characters[0].Y = 1;
	Characters[0].Shape = "P";

	Characters[1].X = 10;
	Characters[1].Y = 10;
	Characters[1].Shape = "M";

	//C++에 null 없음
	//NULL = 0 값 넣어준거 있음
	FrontBufferHandle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, nullptr, CONSOLE_TEXTMODE_BUFFER, NULL);
	BackBufferHandle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, nullptr, CONSOLE_TEXTMODE_BUFFER, NULL);
}

void Clear()
{

}

void MovePlayer()
{
	if (KeyCode == 'w')
	{
		Characters[0].Y--;
	}
	else if (KeyCode == 's')
	{
		Characters[0].Y++;
	}
	else if (KeyCode == 'a')
	{
		Characters[0].X--;
	}
	else if (KeyCode == 'd')
	{
		Characters[0].X++;
	}
}

void MoveMonster()
{
	int Direction = rand() % 4;

	switch (Direction)
	{
	case 0:	//Up
		Characters[1].Y--;
		break;
	case 1:	//Down
		Characters[1].Y++;
		break;
	case 2: //Left
		Characters[1].X--;
		break;
	case 3: //Right
		Characters[1].X++;
		break;
	default:
		//Error
		break;
	}

}

void Tick()
{
	MovePlayer();
	MoveMonster();
}

int main()
{
	//FCharacter* Data = new FCharacter();

	//(*Data).X = 1;
	//Data->X = 1;

	Init();

	while (true)
	{
		Input();
		Tick();
		Render();
	}

	return 0;
}