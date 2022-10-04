#pragma once

#include <string>
#include <vector>
#include <raylib.h>
#include <fstream>
#include <sstream>

struct MapObject
{
	int x_width;//width of tile
	int y_height;//height of tile
	std::vector<char> info; // both values stored in a vector

	Texture tile_atlas; //Texture containing all of the tiles needed
	Rectangle* rectangleMap;//array of rectangles that stores the location of each time from the png in pizel co-ords
	int tilesize;//size of each tile

	MapObject(const char* filename);//constructor
	~MapObject();//destructor
	void InstantiateMap(const char* filename);//creates the map from a txt file
	unsigned int GetIDAtPosition(float x, float y) const;
	void Draw();
};