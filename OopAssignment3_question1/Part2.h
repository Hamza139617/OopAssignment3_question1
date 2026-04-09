#pragma once
class Organism;

struct Tile
{
	float nutrientLevel;
	float toxicity;
	Organism* occupant;
};

class World
{
	Tile** tiles;
	Organism** orgs;
	int width, height;
	int orgCount;
	int orgCap;
public:

	World(int h, int w)
	{
		this->height = h, this->width = w;
		tiles = new Tile * [h];
		for (int i = 0; i < h; i++)
		{
			tiles[i] = new Tile [w];
		}
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				tiles[i][j].nutrientLevel = (float)((rand() % 100001)) / 1000.0f;
				tiles[i][j].toxicity = (float)((rand() % 100001)) / 1000.0f;
			}
		}
		orgCap = 10;
		orgCount = 0;
		orgs = new Organism * [orgCap];
	}
	void runIteration()
	{

	}
	
	~World()
	{
		for (int i = 0; i < height; i++)
			delete[] tiles[i];
		delete[] tiles;

		for (int i = 0; i < orgCount; i++)
			delete orgs[i];
		delete[] orgs;
	}
};