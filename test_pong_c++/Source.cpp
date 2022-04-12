#pragma once

#include <time.h>
#include <random>
#include <conio.h>
#include <iostream>

using namespace std;

enum eDir
{
	STOP,
	LEFT,
	UPLEFT,
	DOWNLEFT,
	RIGHT,
	UPRIGHT,
	DOWNRIGHT
};

class Ball
{
private:
	int x, y;
	int origX, origY;
	eDir directional;
public:
	Ball(int posX, int posY)
	{
		origX = posX;
		origY = posY;
		x = posX;
		y = posY;
		directional = STOP;
	}
	void Reset()
	{
		x = origX;
		y = origY;
	}
	void changeDirectional(eDir d)
	{
		directional = d;
	}
	void randomDirectional()
	{
		directional = (eDir)((rand() % 6) + 1);
	}
	inline int getX() { return x; }
	inline int getY() { return y; }
	inline eDir getDirectional() { return directional; }
	void Move()
	{
		switch (directional)
		{
			case STOP:
				break;
			case LEFT:
				x--;
				break;
			case UPLEFT:
				x--; y--;
				break;
			case DOWNLEFT:
				x--; y++;
				break;
			case RIGHT:
				x++;
				break;
			case UPRIGHT:
				x++; y--;
				break;
			case DOWNRIGHT:
				x++; y++;
				break;
			default:
				break;
		}
	}
	friend ostream& operator<<(ostream& o, Ball c)
	{
		o << "Ball [" << c.x << ", " << c.y << "]\t[" << c.directional << "]";
		return o;
	}
};	

class Paddle
{
private:
	int x, y;
	int origX, origY;
public:
	Paddle()
	{
		x = y = 0;
	}
	Paddle(int posX, int posY) :Paddle()
	{
		origX = posX;
		origY = posY;
		x = posX;
		y = posY;
	}
	inline void Reset() { x = origX; y = origY; }
	inline int getX() { return x; }
	inline int getY() { return y; }
	inline void moveUP() { y--; }
	inline void moveDOWN() { y++; }
	friend ostream& operator<<(ostream& o, Paddle c)
	{
		o << "Paddle [" << c.x << ", " << c.y << "]";
		return o;
	}
};

class GameManager
{
private:
	int width, height;
	int score1, score2;
	char up1, up2, down1, down2;
	bool quit;
	Ball* ball;
	Paddle* player1;
	Paddle* player2;
public:
	GameManager(int width, int height)
	{
		srand(time(NULL));
		quit = false;
		up1 = 'w'; down1 = 's';
		up2 = 'i'; down2 = 'k';
		score1 = score2 = 0;
		this->width = width;
		this->height = height;
		ball = new Ball(width / 2, height / 2);
		player1 = new Paddle(1, height / 2 - 3);
		player2 = new Paddle(width - 2, height / 2 - 3);
	}
	~GameManager()
	{
		delete ball, player1, player2;
	}
	void ScoreUP(Paddle* player)
	{
		if (player == player1)
			score1++;
		else if (player == player2)
			score2++;

		ball->Reset();
		player1->Reset();
		player2->Reset();
	}
	void Draw()
	{
		system("cls");
		for (int i = 0; i < width + 2; i++)
			cout << "\xB2";
		cout << endl;

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				int ballX = ball->getX();
				int ballY = ball->getY();
				int player1X = player1->getX();
				int player1Y = player1->getY();
				int player2X = player2->getX();
				int player2Y = player2->getY();

				if (j == 0) cout << "\xB2";

				if (ballX == j && ballY == i)
					cout << "O";
				else if (player1X == j && player1Y == i)
					cout << "\xDB";
				else if (player2X == j && player2Y == i)
					cout << "\xDB";

				else if (player1X == j && player1Y + 1 == i)
					cout << "\xDB";
				else if (player1X == j && player1Y + 2 == i)
					cout << "\xDB";
				else if (player1X == j && player1Y + 3 == i)
					cout << "\xDB";

				else if (player2X == j && player2Y + 1 == i)
					cout << "\xDB";
				else if (player2X == j && player2Y + 2 == i)
					cout << "\xDB";
				else if (player2X == j && player2Y + 3 == i)
					cout << "\xDB";

				else 
					cout << " ";

				if (j == width - 1) cout << "\xB2";
			}
			cout << endl;
		}

		for (int i = 0; i < width + 2; i++)
			cout << "\xB2";

		cout <<endl<< "Score 1:" << score1 << "\t\t\tScore 2:" << score2 << endl;

	}
	void Input()
	{
		ball->Move();
		int ballX = ball->getX();
		int ballY = ball->getY();
		int player1X = player1->getX();
		int player1Y = player1->getY();
		int player2X = player2->getX();
		int player2Y = player2->getY();	

		if (_kbhit())
		{
			char current = _getch();
			if (current == up1)
				if (player1Y > 0)
					player1->moveUP();
			if (current == down1)
				if (player1Y + 4 < height)
					player1->moveDOWN();

			if (current == up2)
				if (player2Y > 0)
					player2->moveUP();
			if (current == down2)
				if (player2Y + 4 < height)
					player2->moveDOWN();
			if (ball->getDirectional() == STOP)
				ball->randomDirectional();
			
			if (current == 'q')
				quit = true;
		}
	}
	void Logic()
	{
		int ballX = ball->getX();
		int ballY = ball->getY();
		int player1X = player1->getX();
		int player1Y = player1->getY();
		int player2X = player2->getX();
		int player2Y = player2->getY();

		//left
		for (int i = 0; i < 4; i++)
			if (ballX == player1X + 1)
				if (ballY == player1Y + i)
					ball->changeDirectional((eDir)((rand() % 3) + 4));

		//right
		for (int i = 0; i < 4; i++)
			if (ballX == player2X - 1)
				if (ballY == player2Y + i)
					ball->changeDirectional((eDir)((rand() % 3) + 1));

		//bott
		if (ballY == height - 1)
			ball->changeDirectional(ball->getDirectional() == DOWNLEFT ? UPRIGHT : UPLEFT);

		//top
		if (ballY == 0)
			ball->changeDirectional(ball->getDirectional() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);

		//right
		if (ballX == width - 1)
			ScoreUP(player1);

		//left
		if (ballX == 0)
			ScoreUP(player2);
	}
	void Run()
	{
		while (!quit)
		{
			Draw();
			Input();
			Logic();
		}
	}
};

int main()
{
	GameManager g(40, 20);
	g.Run();
}