#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

const int M = 20, N = 10; // height and width of grid

int field[M][N] = {0}; // field to record color if full

struct Square // each square of piece
{
	int x, y; // position
} a[4], b[4]; // a = main piece, b as a temporal piece

int figures[7][4] = // all types of figures
{
	1, 3, 5, 7, // I
	2, 4, 5, 7, // Z
	3, 5, 4, 6, // S
	3, 5, 4, 7, // T
	2, 3, 5, 7, // L
	3, 5, 7, 6, // J
	2, 3, 4, 5, // O
};

bool check() // check if piece can move, or is in a limit, limit movement
{
	for (int i = 0; i < 4; i++)
		if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) // limit movement o pieces part
			return false;
		else if (field[a[i].y][a[i].x])  // field already has pieces
			return false;
	return true; // can move
};


int main()
{
	srand(time(0));

	RenderWindow window(VideoMode(320, 480), "TETRIS");

	// load images
	Texture t1, t2, t3;
	t1.loadFromFile("./assets/images/tiles.png");
	t2.loadFromFile("./assets/images/background.png");
	t3.loadFromFile("./assets/images/frame.png");

	// representations of diferent textures
	Sprite s(t1), background(t2), frame(t3);

	int dx = 0; // movement of piece
	int colorNum = 1; // color of each piece
	bool rotate = 0; //if a peache needs to rotate
	float timer = 0, delay = 0.3; // velociti of movement

	Clock clock; // clock, keep track of time

				 /////keep program working/////
	while (window.isOpen())
	{
		// variables to control the speed of game
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();

			// keyboard input, to rotate or move
			if (e.type == Event::KeyPressed)
				if (e.key.code == Keyboard::Up)
					rotate = true;
				else if (e.key.code == Keyboard::Left)
					dx = -1;
				else if (e.key.code == Keyboard::Right)
					dx = 1;
		}

		// speed up falling
		if (Keyboard::isKeyPressed(Keyboard::Down))
			delay = 0.05;

		//// <- Move -> ////
		for (int i = 0; i < 4; i++)
		{
			b[i] = a[i]; // store temporal b
			a[i].x += dx; // displacement temporaly
		}
		if (!check()) // if piece cant move x, restore b piece
			for (int i = 0; i < 4; i++)
				a[i] = b[i];

		//////Rotate//////
		if (rotate)
		{
			Square p = a[1]; //center of rotation
			for (int i = 0; i < 4; i++)
			{
				int x = a[i].y - p.y;
				int y = a[i].x - p.x;
				a[i].x = p.x - x;
				a[i].y = p.y + y;
			}
			if (!check()) // if rotation is not avalilable restore temp piece
				for (int i = 0; i < 4; i++)
					a[i] = b[i];
		}

		/////Tick/////
		if (timer > delay)
		{
			for (int i = 0; i < 4; i++)
			{
				b[i] = a[i]; // sote temporal b
				a[i].y += 1; // move main piece
			}

			if (!check()) // if piece cant move, move store it to field
			{
				for (int i = 0; i < 4; i++) // store colors of each square from this piece
					field[b[i].y][b[i].x] = colorNum;

				colorNum = 1 + rand() % 7; // change color of next pieve
				int n = rand() % 7; // select next random piece
				for (int i = 0; i < 4; i++) // format piece
				{
					a[i].x = figures[n][i] % 2;
					a[i].y = figures[n][i] / 2;
				}
			}

			timer = 0; // reset timer
		}

		///////check lines//////////
		int k = M - 1; // line to be removed
		for (int i = M - 1; i > 0; i--) // start from the top
		{
			int count = 0; // counter for each line
			for (int j = 0; j < N; j++)
			{
				if (field[i][j])
					count++;
				field[k][j] = field[i][j]; //copy field
			}
			if (count < N) // line is not full
				k--; // go next line
		}

		// reset variables
		dx = rotate = 0;
		delay = 0.3;

		/////////draw//////////
		window.clear(Color::White); // clear window
		window.draw(background); // draw background

		for (int i = 0; i < M; i++) // draw field
			for (int j = 0; j < N; j++)
			{
				if (field[i][j] == 0) continue; // if empty, dont draw nothing
				s.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18)); // draw colors
				s.setPosition(j * 18, i * 18);
				s.move(28, 31); // offset
				window.draw(s); // draw each square
			}

		for (int i = 0; i < 4; i++) // draw each piece
		{
			s.setTextureRect(IntRect(colorNum * 18, 0, 18, 18)); // draw each square
			s.setPosition(a[i].x * 18, a[i].y * 18);
			s.move(28, 31); //offset
			window.draw(s);
		}

		window.draw(frame);
		window.display();
	}

	return 0;
}