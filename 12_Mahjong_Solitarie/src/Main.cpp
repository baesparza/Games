#include<time.h>
#include<fstream>
#include <SFML/Graphics.hpp>

int field[50][50][50] = {0};

int & f(int x, int y, int z)
{
	return field[y + 2][x + 2][z];
}

int & f(sf::Vector3i v)
{
	return f(v.x, v.y, v.z);
}

int main()
{
	sf::RenderWindow app(sf::VideoMode(740, 570), "Mahjong Solitarie");

	sf::Texture t1, t2;
	t1.loadFromFile("./assets/images/background.png");
	t2.loadFromFile("./assets/images/tiles.png");

	sf::Sprite sBackground(t1), sTile(t2);

	const int W = 48, H = 66;
	const int stepX = W / 2 - 2, stepY = H / 2 - 2;

	///////////load from file//////
	std::fstream file("./assets/map.txt");
	for (int y = 0; y < 18; y++)
		for (int x = 0; x < 30; x++)
		{
			char a;
			file >> a;
			int n = a - '0';
			for (int z = 0; z < n; z++)
				if (f(x - 1, y - 1, z))
					f(x - 1, y, z) = f(x, y - 1, z) = 0;
				else
					f(x, y, z) = 1;
		}

	while (app.isOpen())
	{
		sf::Event e;
		while (app.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				app.close();
		}

		//////////draw//////////
		app.clear();
		app.draw(sBackground);

		for (int z = 0; z < 10; z++)
			for (int x = 30; x >= 0; x--)
				for (int y = 0; y < 18; y++)
				{
					int k = f(x, y, z);
					if (k == 0)
						continue;
					sTile.setTextureRect(sf::IntRect(k * W, 0, W, H));
					sTile.setPosition(x * stepX, y * stepY);

					app.draw(sTile);
				}
				app.display();
	}

	return 0;
}