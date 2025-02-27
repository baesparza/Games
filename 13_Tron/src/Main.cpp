#include <SFML/Graphics.hpp>
#include <time.h>

const int W = 600, H = 480;
int speed = 4;
bool field[W][H] = {0};

struct Player
{
	int x, y, dir;
	sf::Color color;
	Player(sf::Color c) : color(c)
	{
		x = rand() % W;
		y = rand() % H;
		dir = rand() % 4;
	}

	void tick()
	{
		//		^
		//		3
		//	< 1 + 2 >
		//		0
		//		v
		if (dir == 0) y += 1;
		if (dir == 1) x -= 1;
		if (dir == 2) x += 1;
		if (dir == 3) y -= 1;

		if (x >= W) x = 0;
		if (x < 0) x = W - 1; 
		if (y >= H) y = 0;
		if (y < 0) y = H - 1;
	}
};

int main()
{
	srand(time(0));

	sf::RenderWindow app(sf::VideoMode(W, H), "TRON");
	app.setFramerateLimit(60);

	sf::Texture t1;
	t1.loadFromFile("./assets/images/background.jpg");

	sf::Sprite sBackground(t1);

	Player p1(sf::Color::Blue), p2(sf::Color::Red);

	sf::Sprite sprite;
	sf::RenderTexture t;
	t.create(W, H);
	t.setSmooth(true);
	sprite.setTexture(t.getTexture());
	t.clear();
	t.draw(sBackground);

	sf::Font font;
	font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
	sf::Text text("You Win", font, 35);
	text.setPosition(W / 2 - 80, 20);

	sf::Shader * shader = new sf::Shader;
	shader->loadFromFile("./assets/shader.frag", sf::Shader::Fragment);
	shader->setParameter("frag_ScreenResolution", sf::Vector2f(W, H));
	shader->setParameter("frag_LightAttenuation", 100);

	sf::RenderStates states; 
	states.shader = shader;

	bool game = true;

	while (app.isOpen())
	{
		sf::Event e;
		while (app.pollEvent(e))
		{
			using key = sf::Keyboard;

			if (e.type == sf::Event::Closed) app.close();

			// player 1
			if (key::isKeyPressed(key::Left)) if (p1.dir != 2) p1.dir = 1;
			if (key::isKeyPressed(key::Right)) if (p1.dir != 1) p1.dir = 2;
			if (key::isKeyPressed(key::Up)) if (p1.dir != 0) p1.dir = 3;
			if (key::isKeyPressed(key::Down)) if (p1.dir != 3) p1.dir = 0;

			// player 2
			if (key::isKeyPressed(key::A)) if (p2.dir != 2) p2.dir = 1;
			if (key::isKeyPressed(key::D)) if (p2.dir != 1) p2.dir = 2;
			if (key::isKeyPressed(key::W)) if (p2.dir != 0) p2.dir = 3;
			if (key::isKeyPressed(key::S)) if (p2.dir != 3) p2.dir = 0;
		}
		
		if (!game) // when lose, stop game
		{
			app.draw(text);
			app.display();
			continue;
		}

		for (int i = 0; i < speed; i++)
		{
			p1.tick();
			p2.tick();

			if (field[p1.x][p1.y] == 1 || field[p2.x][p2.y] == 1)
			{
				game = false;
				text.setFillColor((field[p1.x][p1.y] == 1) ? p2.color : p1.color); // the oposite that cashed
			}

			field[p1.x][p1.y] = field[p2.x][p2.y] = 1;

			t.display();

			shader->setParameter("frag_LightOrigin", sf::Vector2f(p1.x, p1.y));
			shader->setParameter("frag_LightColor", p1.color);
			t.draw(sprite, states);
			shader->setParameter("frag_LightOrigin", sf::Vector2f(p2.x, p2.y));
			shader->setParameter("frag_LightColor", p2.color);
			t.draw(sprite, states);
		}

		/////////draw/////////
		app.clear();
		app.draw(sprite);
		app.display();
	}

	return 0;
}