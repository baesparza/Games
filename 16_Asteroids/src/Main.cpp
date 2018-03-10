#include <SFML/Graphics.hpp>
#include "Main.h"

const int W = 1200, H = 800;

const float DEGTORAD = 0.017453f;

class Animation
{
public:
	Animation(sf::Texture &t, int x, int y, int w, int h, int count, float speed) :
		m_speed(speed), m_frame(0.f)
	{
		for (int i = 0; i < count; i++)
			m_frames.push_back(sf::IntRect(x + i * w, y, w, h));

		m_sprite.setTexture(t);
		m_sprite.setPosition(w / 2, h / 2);
		m_sprite.setTextureRect(m_frames[0]);
	}

	void update()
	{
		m_frame += m_speed;
		int n = m_frames.size();
		if (m_frame >= n) m_frame -= n;
		if (n > 0) m_sprite.setTextureRect(m_frames[int(m_frame)]);
	}

	void setPosition(int x, int y)
	{
		m_sprite.setPosition(x, y);
	}

	sf::Sprite& getSprite()
	{
		return m_sprite;
	}

private:
	float m_frame, m_speed;
	sf::Sprite m_sprite;
	std::vector<sf::IntRect> m_frames;
};


int main()
{
	sf::RenderWindow app(sf::VideoMode(W, H), "Asteroids");
	app.setFramerateLimit(60);

	sf::Texture t1, t2, t3;

	t1.loadFromFile("./images/spaceship.png");
	t2.loadFromFile("./images/background.jpg");
	t3.loadFromFile("./images/rock.png");

	sf::Sprite sPlayer(t1), sBackground(t2);
	sPlayer.setTextureRect(sf::IntRect(40, 0, 40, 40));
	sPlayer.setOrigin(20, 20);

	Animation sRock(t3, 0, 0, 64, 64, 16, 0.2);

	sRock.setPosition(400, 400);

	float frame = 0, animSpeed = 0.4, framecount = 20;

	// ship
	float x = W / 2, y = H / 2;
	float dx = 0, dy = 0, angle = 0;
	bool thrust;



	while (app.isOpen())
	{
		sf::Event e;
		while (app.pollEvent(e))
			if (e.type == sf::Event::Closed)
				app.close();


		//////sprite animation/////
		frame += animSpeed;
		if (frame > framecount) frame = -framecount;

		/////keyboard/////
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

		////teleport
		if (x > W) x = 0;
		if (x < 0) x = W;
		if (y > H) y = 0;
		if (y < 0) y = H;

		sPlayer.setPosition(x, y);
		sPlayer.setRotation(angle + 90); // to aling ship with dir


		sRock.update();
		/////draw/////
		app.clear();

		app.draw(sBackground);
		app.draw(sRock.getSprite());
		app.draw(sPlayer);
		app.display();
	}

	return 0;
}