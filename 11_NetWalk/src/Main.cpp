#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

const int N = 6;
const int TS = 54; // tile size
Vector2f offset(65, 55);

struct Pipe
{
	int orientation;
	bool on;
} grid[N][N];

int main()
{
	RenderWindow app(VideoMode(390, 390), "The Pipe Puzzle");

	Texture t1, t2;
	t1.loadFromFile("./images/background.png");
	t2.loadFromFile("./images/pipes.png");

	Sprite sBackground(t1), sPipe(t2);
	sPipe.setOrigin(TS / 2, TS / 2);

	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
			if (e.type == Event::Closed)
				app.close();

		app.clear();
		app.draw(sBackground);
		
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
			{
				sPipe.setTextureRect(IntRect(TS * 2, 0, TS, TS));
				sPipe.setRotation(grid[j][i].orientation);
				sPipe.setPosition(j * TS, i * TS);
				sPipe.move(offset);
				app.draw(sPipe);
			}
		
		app.display();
	}

	return 0;
}