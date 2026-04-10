#pragma once

#include "Part2.h"




class Organism {

protected:
	int x, y, width, height;
	bool** internalShape = nullptr ;
	bool specie = false; // type of the organism initially false meaning fractalSprawler and true meaning kineticHunter 
	bool alive = false;
	
	
	float getAverageNutrients(Tile** world) {

		int numTile = width * height; // total number of tiles covered by the organismm
		float sumOfNutrient = 0;

		for (int i = 0; i < width; i++) {

			for (int j = 0; j < height; j++) {

				sumOfNutrient += world[x + i][y + j].nutrientLevel;

			}

		}


		return sumOfNutrient / numTile;

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


	void update(Tile** world, int worldWidth, int worldHeight) {

		int centerX = (x + width) / 2;
		int centerY = (y + height) / 2;

		int startX = centerX - 1;
		int startY = centerY - 1;

		int endX = centerX + 1;
		int endY = centerY + 1;

		if (startX < worldWidth) startX = 0;
		if (startY < worldHeight) startY = 0;

		if (endX > worldWidth) endX = worldWidth - 1;
		if (endY > worldHeight) endY = worldHeight - 1;


		int countTiles = 0;
		float sumNutrient = 0;

		for (int i = startX; i < endX; i++) {

			for (int j = startY; j < endY; j++) {

				sumNutrient += world[i][j].nutrientLevel;
				countTiles++;

			}

		}

		float averageNutrient = sumNutrient / countTiles;

		if (averageNutrient > 70) {

			for (int i = 0; i < width; i++)
				delete[] internalShape[i];

			delete[] internalShape;

			width += 2;
			height += 2;

			if (width < 5 && height < 5) {

				internalShape = new bool* [width];

				for (int i = 0; i < width; i++)
					internalShape[i] = new bool[height];

				for (int i = 0; i < width; i++) {

					for (int j = 0; j < height; j++) {

						internalShape[i][j] = true;
					}
				}



			}
			else {

				int newX, newY; // the position of the new fractal sprawner being created

				bool hitEdge = false;

				// logic: 
				//
				// start loop go forward first and the first empty spot find place a sprawler else keep on going 
				// if hit edge the go backward 
				//

				for (int i = x + width - 1 ; i < worldWidth && i >= 0; ) {

					for (int j = y + height - 1; j < worldHeight && j >= 0; j++ ) {

						if (world[i][j].occupant == nullptr && (i + 2 < worldWidth && j + 2 < worldHeight ) ) {
							
							FractalSprawler* newConsumer = new FractalSprawler(i, y, 2, 2);
							world[i][j].occupant = newConsumer;
						}

					}

					if (i + 1 < worldWidth && hitEdge != true ) i++;
					else if ( !hitEdge ){
						hitEdge = true;
						i--;
					}
					else if( i >= 0 && hitEdge ){
						i--;
					}


				}

			}

		}
		else if (averageNutrient < 30) {

			for (int i = 0; i < width; i++)
				delete[] internalShape[i];

			delete[] internalShape;

			width--;
			height--;

			if (width <= 0 && height <= 0) {
				alive = false;
				world[x][y].occupant = nullptr;
			}

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

	}
	

	~FractalSprawler() {

	}
	
};

class KineticHunter: public Organism {

public:
	KineticHunter(int x, int y, int width, int height) : Organism(x, y, width, height) {
		this->specie = true;
	}

	
	void update(Tile** world, int worldWidth, int worldHeight) {

		//
		// logic first scan if find a producer then store it's location and call move 
		// 
		// then check if the internal structure is touching any producer if yes then decrease the producers nutrientlevel
		//

		// search  



	}


	KineticHunter() {
		this->specie = true;
	}

};
