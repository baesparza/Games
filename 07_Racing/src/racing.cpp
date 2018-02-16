#include <SFML/Graphics.hpp>

using namespace sf;

struct Car
{
	float x, y, speed, angle;

	Car() : speed(2), angle(0)
	{
	}

	void move()
	{
		x += sin(angle) * speed;
		y -= cos(angle) * speed;
		angle += 0.08f;
	}
};

int main()
{
	RenderWindow app(VideoMode(640, 480), "Racing");
	app.setFramerateLimit(60);

	Texture t1, t2;
	t1.loadFromFile("./assets/images/background.png");
	t2.loadFromFile("./assets/images/car.png");

	Sprite sBackground(t1), sCar(t2);

	sCar.setPosition(300, 300);
	sCar.setOrigin(22, 22);

	const unsigned int N = 5;
	Car cars[N];
	for (int i = 0; i < N; i++)
	{
		cars[i].x = 300 + i * 50;
		cars[i].y = 300 + i * 80;
		cars[i].speed = 7 + i;
	}


	float x = 300.f, y = 300.f;
	float speed = 0.f, angle = 0.f;
	float maxSpeed = 12.f;
	float acc = 0.2f, dec = 0.3f;
	float turnSpeed = 0.08f;

	int offsetX = 0, offsetY = 0;


	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();
		}

		bool Up = 0, Right = 0, Down = 0, Left = 0;
		if (Keyboard::isKeyPressed(Keyboard::Up)) Up = 1;
		if (Keyboard::isKeyPressed(Keyboard::Right)) Right = 1;
		if (Keyboard::isKeyPressed(Keyboard::Down)) Down = 1;
		if (Keyboard::isKeyPressed(Keyboard::Left)) Left = 1;


		//car movement//
		if (Up && speed < maxSpeed)
			speed += (speed < 0) ? dec : acc;
		if (Down && speed > -maxSpeed)
			speed -= (speed > 0) ? dec : acc;
		if (!Up && !Down)
		{
			if (speed - dec > 0)
				speed -= dec;
			else if (speed + dec < 0)
				speed += dec;
			else
				speed = 0;
		}
		if (Right && speed != 0)
			angle += turnSpeed * speed / maxSpeed;
		if (Left && speed != 0)
			angle -= turnSpeed * speed / maxSpeed;


		cars[0].speed = speed;
		cars[0].angle = angle;


		for (int i = 0; i < N; i++) cars[i].move();

		float R = 22;
		// colision
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
			{
				int dx = cars[i].x - cars[j].x;
				int dy = cars[i].y - cars[j].y;
				if (dx*dx + dy*dy < 4 * R*R)
				{
					cars[i].x += dx / 10;
					cars[i].y += dy / 10;
					cars[j].x -= dx / 10;
					cars[j].y -= dy / 10;
				}
			}


		if (cars[0].x > 320) offsetX = cars[0].x - 320;
		if (cars[0].y > 240) offsetY = cars[0].y - 240;

		/////draw/////
		app.clear(Color::White);
		sBackground.setPosition(-offsetX, -offsetY);
		app.draw(sBackground);

		Color colors[5] = {Color::Red, Color::Green, Color::Magenta, Color::Blue, Color::White};

		for (int i = 0; i < N; i++)
		{
			sCar.setPosition(cars[i].x - offsetX, cars[i].y - offsetY);
			sCar.setRotation(cars[i].angle * 180 / 3.141592);
			sCar.setColor(colors[i]);
			app.draw(sCar);
		}

		app.display();
	}

	return 0;
}