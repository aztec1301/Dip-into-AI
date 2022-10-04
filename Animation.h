#pragma once

#include <raylib.h>
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>

class Animation
{
private:
	Texture image; //the spritesheet once loaded in as a texture
	Rectangle drawSize;//the size to be drawn at
	std::vector<Rectangle> frames;//a vector that will hold each individual frame of the sprite sheet
	float fps = 25.0f;//fps frames will be shown at

public:
	~Animation()
	{
		UnloadTexture(image);
	}

	Animation(Rectangle size, const std::string& filename) : drawSize{ size }//input size to be drawn at, the filename, allocate drawsize immediately
	{
		std::ifstream file{ filename };//open up ifstream to read file
		if (!file)//if file isn't there
		{
			throw std::runtime_error{ "couldn't load " + filename };//tell off the user
		}

		std::string texture;//container to hold strings from file
		std::getline(file, texture);//get the first line of the file

		image = LoadTexture(texture.c_str());//load the first line(which should be a pathway to the image) as a texture

		file >> fps;//ther next line should be timing of fps

		Vector2 frameSize;//size of the sprite
		file >> frameSize.x;//width of the sprite (next line)
		file >> frameSize.y;//height of the sprite (next line)

		Rectangle current{ 0,0,frameSize.x, frameSize.y };//start point of the rectangle being (x pos, y pos, how many x pixels to move, how many y pixels to move
		while (file >> current.x)//while lines in file to read for x pos
		{
			file >> current.y;//current y pos
			current.x *= frameSize.x;//get sprite at this x pos
			current.y *= frameSize.y;//get sprite at this y pos
			frames.push_back(current);//put collected sprite into the frames vector
		}

	}

	void Draw(Vector2 position, float degrees)
	{
		int i = (int)(GetTime() * fps) % frames.size();
		
		DrawTexturePro(
			image,
			frames[i],
			Rectangle{ position.x, position.y, drawSize.width, drawSize.height }
			, { drawSize.width / 2, drawSize.height / 2 }
			, degrees
			,  Color{ 255,255,255,255 }
		);
	}

	std::vector<Rectangle> GetFrames() {return frames;}//returns frame information
	float GetFPS() { return fps; }//returns fps information

};