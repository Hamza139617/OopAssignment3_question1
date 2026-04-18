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

	Organism() : x(0), y(0), width(2), height(2) {

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


	// setters

	void setWidth(int x) {
		this->width = x; 
		return;
	}

	void setHeight(int y) {
		this->height = y;
		return;
	}


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

		int radiusX = 2 * width;
		int radiusY = 2 * height;



		int centerX = (x + width) / 2;
		int centerY = (y + height) / 2;

		int startX = centerX - radiusX;
		int endX = centerX + radiusX;

		int startY = centerY - radiusY;
		int endY = centerY + radiusY;

		if (startX < 0) startX = 0;
		if (startY < 0) startY = 0;

		if (endX > worldWidth) endX = worldWidth;
		if (endY > worldHeight) endY = worldHeight;


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
							
							FractalSprawler* newConsumer = new FractalSprawler(i, j, 2, 2);
							for (int a = i; a < i + 2; ++a)
								for (int b = j; b < j + 2; ++b)
									world[a][b].occupant = newConsumer;
						}

					}

					if (i + 1 < worldWidth && hitEdge != true ) i++;
					else if ( !hitEdge ){
						hitEdge = true;
						hitEdge = true;
						i--;
					}
					else if( i >= 0 && hitEdge ){
						i--;
					}


				}


				for (int i = 0; i < width; i++)
					delete[] internalShape[i];

				delete[] internalShape;

				width = 2;
				height = 2;

				internalShape = new bool* [width];

				for (int i = 0; i < width; i++)
					internalShape[i] = new bool[height];


				for (int i = 0; i < width; i++) {


					for (int j = 0; j < height; j++) {
						internalShape[i][j] = true;
					}
				}

			}

		}
		else if (averageNutrient < 30) {

			int oldW = width;
			int oldH = height;

			


			for (int i = 0; i < width; i++)
				delete[] internalShape[i];

			delete[] internalShape;

			width--;
			height--;

			if (width <= 0 || height <= 0) {
				alive = false;

				for (int i = x; i < x + oldW; i++) {
					for (int j = y; j < y + oldH; j++) {
						if (i >= 0 && j >= 0 && i < worldWidth && j < worldHeight && world[i][j].occupant == this) {
							world[i][j].occupant = nullptr;
						}
					}
				}

				return;
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


	void move(int targetX, int targetY, Tile** world, int worldWidth, int worldHeight ) {

		int oldX = x, oldY = y;

		int nextX = x;
		int nextY = y;

		if (targetX < x) nextX--;
		else if (targetX > x) nextX++;

		if (targetY > y) nextY++;
		else if (targetY < y) nextY--;

		if (nextX < 0 || nextY < 0 || nextX + width > worldWidth || nextY + height > worldHeight) {
			return;
		}

		for (int i = oldX; i < oldX + width; i++) {
			
			for (int j = oldY; j < oldY + height; j++) {
				if (world[i][j].occupant == this) world[i][j].occupant = nullptr;
			}

		}

		x = nextX;
		y = nextY;

		for (int i = x; i < x + width; i++) {
			for (int j = y; j < y + height; j++) {
				world[i][j].occupant = this;
			}
		}
		
	}

	void eat(Tile** world) {

		for (int i = x; i < x + width; i++) {

			for (int j = y; j < y + height; j++) {


				if (world[i][j].occupant != nullptr && world[i][j].occupant->getSpecie() == false ) {
					world[i][j].nutrientLevel--;
					world[i][j].toxicity += 0.5f;
					int newX = world[i][j].occupant->getWidth();
					int newY = world[i][j].occupant->getHeight();
					newX--;
					newY--;

					world[i][j].occupant->setWidth(newX);
					world[i][j].occupant->setHeight(newY);
				}

			}

		}

	}
	
	void update(Tile** world, int worldWidth, int worldHeight) {

		//
		// logic first scan if find a producer then store it's location and call move 
		// 
		// then check if the internal structure is touching any producer if yes then decrease the producers nutrientlevel
		//

		// search  
		bool found = false;
		int radiusX = 4 * width;
		int radiusY = 4 * height;

		int startX = x - radiusX;
		int startY = y - radiusY;

		int endX = x + radiusX;
		int endY = y + radiusY;

		if (startX < 0) startX = 0;
		if (startY < 0) startY = 0;



		if (endX > worldWidth) endX = worldWidth;
		if (endY > worldHeight) endY = worldHeight;

		for (int i = startX; i < endX; i++) {

			for (int j = startY; j < endY; j++) {
				
				if ( world[i][j].occupant != nullptr &&  world[i][j].occupant->getSpecie() == false) {
					move(i, j, world, worldWidth, worldHeight );
					found = true;
					break;
				}

			}

			if (found) break;
		}

		eat(world);

	}


	KineticHunter() {
		this->specie = true;
	}

};
