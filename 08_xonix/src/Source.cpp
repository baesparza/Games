#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

const unsigned int M = 20, N = 40;

int grid[M][N];
const unsigned int TS = 18; // tile size

struct Enemy
{
	int x, y, dx, dy;
	Enemy()
	{
		x = y = 300;
		dx = 4 - rand() % 8;
		dy = 4 - rand() % 8;
	}
	void move()
	{
		// move and colitions with walls
		x += dx;
		if (grid[y / TS][x / TS] == 1)
		{
			dx *= -1;
			x += dx;
		}
		y += dy;
		if (grid[y / TS][x / TS] == 1)
		{
			dy *= -1;
			y += dy;
		}
	}
};

void drop(int y, int x)
{
	if (grid[y][x] == 0)
		grid[y][x] = -1;
	if (grid[y - 1][x] == 0)
		drop(y - 1, x);
	if (grid[y + 1][x] == 0)
		drop(y + 1, x);
	if (grid[y][x - 1] == 0)
		drop(y, x - 1);
	if (grid[y][x + 1] == 0)
		drop(y, x + 1);
}


int main()
{
	srand(time(0));

	RenderWindow window(VideoMode(N * TS, M * TS), "XONIX");
	window.setFramerateLimit(60);

	// load texture
	Texture t1, t2, t3;
	t1.loadFromFile("./assets/images/tiles.png");
	t2.loadFromFile("./assets/images/enemy.png");
	t3.loadFromFile("./assets/images/gameover.png");

	Sprite sTile(t1), sEnemy(t2), sGameOver(t3);
	sGameOver.setPosition(100, 100);

	sEnemy.setOrigin(20, 20);
	int enemyCount = 4;
	Enemy a[10];


	bool gameover = false;
	int x = 0, y = 0, dx = 0, dy = 0;
	float timer = 0.f, delay = 0.07f;
	Clock clock;

	// fill border
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			grid[i][j] = (i == 0 || j == 0 || i == M - 1 || j == N - 1) ? 1 : 0;


	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();


			// restart game
			if (e.type == Event::KeyPressed)
				if (e.key.code == Keyboard::Escape)
				{
					for (int i = 1; i < M - 1; i++)
						for (int j = 1; j < N - 1; j++)
							grid[i][j] = 0;

					x = 10; y = 0;
					gameover = false;
				}
		}


		// keyboar input
		if (Keyboard::isKeyPressed(Keyboard::Left)) { dx = -1; dy = 0; }
		else if (Keyboard::isKeyPressed(Keyboard::Right)) { dx = 1; dy = 0; }
		else if (Keyboard::isKeyPressed(Keyboard::Up)) { dx = 0; dy = -1; }
		else if (Keyboard::isKeyPressed(Keyboard::Down)) { dx = 0; dy = 1; }

		// end game
		if (gameover) continue;

		// move main tile
		if (timer > delay)
		{
			x += dx;
			y += dy;

			// def limit
			if (x < 0) x = 0;
			if (x > N - 1) x = N - 1;
			if (y < 0) y = 0;
			if (y > M - 1) y = M - 1;

			// verifi if player lose
			if (grid[y][x] == 2) gameover = true;

			// define this tile as used
			if (grid[y][x] == 0) grid[y][x] = 2;

			timer = 0;
		}
		for (int i = 0; i < enemyCount; i++)
			a[i].move();

		if (grid[y][x] == 1)
		{
			dx = dy = 0;
			for (int i = 0; i < enemyCount; i++)
				drop(a[i].y / TS, a[i].x / TS);

			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					if (grid[i][j] == -1)
						grid[i][j] = 0;
					else
						grid[i][j] = 1;

		}
		for (int i = 0; i < enemyCount; i++)
			if (grid[a[i].y / TS][a[i].x / TS] == 2)
				gameover = true;

		////////draw////////////
		window.clear(Color::Black);
		// grig
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
			{
				if (grid[i][j] == 0) continue;
				else if (grid[i][j] == 1) sTile.setTextureRect(IntRect(0, 0, TS, TS));
				else if (grid[i][j] == 2) sTile.setTextureRect(IntRect(54, 0, TS, TS));
				sTile.setPosition(j * TS, i * TS);
				window.draw(sTile);
			}

		// main tile
		sTile.setTextureRect(IntRect(36, 0, TS, TS));
		sTile.setPosition(x * TS, y * TS);
		window.draw(sTile);

		// draw enemys
		sEnemy.rotate(10);
		for (int i = 0; i < enemyCount; i++)
		{

			sEnemy.setPosition(a[i].x, a[i].y);
			window.draw(sEnemy);
		}

		// last thing to be draw if lose
		if (gameover)
			window.draw(sGameOver);

		window.display();
	}
	return 0;
}