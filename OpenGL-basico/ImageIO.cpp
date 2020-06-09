#include "ImageIO.h"
#include <direct.h>
#include <ctime>


void ImageIO::saveAsPng(Scene scene, vector<vector<Vector3>> pixels, vector<vector<Vector3>> pixelsReflection, vector<vector<Vector3>> pixelsTransmision)
{
    time_t rawtime;
    struct tm timeinfo;
    char buffer[80];

    time(&rawtime);
    localtime_s(&timeinfo , &rawtime);

    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H.%M.%S", &timeinfo);
    std::string path(buffer);

    string folder = "Historial";
    _mkdir(folder.c_str());
    if (errno == ENOENT) {
        throw 1;
    }
    else
    {
        string pathFolder = "Historial/" + path;
        _mkdir(pathFolder.c_str());
        if (errno == ENOENT) {
            throw 1;
        }
        else
        {
            saveAsPng(scene, pixels, pathFolder + "/Escena.png");
            saveAsPng(scene, pixelsReflection, pathFolder + "/Reflection.png");
            saveAsPng(scene, pixelsTransmision, pathFolder + "/Transmision.png");

        }
    }
    


}


void ImageIO::saveAsPng(Scene scene, vector<vector<Vector3>> pixels, string pathFile) {

    FIBITMAP* freeImageBitmap = FreeImage_Allocate(scene.getWidth(), scene.getHeight(),
        32, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK);

    const unsigned int BYTESPP =
        FreeImage_GetLine(freeImageBitmap) / FreeImage_GetWidth(freeImageBitmap);
    for (unsigned int y = 0; y < FreeImage_GetHeight(freeImageBitmap); ++y) {
        BYTE* bits = FreeImage_GetScanLine(freeImageBitmap, y);

        for (unsigned int x = 0; x < FreeImage_GetWidth(freeImageBitmap); ++x) {

            if (pixels[y][x].getX() > 255) {
                bits[FI_RGBA_RED] = 255;
            }
            else {
                bits[FI_RGBA_RED] = pixels[y][x].getX();
            }

            if (pixels[y][x].getY() > 255) {
                bits[FI_RGBA_GREEN] = 255;
            }
            else {
                bits[FI_RGBA_GREEN] = pixels[y][x].getY();
            }


            if (pixels[y][x].getZ() > 255) {
                bits[FI_RGBA_BLUE] = 255;
            }
            else {
                bits[FI_RGBA_BLUE] = pixels[y][x].getZ();
            }

            bits[FI_RGBA_ALPHA] = 255;

            bits += BYTESPP;
        }
    }

    if (!FreeImage_Save(FIF_PNG, freeImageBitmap, pathFile.c_str(), 0)) {
        string err = "Error al guardar archivo '";
        throw err;
    }

    FreeImage_Unload(freeImageBitmap);
}