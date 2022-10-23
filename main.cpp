#include <iostream>
#include <time.h>
#include <conio.h>
#include <windows.h>
using namespace std;

enum eDirection
{
	STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6
};

class ball
{
private:
	int x, y;
	int originalX, originalY;
	eDirection direction;

public:
	ball(int posX, int posY)
	{
		originalX = posX;
		originalY = posY;
		x = posX;
		y = posY;
		direction = STOP;
	}
	void reset()
	{
		x = originalX;
		y = originalY;
		direction = STOP;
	}
	void changeDirection(eDirection d)
	{
		direction = d;
	}
	inline int getX()
	{
		return x;
	}
	inline int getY()
	{
		return y;
	}
	inline eDirection getDirection()
	{
		return direction;
	}
	void randomDirection()
	{
		direction = (eDirection)((rand() % 6) + 1);
	}
	void move()
	{
		switch (direction)
		{
		case STOP:
			break;
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UPLEFT:
			x--;
			y--;
			break;
		case UPRIGHT:
			x++;
			y--;
			break;
		case DOWNLEFT:
			x--;
			y++;
			break;
		case DOWNRIGHT:
			x++;
			y++;
			break;
		default:
			break;
		}
	}
	friend ostream & operator << (ostream & object, ball c)
	{
		object << "Ball [" << c.x << "," << c.y << "][" << c.direction << "]" << endl;
		return object;
	}
};

class paddle
{
private:
	int x, y;
	int originalX, originalY;
public:
	paddle()
	{
		x = y = 0;
	}
	paddle(int posX, int posY) : paddle()
	{
		originalX = posX;
		originalY = posY;
		x = posX;
		y = posY;
	}
	inline void reset()
	{
		x = originalX;
		y = originalY;
	}
	inline int getX()
	{
		return x;
	}
	inline int getY()
	{
		return y;
	}
	inline void moveUp()
	{
		y--;
	}
	inline void moveDown()
	{
		y++;
	}
	friend ostream& operator << (ostream& object, paddle c)
	{
		object << "Paddle [" << c.x << "," << c.y << "]" << endl;
		return object;
	}
};

