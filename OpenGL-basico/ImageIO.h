#include <iostream>
#include <vector>
#include "FreeImage.h"

#include "Scene.h"

#ifndef IMAGEIO_H
#define IMAGEIO_H

using namespace std;

class ImageIO
{
private:


public:
	void ImageIO::saveAsPng(Scene scene, vector<vector<Vector3>> pixels);

};

#endif // IMAGEIO_H