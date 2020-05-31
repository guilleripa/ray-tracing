#include "Whitted.h"
#include <vector>

#include "Vector3.h"
#include "ImageIO.h"

void Whitted::run(Scene scene) {

	//Seleccionar el centro de proyecci�n y la ventana en el plano de vista;
    vector<vector<Vector3>> pixels(scene.getHeight(), vector<Vector3>(scene.getWidth(), Vector3()));
    Vector3 origin = Vector3(0,0,0);// todo scene camera 
    for (int j = 0; j < scene.getHeight(); ++j) {
        for (int i = 0; i < scene.getWidth(); ++i) {
            // determinar rayo por centro de proyecci�n y p�xel;
            Vector3 direction = Vector3(0, 0, 0); // todo
            pixels[j][i] = trace(scene, origin, direction, 1);
        }
    }

    ImageIO().saveAsPng(scene, pixels);

}

Vector3 Whitted::trace(Scene scene, Vector3 origin, Vector3 direction, int depth)
{
    //determinar la intersecci�n m�s cercana de rayo con un objeto;
    bool intersectedObject = false; // Hay objeto intersecado
    if (intersectedObject) {
        //calcular la normal en la intersecci�n;
        //return shadow(obj.intersecado m�s cercano, rayo, intersecci�n, normal, depth);
        return shadow(scene, depth);
    }
    else
        return scene.getBackgroundColor();
}

Vector3 Whitted::shadow(Scene scene, int depth)
//Vector3 shadow(objeto, rayo, punto, normal, int profundidad)
{
    Vector3 color = Vector3(0, 0, 0); // todo
    /*Vector3 color = t�rmino del ambiente;
    for (cada luz) {
        rayo_s = rayo desde el punto a la luz;
        if (producto punto entre normal y direcci�n de la luz es positivo) {
            Calcular cu�nta luz es bloqueada por sup.opacas y transp., y usarlo para escalar los t�rminos difusos y especulares antes de a�adirlos a color;
        }
    }

    if (profundidad < profundidad_max) {
        if (objeto es reflejante) {
            rayo_r = rayo en la direcci�n de reflexi�n desde punto;
            color_r = traza_RR(rayo_r, profundidad + 1);
            escalar color_r por el coeficiente especular y a�adir a color;
        }
        if (objeto es transparente) {
            if (no ocurre la reflexi�n interna total) {
                rayo_t = rayo en la direcci�n de refracci�n desde punto;
                color_t = traza_RR(rayo_t, profundidad + 1);
                escalar color_t por el coeficiente de transmisi�n y a�adir a color;
            }
        }
    }*/
    return color; /* Devolver color del rayo. */
}