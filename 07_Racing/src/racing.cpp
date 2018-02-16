#include <SFML/Graphics.hpp>

using namespace sf;

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

	float x = 300.f, y = 300.f;
	float speed = 0.f, angle = 0.f;
	float maxSpeed = 12.f;
	float acc = 0.2f, dec = 0.3f;
	float turnSpeed = 0.08f;


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

		x += sin(angle) * speed;
		y -= cos(angle) * speed;

		/////draw/////
		app.clear(Color::White);
		app.draw(sBackground);


		sCar.setPosition(x, y);
		sCar.setRotation(angle * 180 / 3.141592);
		sCar.setColor(Color::Red);
		app.draw(sCar);

		app.display();
	}

	return 0;
}