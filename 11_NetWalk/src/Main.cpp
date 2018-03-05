#include <vector>
#include <time.h>

#include <SFML/Graphics.hpp>

const int N = 6;
const int TS = 54; // tile size
sf::Vector2f offset(65, 55);

sf::Vector2i Up(0, -1);
sf::Vector2i Down(0, 1);
sf::Vector2i Right(1, 0);
sf::Vector2i Left(-1, 0);

sf::Vector2i DIR[4] = {Up, Down, Right, Left};

struct Pipe
{
	std::vector<sf::Vector2i> dirs;
	int orientation;
	float angle;
	bool on;

	Pipe() : angle(0)
	{ }

	void rotate()
	{
		for (int i = 0; i < dirs.size(); i++)
			if (dirs[i] == Up)
				dirs[i] = Right;
			else if (dirs[i] == Right)
				dirs[i] = Down;
			else if (dirs[i] == Down)
				dirs[i] = Left;
			else if (dirs[i] == Left)
				dirs[i] = Up;
	}

	bool isConnect(sf::Vector2i dir)
	{
		for (sf::Vector2i d : dirs)
			if (d == dir) return true;
		return false;
	}

} grid[N][N];

Pipe & cell(sf::Vector2i v)
{
	return grid[v.x][v.y];
}

bool isOut(sf::Vector2i v)
{
	return !sf::IntRect(0, 0, N, N).contains(v);
}

void generatePuzze()
{
	std::vector<sf::Vector2i> nodes;
	nodes.push_back(sf::Vector2i(rand() % N, rand() % N));
	while (!nodes.empty())
	{
		int n = rand() % nodes.size();
		sf::Vector2i v = nodes[n];
		sf::Vector2i d = DIR[rand() % 4];

		if (cell(v).dirs.size() == 3)
		{
			nodes.erase(nodes.begin() + n);
			continue;
		}

		bool complete = true;
		for (auto D : DIR)
			if (!isOut(v + D) && cell(v + D).dirs.empty())
				complete = false;
		if (complete)
		{
			nodes.erase(nodes.begin() + n);
			continue;
		}
		
		if (isOut(v + d))
			continue;
		if (!cell(v + d).dirs.empty())
			continue;
		cell(v).dirs.push_back(d);
		cell(v + d).dirs.push_back(-d);
		nodes.push_back(v + d);

	}
}

int main()
{
	sf::RenderWindow app(sf::VideoMode(390, 390), "The Pipe Puzzle");
	app.setFramerateLimit(60);

	sf::Texture t1, t2;
	t1.loadFromFile("./images/background.png");
	t2.loadFromFile("./images/pipes.png");

	sf::Sprite sBackground(t1), sPipe(t2);
	sPipe.setOrigin(TS / 2, TS / 2);

	generatePuzze();

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			Pipe & p = grid[i][j];

			for (int n = 4; i > 0; n--) // find orientation
			{
				std::string s = "";
				for (auto d : DIR) s += p.isConnect(d) ? '1' : '0';
				if (s == "0011" || s == "0111" || s == "0101" || s == "0010")
					p.orientation = n;
				p.rotate();
			}
		}

	while (app.isOpen())
	{
		sf::Event e;
		while (app.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				app.close();

			if (e.type == sf::Event::MouseButtonPressed)
				if (e.key.code == sf::Mouse::Left)
				{
					sf::Vector2i pos = sf::Mouse::getPosition(app) + sf::Vector2i(TS / 2, TS / 2) - sf::Vector2i(offset);
					pos /= TS;
					grid[pos.x][pos.y].orientation++;
				}
		}


		/////draw/////
		app.clear();
		app.draw(sBackground);

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
			{
				Pipe & p = grid[i][j];

				int kind = p.dirs.size();
				if (kind == 2 && p.dirs[0] == -p.dirs[1])
					kind = 0;

				// smoth rotation
				p.angle += 5;
				if (p.angle > p.orientation * 90)
					p.angle = p.orientation * 90;

				// draw pipe
				sPipe.setTextureRect(sf::IntRect(TS * kind, 0, TS, TS));
				sPipe.setRotation(p.angle);
				sPipe.setPosition(j * TS, i * TS);
				sPipe.move(offset);
				app.draw(sPipe);
			}

		app.display();
	}

	return 0;
}