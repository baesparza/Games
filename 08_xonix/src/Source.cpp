#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

const unsigned int M = 20, N = 40;

int grid[M][N];
const unsigned int TS = 18; // tile size


int main()
{
	srand(time(0));

	RenderWindow window(VideoMode(N * TS, M * TS), "XONIX");

	// load texture
	Texture t1, t2, t3;
	t1.loadFromFile("./assets/images/tiles.png");
	t2.loadFromFile("./assets/images/enemy.png");
	t3.loadFromFile("./assets/images/gameover.png");

	Sprite sTile(t1), sEnemy(t2), sGameOver(t3);
	sGameOver.setPosition(100, 100);

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

		// last thing to be draw if lose
		if (gameover) 
			window.draw(sGameOver);

		window.display();
	}
	return 0;
}