#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

int main()
{
	RenderWindow app(VideoMode(520, 450), "Arkanoid Game!");

	app.setFramerateLimit(60);

	Texture t1, t2, t3, t4;
	t1.loadFromFile("./assets/images/block01.png");
	t2.loadFromFile("./assets/images/background.jpg");
	t3.loadFromFile("./assets/images/ball.png");
	t4.loadFromFile("./assets/images/paddle.png");

	Sprite sBackground(t2), sBall(t3), sPaddle(t4);

	sPaddle.setPosition(300, 440);
	sBall.setPosition(300, 300);

	Sprite blocks[100];

	int n = 0;
	//set blocks to be destroyed//
	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++)
		{
			blocks[n].setTexture(t1);
			blocks[n].setPosition(i * 43, j * 20);
			n++;
		}

	float dx = 6.f, dy = 5.f;

	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				app.close();
			}
		}


		//ball movement//
		sBall.move(dx, dy);
		Vector2f b = sBall.getPosition();
		if (b.x < 0 || b.x > 520) dx = -dx;
		if (b.y < 0 || b.y > 450) dy = -dy;

		////draw////
		app.clear();
		app.draw(sBackground);
		app.draw(sBall);
		app.draw(sPaddle);
		for (auto block : blocks) // draw blocks
			app.draw(block);


		app.display();

	}

	return 0;
}