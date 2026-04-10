#pragma once


class Tile;


class Organism {

protected:
	int x, y, width, height;
	bool** internalShape = nullptr ;
	bool specie = false; // type of the organism initially false meaning fractalSprawler and true meaning kineticHunter 
	bool alive = false;
	
	float getAverageNutrients(Tile** world) {

	}

public:
	Organism(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {

		alive = true;

		internalShape = new bool* [width];	// when the organism is created the internalShape initially should be 2x2

		for (int i = 0; i < width; i++) {
			internalShape[i] = new bool[height];
		}

		for (int i = 0; i < width; i++) {

			for (int j = 0; j < height ; j++) {
				internalShape[i][j] = true;
			}

		}

		

	}

	Organism() : x(0), y(0), width(0), height(0) {

		alive = true;

		internalShape = new bool* [width];	

		for (int i = 0; i < width; i++) {
			internalShape[i] = new bool[height];
		}

		for (int i = 0; i < width; i++) {

			for (int j = 0; j < height; j++) {
				internalShape[i][j] = true;
			}

		}



	}


	// getters 

	int getX() const { return x; }
	int getY() const { return y; }
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	bool getSpecie() const { return specie; }
	bool isAlive() const { return alive; }



	virtual void update(Tile** word, int worldWidth, int worldHeight);

	~Organism() {

		for (int i = 0; i < width; i++) {
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
