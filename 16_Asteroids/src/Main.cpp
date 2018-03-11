#include <SFML/Graphics.hpp>
#include <iostream>

const int W = 1200, H = 800;

const float DEGTORAD = 0.017453f;

class Animation
{
public:
	Animation()
	{ }

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

public:
	float m_frame, m_speed;
	sf::Sprite m_sprite;
	std::vector<sf::IntRect> m_frames;
};

class Entity
{
public:
	Entity() : m_life(1)
	{ }

	void settings(Animation &a, int x, int y, float angle = 0, int radius = 1)
	{
		m_anim = a;
		m_x = x;
		m_y = y;
		m_angle = angle;
		m_radius = radius;
	}

	virtual void update() {};

	void draw(sf::RenderWindow& app)
	{
		m_anim.m_sprite.setPosition(m_x, m_y);
		m_anim.m_sprite.setRotation(m_angle + 90);
		app.draw(m_anim.m_sprite);
	}

public:
	float m_x, m_y, m_dx, m_dy, m_radius, m_angle;
	bool m_life;
	std::string m_name;
	Animation m_anim;
};

class Asteroid : public Entity
{
public:
	Asteroid()
	{
		m_dx = rand() % 8 - 4;
		m_dy = rand() % 8 - 4;
		m_name = "Asteroids";
	}

	void update()
	{
		m_x += m_dx;
		m_y += m_dy;
		if (m_x > W) m_x = 0;
		if (m_x < 0) m_x = W;
		if (m_y > H) m_y = 0;
		if (m_y < 0) m_y = H;
	}
};


int main()
{
	srand(time(0));

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

	std::vector <Entity *> entities;

	for (int i = 0; i < 15; i++)
	{
		entities.push_back(new Asteroid());
		entities[i]->settings(sRock, rand() % W, rand() % H, rand() % 360, 25);
	}


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

		for (auto i = entities.begin(); i != entities.end();)
		{
			Entity *e = *i;
			e->update();
			e->m_anim.update();
			if (!e->m_life)
			{
				i = entities.erase(i);
				delete e;
			}
			else i++;
		}


		/////draw/////
		app.clear();
		app.draw(sBackground);
		for (auto e : entities) e->draw(app);
		app.draw(sPlayer);
		app.display();
	}

	return 0;
}