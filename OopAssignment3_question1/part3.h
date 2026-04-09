#pragma once


class Tile;


class Organism {

protected:
	int x, y, width, height;
	bool** internalShape;

	virtual void update(Tile** word, int worldWidth, int worldHeight);

	float getAverageNutrients(Tile** world);

};

class FractalSprawler {
	
};

class KineticHunter {

};
