#pragma once
#include "Color.h"
#include <vector>

#define MAX_PIXEL_VALUE 255

namespace EPIC{
	class Image{

	public:
		Image(int width, int height);
		Image(const Image& img);
		Color* getPixel(int row, int col);
		//std::vector<Color>::iterator getPixel(int row, int col);
		bool save(const char* filepath);

	private:
		int m_height;
		int m_width;
		std::vector<Color> m_pixels;
	};

}

