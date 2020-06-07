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
	void saveAsPng(Scene scene, vector<vector<Vector3>> pixels, vector<vector<Vector3>> pixelsReflection, vector<vector<Vector3>> pixelsTransmision);
	void saveAsPng(Scene scene, vector<vector<Vector3>> pixels, string path);

};

#endif // IMAGEIO_H