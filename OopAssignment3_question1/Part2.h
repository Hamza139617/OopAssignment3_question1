#pragma once
#include<iostream>
#include<ctime>
class Organism;
// Ansi escape sequences 
const char* GREEN = "\033[32m";
const char* RED = "\033[31m";
const char* BLACK = "\033[30m";
const char* RESET = "\033[0m";
const char* SQUARE = "#"; // instead of the actual square we will be using the hashtag

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

	void addNewOrg(Organism* org)
	{
		if (orgCap == orgCount) //if capacity gets full
		{
			orgCap *= 2;
			Organism** temp = new Organism * [orgCap];
			for (int i = 0; i < orgCount; i++)
			{
				temp[i] = orgs[i];
			}
			delete[]  orgs;
			orgs = temp;
		}

		orgs[orgCount] = org;
		orgCount++;
	}
	void removeDead() //for removing dead organisms before next iteration
	{
		int count = 0;
		for (int i = 0; i < orgCount; i++)
		{
			if (orgs[i]->isAlive())
				orgs[count++] = orgs[i];
			else
				delete orgs[i];
		}
		orgCount = count;
	}
	int getFractalCount()
	{
		int c=0;
		for (int i = 0; i < orgCount; i++)
		{
			if (orgs[i]->getSpecie() && orgs[i]->isAlive())
			{
				c++;
			}
		}
		return c;
	}
	void display()
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (tiles[i][j].occupant == nullptr)
					std::cout << "\033[40m#\033[0m";  // black for empty
				else
				{
					if (tiles[i][j].occupant->getSpecie())
					{
						std::cout << "\033[31m#\033[0m";  // red for kinetic hunter
					}
					else
					{
						std::cout << "\033[32m#\033[0m";  // green for fractal spawner
					}
				}
			}
			std::cout << std::endl;
		}
		std::cout << "Total Population: " << orgCount;
		std::cout << std::endl;
		float sum = 0;
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				sum += tiles[i][j].getToxicity(); 
			}
		}
		std::cout << "Average World Toxicity: " << sum / (height*width);	// print average toxicity
	}
	void runIteration()
	{
		for (int i = 0; i < orgCount; i++)
		{
			orgs[i]->update(tiles, width, height);
		}
		removeDead();
		display();
	}

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