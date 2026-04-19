#include"Part2.h"
#include"part3.h"

// Ansi escape sequences 
const char* GREEN = "\033[32m";
const char* RED = "\033[31m";
const char* BLACK = "\033[30m";
const char* RESET = "\033[0m";
const char* SQUARE = "#"; // instead of the actual square we will be using the hashtag

Tile::Tile()
{
	occupant = nullptr;
	nutrientLevel = 0;
	toxicity = 0;
}
void World::addNewOrg(Organism* org)
{
	
	if (orgCap == orgCount) {
		orgCap *= 2;
		Organism** temp = new Organism * [orgCap];

		for (int i = 0; i < orgCount; i++) temp[i] = orgs[i];
		delete[] orgs;
		orgs = temp;

	}

	int ox = org->getX();
	int oy = org->getY();
	int ow = org->getWidth();
	int oh = org->getHeight();

	if (ox < 0 || oy < 0 || ox + ow > height || oy + oh > width) {
		delete org;
		return;
	}

	for (int i = ox; i < ox + ow; i++) {
		for (int j = oy; j < oy + oh; j++) {
			if (tiles[i][j].occupant != nullptr) {
				delete org;
				return;
			}
		}
	}

	for (int i = ox; i < ox + ow; i++) {
		for (int j = oy; j < oy + oh; j++) {
			tiles[i][j].occupant = org;
		}
	}

	orgs[orgCount++] = org;
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
		if (!orgs[i]->getSpecie() && orgs[i]->isAlive())
		{
			c++;
		}
	}
	return c;
}

void World::runIteration()
{

	for (int i = 0; i < orgCount; i++) {
		orgs[i]->update(tiles, width, height);
	}

	for (int r = 0; r < height; r++) {
		for (int c = 0; c < width; c++) {
			if (tiles[r][c].occupant == nullptr) {
				tiles[r][c].toxicity -= 0.2f;
			}
			else if (tiles[r][c].occupant->getSpecie()) {
				tiles[r][c].toxicity += 0.3f;
			}
			else {
				tiles[r][c].toxicity -= 0.1f;
			}

			if (tiles[r][c].toxicity < 0.0f) tiles[r][c].toxicity = 0.0f;
			if (tiles[r][c].toxicity > 100.0f) tiles[r][c].toxicity = 100.0f;
		}
	}

	for (int r = 0; r < height; r++) {

		for (int c = 0; c < width; c++) {
			Organism* occ = tiles[r][c].occupant;
			if (occ == nullptr) continue;

			bool alreadyTracked = false;

			for (int k = 0; k < orgCount; k++) {

				if (orgs[k] == occ) {
					alreadyTracked = true;
					break;
				}

			}

			if (!alreadyTracked) {

				if (orgCap == orgCount) {
					orgCap *= 2;
					Organism** temp = new Organism * [orgCap];
					for (int t = 0; t < orgCount; t++) temp[t] = orgs[t];
					delete[] orgs;
					orgs = temp;

				}

				orgs[orgCount++] = occ;
			}
		}
	}
	
	removeDead();
	display();
}

World::~World() {

	for (int i = 0; i < height; i++)
		delete[] tiles[i];
	delete[] tiles;

	for (int i = 0; i < orgCount; i++)
		delete orgs[i];
	delete[] orgs;
}

void World::display()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (tiles[i][j].occupant == nullptr)
			{
				std::cout << BLACK << "#" << RESET;  // black for empty
			}
			else if (tiles[i][j].occupant->getSpecie())
			{
				std::cout << RED<<"#"<<RESET;  // red for kinetic hunter
			}
			else
			{
				std::cout << GREEN<<"#"<<RESET;  // green for fractal spawner
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