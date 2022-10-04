#include "MapObject.h"




MapObject::MapObject(const char* filename)
{
	InstantiateMap(filename);
}

void MapObject::InstantiateMap(const char* filename)
{
	info.clear();

	std::ifstream filein(filename);//open an fstream of the filename
	if (!filein.is_open())//if the file isn't there, throw up an error
	{
		throw std::runtime_error("file not found");
	}

	std::string line;//the line we need depending on the situation
	std::getline(filein, line);//get first line in the file and save to 'line'

	tile_atlas = LoadTexture(line.c_str());//loads the first line of filename (the texture), into file_atlas

	std::getline(filein, line);//gets the next line of filename
	std::istringstream is{ line };//create a stringstream called 'is' that holds the line

	is >> tilesize;//put the first string of line into tilesize x (x not shown)
	is >> tilesize;//put the second string of line into tilesize y (y not shown)

	std::getline(filein, line); // get the third line
	is.clear();//clear the string stream
	is.str(line);//load the string stream with the next line

	int numberOfTiles; //number of tiles we'll be using
	is >> numberOfTiles;//laod the number of tiles we'll be using from the string streazm into the numberOfTiles int

	rectangleMap = new Rectangle[numberOfTiles];//an array of rectangles

	for (int i = 0; i < numberOfTiles; ++i)//read each of the next set of lines in, etablishing the textures we want, and loading them into the rectangle map
	{
		auto& r = rectangleMap[i];
		r.width = tilesize;
		r.height = tilesize;
		filein >> r.x;
		r.x *= tilesize;
		filein >> r.y;
		r.y *= tilesize;
	}

	filein >> x_width;//total width of the map
	filein >> y_height;//total height of the map
	info.reserve(x_width * y_height);//reserve space for the map

	while (std::getline(filein, line))//read the map in
	{
		std::istringstream is{ line };
		std::string tv; // tv is the number read in
		while (is >> tv)
		{
			info.push_back(atoi(tv.c_str()));
		}
	}
}

MapObject::~MapObject()
{
	delete[] rectangleMap;
	UnloadTexture(tile_atlas);
}

unsigned int MapObject::GetIDAtPosition(float x, float y) const
{
	const int tilex = x / tilesize;
	const int tiley = y / tilesize;
	return tilex + tiley * x_width;
}


void MapObject::Draw()
{
	for (int i = 0; i < x_width; ++i)
	{
		for (int j = 0; j < y_height; ++j)
		{
			int id = i + j * x_width;//the ID of the exact tile we're after
			int mapInfo = info[id];
			Rectangle src = rectangleMap[mapInfo];
			Rectangle dest{ i * tilesize, j * tilesize, tilesize, tilesize };
			DrawTexturePro(tile_atlas, src, dest, Vector2{ 0,0 }, 0, Color{ 255,255,255,255 });

		}
	}
}
