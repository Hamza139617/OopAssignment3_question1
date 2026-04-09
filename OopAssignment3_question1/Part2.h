#pragma once
#include<ctime>
class Organism;

struct Tile
{
	float nutrientLevel;
	float toxicity;
	Organism* occupant;

	float getNutrientLevel() const { return nutrientLevel; }
	float getToxicity()const { return toxicity; }
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
		srand(time(0));
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
				tiles[i][j].occupant = nullptr;
			}
		}
		orgCap = 10;
		orgCount = 0;
		orgs = new Organism * [orgCap];
	}
	void addNewOrg()
	{
		if (orgCap == orgCount)
		{
			orgCap *= 2;
			Organism** temp = new Organism*[orgCap];
			delete[] orgs;
			orgs = temp;
		}
		
		orgs[orgCount] = new Organism;
		orgCount++;
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