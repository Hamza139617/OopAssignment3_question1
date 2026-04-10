#pragma once
#include<iostream>
#include<ctime>

class Organism;
struct Tile
{
	float nutrientLevel;
	float toxicity;
	Organism* occupant;
	Tile()
	{
		occupant = nullptr;
		nutrientLevel = 0;
		toxicity = 0;
	}
	Tile(float n, float t, Organism* o) :nutrientLevel(n), toxicity(t), occupant(o) {}
	float getNutrientLevel() const { return nutrientLevel; }
	float getToxicity()const { return toxicity; }
};

class World
{
	Tile** tiles; //2D array of tiles
	Organism** orgs; //2D array of corresponding organisms
	int width, height; //for tiles
	int orgCount; //population
	int orgCap; 
public:
	//constructor
	World(int h, int w):height(h),width(w),tiles(new Tile*[h]), orgCap(10),orgCount(0)
	{
		orgs = new Organism* [orgCap]; 
		srand(time(0));
		for (int i = 0; i < h; i++)
		{
			tiles[i] = new Tile [w];
		}
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				tiles[i][j].nutrientLevel = (float)((rand() % 10001)) / 100.0f; //random float values between 0 adn 100
				tiles[i][j].toxicity = (float)((rand() % 10001)) / 100.0f; //random float values between 0 adn 100
				tiles[i][j].occupant = nullptr; //initially no org there
			}
		}
	}

	void addNewOrg(Organism* org);
	void removeDead(); //for removing dead organisms before next iteration
	int getFractalCount();
	void runIteration();
	void display();


	//getters
	int getOrgCount()const { return orgCount; }
	int getOrgCapacity()const { return orgCap; }
	int getH()const { return height; }
	int getW()const { return width; }

	//destructor
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