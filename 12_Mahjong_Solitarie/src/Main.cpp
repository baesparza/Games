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

bool isOpen(int x, int y, int z)
{
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
			if (f(x + 2, y + i, z) > 0 && f(x - 2, y + j, z) > 0)
				return false;

	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
			if (f(x + i, y + j, z + 1) > 0)
				return false;

	return true;
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
	const float offX = 4.6f, offY = 7.1f; // z offset 

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

	//////shufle//////
	for (int k = 1; ; k++)
	{
		std::vector<sf::Vector3i> opens;
		for (int z = 0; z < 10; z++)
			for (int y = 0; y < 18; y++)
				for (int x = 0; x < 30; x++)
					if (f(x, y, z) > 0 && isOpen(x, y, z))
						opens.push_back(sf::Vector3i(x, y, z));

		int n = opens.size();
		if (n < 2)
			break;
		int a = 0, b = 0;
		while (a == b)
		{
			a = rand() % n;
			b = rand() % n;
		}
		f(opens[a]) = -k;
		f(opens[b]) = -k;
		k %= 42;
	}

	for (int z = 0; z < 10; z++)
		for (int y = 0; y < 18; y++)
			for (int x = 0; x < 30; x++)
				f(x, y, z) *= -1;

	sf::Vector3i v1, v2;

	while (app.isOpen())
	{
		sf::Event e;
		while (app.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				app.close();

			if (e.key.code == sf::Mouse::Left)
				for (int z = 0; z < 10; z++)
				{
					sf::Vector2i pos = sf::Mouse::getPosition(app);
					int x = (pos.x - z * offX) / stepX;
					int y = (pos.y + z * offY) / stepY;

					for (int i = 0; i < 2; i++)
						for (int j = 0; j < 2; j++)
							if (f(x - i, y - j, z) > 0 && isOpen(x - i, y - j, z))
								v1 = sf::Vector3i(x - i, y - j, z);

					if (v1 == v2)
						continue;

					int a = f(v1), b = f(v2);
					if (a == b)
					{
						f(v1) *= -1;
						f(v2) *= -1;
					}
					v2 = v1;

				}

		}

		//////////draw//////////
		app.clear();
		app.draw(sBackground);

		for (int z = 0; z < 10; z++)
			for (int x = 30; x >= 0; x--)
				for (int y = 0; y < 18; y++)
				{
					int k = f(x, y, z) - 1;
					if (k < 0)
						continue;
					sTile.setTextureRect(sf::IntRect(k * W, 0, W, H));
					sTile.setPosition(x * stepX + z * offX, y * stepY - z * offY);

					app.draw(sTile);
				}
				app.display();
	}

	return 0;
}