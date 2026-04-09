#pragma once


class Tile;


class Organism {

protected:
	int x, y, width, height;
	bool** internalShape = nullptr ;
	bool specie = false; // type of the organism initially false meaning fractalSprawler and true meaning kineticHunter 
	int maxSize = 5;
	
	float getAverageNutrients(Tile** world) {

	}

public:
	Organism(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {

		

		internalShape = new bool* [maxSize];	// when the organism is created the internalShape initially should be 2x2

		for (int i = 0; i < maxSize; i++) {
			internalShape[i] = new bool[maxSize];
		}

		for (int i = 0; i < width; i++) {

			for (int j = 0; j < height ; j++) {
				internalShape[i][j] = true;
			}

		}

		

	}

	Organism() : x(0), y(0), width(0), height(0) {

		

		internalShape = new bool* [maxSize];	

		for (int i = 0; i < maxSize; i++) {
			internalShape[i] = new bool[maxSize];
		}

		for (int i = 0; i < width; i++) {

			for (int j = 0; j < height; j++) {
				internalShape[i][j] = true;
			}

		}



	}

	virtual void update(Tile** word, int worldWidth, int worldHeight);

	~Organism() {

		for (int i = 0; i < maxSize; i++) {
			delete[] internalShape[i];
		}

		delete[] internalShape;

	}

};

class FractalSprawler: public Organism {

public:
	FractalSprawler(int x, int y, int width, int height) : Organism(x, y, width, height) {
		this->specie = false;
	}

	FractalSprawler() {
		this->specie = false;
	}

	~FractalSprawler() {

	}
	
};

class KineticHunter: public Organism {

public:
	KineticHunter(int x, int y, int width, int height) : Organism(x, y, width, height) {
		this->specie = true;
	}

	KineticHunter() {
		this->specie = true;
	}

};