class gameManager
{
private:
	int width, height;
	int score1, score2;
	char up1, down1, up2, down2, startGame;
	bool quit;
	int winner;
	ball* cball;
	paddle* player1;
	paddle* player2;
public:
	gameManager(int w, int h)
	{
		srand(time(NULL));
		quit = false;
		up1 = 'w';
		up2 = 'i';
		down1 = 's';
		down2 = 'k';
		startGame = 'g';
		score1 = score2 = 0;
		width = w;
		height = h;
		cball = new ball(w / 2, h / 2);
		player1 = new paddle(1, h/2 - 3);
		player2 = new paddle(w - 2, h / 2 - 3);
		winner = 0;
	}
	~gameManager()
	{
		delete cball, player1, player2;
	}
	void scoreUp(paddle* player)
	{
		if (player == player1)
		{
			score1++;
		}
		else if (player == player2)
		{
			score2++;
		}
		if (score1 >= 5)
			winner = 1;
		if (score2 >= 5)
			winner = 2;

		if (winner != 0)
		{
			system("cls");

			for (int i = 0; i < width; i++)
			{
				cout << "\xB2";
			}
			cout << endl;
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
					if (j == 0)
					{
						cout << "\xB2";
					}
					else if (j == width - 1)
					{
						cout << "\xB2" << endl;
					}
					else
					{
						cout << " ";
					}
				}
			}
			for (int i = 0; i < width; i++)
			{
				cout << "\xB2";
			}
			cout << endl;
			cout << "\nGAME OVER, PLAYER " << winner << " WINS\n";
			quit = true;
		}

		cball->reset();
		player1->reset();
		player2->reset();
	}
	void Draw()
	{
		system("cls");
		for (int i = 0; i < width + 2; i++)
		{
			cout << "\xB2";
		}
		cout << endl;
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				int ballx = cball->getX();
				int bally = cball->getY();
				int player1x = player1->getX();
				int player1y = player1->getY();
				int player2x = player2->getX();
				int player2y = player2->getY();

				if (j == 0)
					cout << "\xB2";

				if (ballx == j && bally == i)
					cout << "o"; //print ball

				else if (player1x == j && player1y == i)
					cout << "\xDB"; 
				else if (player1x == j && player1y + 1 == i)
					cout << "\xDB"; 
				else if (player1x == j && player1y + 2 == i)
					cout << "\xDB"; 
				else if (player1x == j && player1y + 3 == i)
					cout << "\xDB"; 
				//print paddle player1

				else if (player2x == j && player2y == i)
					cout << "\xDB"; //print paddle player2
				else if (player2x == j && player2y + 1 == i)
					cout << "\xDB";
				else if (player2x == j && player2y + 2 == i)
					cout << "\xDB";
				else if (player2x == j && player2y + 3 == i)
					cout << "\xDB";
				//print paddle player2

				else
					cout << " ";

				if (j == width - 1)
					cout << "\xB2";
			}
			cout << endl;
		}
		for (int i = 0; i < width + 2; i++)
		{
			cout << "\xB2";
		}

		cout << "\nScore 1: " << score1 << "\nScore 2: " << score2 << endl;
	}
	void Input()
	{
		cball->move();

		int ballx = cball->getX();
		int bally = cball->getY();
		int player1x = player1->getX();
		int player1y = player1->getY();
		int player2x = player2->getX();
		int player2y = player2->getY();

		if (_kbhit())
		{
			char current = _getch();

			if (current == up1)
				if (player1y > 0)
					player1->moveUp();

			if (current == up2)
				if (player2y > 0)
					player2->moveUp();

			if (current == down1)
				if (player1y + 4 < height)
					player1->moveDown();

			if (current == down2)
				if (player2y + 4 < height)
					player2->moveDown();

			if (cball->getDirection() == STOP)
				cball->randomDirection();

			if (current == 'q')
				quit = true;
		}
	}
	void Logic()
	{
		int ballx = cball->getX();
		int bally = cball->getY();
		int player1x = player1->getX();
		int player1y = player1->getY();
		int player2x = player2->getX();
		int player2y = player2->getY();

		//left paddle
		for (int i = 0; i < 4; i++)
		{
			if (ballx == player1x + 1)
				if (bally == player1y + i)
					cball->changeDirection((eDirection)((rand() % 3) + 4));
		}

		//right paddle
		for (int i = 0; i < 4; i++)
		{
			if (ballx == player2x - 1)
				if (bally == player2y + i)
					cball->changeDirection((eDirection)((rand() % 3) + 1));
		}

		//bottom wall

		if (bally == height - 1)
			if (cball->getDirection() == DOWNRIGHT)
				cball->changeDirection((eDirection)(5));
			else
				cball->changeDirection((eDirection)(2));

		//top wall

		if (bally == 0)
			if (cball->getDirection() == UPRIGHT)
				cball->changeDirection((eDirection)(6));
			else
				cball->changeDirection((eDirection)(3));

		//right wall
		if (ballx == width - 1)
			scoreUp(player1);

		//left wall
		if (ballx == 0)
			scoreUp(player2);
		
	}
	void Run()
	{
		while (!quit)
		{
			Draw();
			Input();
			Logic();
			Sleep(25);
		}
	}
	void startScreen()
	{
		cout << "               Controls               " << endl;
		cout << "        Use W and S for Player 1      " << endl;
		cout << "        Use I and K for Player 2      " << endl;
		cout << " Press Q to quit the game at any time " << endl;
		cout << "       Press G to begin the game      ";
		while (true)
		{
			if (_kbhit())
			{
				char current = _getch();
				if (current == 'g')
				{
					Run();
				}
			}
		}
	}
};


int main()
{
	gameManager o(40, 20);
	o.startScreen();
	return 0;




	/*ball c(0, 0);
	cout << c << endl;
	c.randomDirection();
	cout << c << endl;
	c.move();
	cout << c << endl;
	c.randomDirection();
	c.move();
	cout << c << endl;
	c.randomDirection();
	c.move();
	cout << c << endl;*/

	/*paddle p1(0, 0);
	paddle p2(10, 0);
	cout << p1 << endl;
	cout << p2 << endl;
	for (int i = 0; i < 10; i++)
	{
		p1.moveUp();
		cout << p1 << endl;
	}
	p2.moveDown();*/
	

	return 0;
}
