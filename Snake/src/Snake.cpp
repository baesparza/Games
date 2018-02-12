#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

unsigned const int 
N = 30, M = 20, // number of colums, rows
size = 16, // size of each square
Width = size * N, Height = size * M; // size of window

int dir, num = 4;

struct Snake
{
	int x, y;
} s[100]; // all component of a snake

void Tick() 
{
	for (int i = num; i > 0; i--) // copy last position of snake part
	{
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;
	}
	if (dir == 0) s[0].y += 1;
	else if (dir == 1) s[0].x -= 1;
	else if (dir == 2) s[0].x += 1;
	else if (dir == 3) s[0].y -= 1;
}


int main()
{
	RenderWindow app(VideoMode(Width, Height), "Snake Game!");

	Texture t1, t2;
	t1.loadFromFile("./assets/images/white.png");
	t2.loadFromFile("./assets/images/red.png");

	Sprite sprite1(t1), sprite2(t2);

	Clock clock;
	float timer = 0.f, delay = 0.1f;

	while (app.isOpen())
	{
		// control speed
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();
		}

		// control movement(keyboard input)
		if (Keyboard::isKeyPressed(Keyboard::Up) &&  dir != 0) dir = 3;
		else if (Keyboard::isKeyPressed(Keyboard::Down) && dir != 3) dir = 0;
		else if (Keyboard::isKeyPressed(Keyboard::Right) && dir != 1) dir = 2;
		else if (Keyboard::isKeyPressed(Keyboard::Left) && dir != 2) dir = 1;

		// control speed of movement
		if (timer > delay)
		{
			timer = 0;
			Tick();
		}


		////draw////
		app.clear();
		// draw background
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
			{
				sprite1.setPosition(i * size, j * size);
				app.draw(sprite1);
			}

		// draw snake
		for (int i = 0; i < num; i++)
		{
			sprite2.setPosition(s[i].x * size, s[i].y * size);
			app.draw(sprite2);
		}

		app.display();
	}

	return 0;
}