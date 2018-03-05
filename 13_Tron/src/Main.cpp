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
		if (dir == 0) y += 1;
		if (dir == 1) x -= 1;
		if (dir == 2) x += 1;
		if (dir == 3) y -= 1;

		if (x >= W) x = 0;
		if (x < 0) x = W - 1; 
		if (y >= H) y = 0;
		if (y < 0) y = H - 1;
	}

	sf::Color & getColor()
	{
		return color;
	}
};

int main()
{
	return 0;
}