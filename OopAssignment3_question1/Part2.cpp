#include"Part2.h"
#include"part3.h"


void World::addNewOrg(Organism* org)
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

void World::removeDead() //for removing dead organisms before next iteration
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

int World::getFractalCount()
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

void World::runIteration()
{
	for (int i = 0; i < orgCount; i++)
	{
		orgs[i]->update(tiles, width, height);
	}
	removeDead();
	display();
}

void World::display()
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
	std::cout << "Average World Toxicity: " << sum / (height * width);	// print average toxicity
}