#include <SFML/Graphics.hpp>

const int W = 1200, H = 800;

const float DEGTORAD = 0.017453f;

int main()
{
	sf::RenderWindow app(sf::VideoMode(W, H), "Asteroids");
	app.setFramerateLimit(60);

	sf::Texture t1, t2;

	t1.loadFromFile("./images/spaceship.png");
	t2.loadFromFile("./images/background.jpg");

	sf::Sprite sPlayer(t1), sBackground(t2);

	sPlayer.setTextureRect(sf::IntRect(40,0,40,40));
	sPlayer.setOrigin(20, 20);

	float x = 300, y = 300;
	float dx = 0, dy = 0, angle = 0;
	bool thrust;



	while (app.isOpen())
	{
		sf::Event e;

		while (app.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				app.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) angle += 3;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) angle -= 3;
		thrust = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);

		/////space ship movement/////
		if (thrust)
		{
			dx += std::cos(angle * DEGTORAD) * 0.2;
			dy += std::sin(angle * DEGTORAD) * 0.2;
		}
		else
		{
			dx *= 0.99;
			dy *= 0.99;
		}

		int maxSpeed = 15;
		float speed = std::sqrt(dx * dx + dy * dy);
		if (speed > maxSpeed)
		{
			dx *= maxSpeed / speed;
			dy *= maxSpeed / speed;
		}

		x += dx;
		y += dy;

		if (x > W) x = 0;
		if (x < 0) x = W;
		if (y > H) y = 0;
		if (y < 0) y = H;

		sPlayer.setPosition(x, y);
		sPlayer.setRotation(angle + 90);

		/////draw/////
		app.clear();

		app.draw(sBackground);
		app.draw(sPlayer);
		app.display();
	}

	return 0;
}