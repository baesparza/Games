#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

// veryfy fi to sprite are coliding
bool isCollide(const Sprite &s1, const Sprite &s2) 
{
	return s1.getGlobalBounds().intersects(s2.getGlobalBounds());
}

int main()
{
	srand(time(0));

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

	int n = 0; // number of blocks
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


		//////move and colitions(ball)////////
		// verify colition whit left or right side of block
		sBall.move(dx, 0);
		for (int i = 0; i < n; i++)
			if (isCollide(sBall, blocks[i]))
			{
				blocks[i].setPosition(-100, 0); // move block from visible screen, not from memory
				dx = -dx; // change direction
			}

		// verify colition with top or bottom of block
		sBall.move(0, dy);
		for (int i = 0; i < n; i++)
			if (isCollide(sBall, blocks[i]))
			{
				blocks[i].setPosition(-100, 0);
				dy = -dy;
			}

		Vector2f b = sBall.getPosition();
		// change direction of vector
		if (b.x < 0 || b.x > 520) dx = -dx;
		if (b.y < 0 || b.y > 450) dy = -dy;

		//////move platform///////
		if (Keyboard::isKeyPressed(Keyboard::Right)) sPaddle.move(6, 0);
		if (Keyboard::isKeyPressed(Keyboard::Left)) sPaddle.move(-6, 0);

		if (isCollide(sPaddle, sBall))
			dy = -(rand() % 5 + 2); // negative due to origin is top left


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