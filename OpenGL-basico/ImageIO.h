#include <iostream>
#include "FreeImage.h"

#ifndef IMAGEIO_H
#define IMAGEIO_H

using namespace std;

class ImageIO
{
private:
	int width = 640;
	int height = 400;

public:
	void ImageIO::saveAsPng();

};

#endif // IMAGEIO_H