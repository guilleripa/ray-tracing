#include "ImageIO.h"
#include <direct.h>
#include <ctime>


void ImageIO::saveAsPng(Scene scene, vector<vector<Vector3>> pixels)
{
    time_t rawtime;
    struct tm timeinfo;
    char buffer[80];

    time(&rawtime);
    localtime_s(&timeinfo , &rawtime);

    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H.%M.%S", &timeinfo);
    std::string path(buffer);

    string pathFolder = "Historial/" + path;
    if (_mkdir(pathFolder.c_str())) {
        throw 1;
    } else
    {
        FIBITMAP* freeImageBitmap = FreeImage_Allocate(scene.getWidth(), scene.getHeight(),
            32, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK);

        const unsigned int BYTESPP =
            FreeImage_GetLine(freeImageBitmap) / FreeImage_GetWidth(freeImageBitmap);
        for (unsigned int y = 0; y < FreeImage_GetHeight(freeImageBitmap); ++y) {
            BYTE* bits = FreeImage_GetScanLine(freeImageBitmap, y);

            for (unsigned int x = 0; x < FreeImage_GetWidth(freeImageBitmap); ++x) {
                bits[FI_RGBA_RED] = pixels[y][x].getX();
                bits[FI_RGBA_GREEN] = pixels[y][x].getY();
                bits[FI_RGBA_BLUE] = pixels[y][x].getZ();
                bits[FI_RGBA_ALPHA] = 255;

                bits += BYTESPP;
            }
        }

        string pathFile = pathFolder + "/Escena.png";
        if (!FreeImage_Save(FIF_PNG, freeImageBitmap, pathFile.c_str(), 0)) {
            string err = "Error al guardar archivo '";
            err += "Escena.png";
            err += '\'';
            throw err;
        }

        FreeImage_Unload(freeImageBitmap);
    }


}