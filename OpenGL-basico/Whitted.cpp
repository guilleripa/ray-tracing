#include "Whitted.h"
#include <vector>

#include "Vector3.h"
#include "ImageIO.h"

void Whitted::run(Scene scene) {

	//Seleccionar el centro de proyección y la ventana en el plano de vista;
    vector<vector<Vector3>> pixels(scene.getHeight(), vector<Vector3>(scene.getWidth(), Vector3()));
    Vector3 origin = Vector3(0,0,0);// todo scene camera 
    for (int j = 0; j < scene.getHeight(); ++j) {
        for (int i = 0; i < scene.getWidth(); ++i) {
            // determinar rayo por centro de proyección y píxel;
            Vector3 direction = Vector3(0, 0, 0); // todo
            pixels[j][i] = trace(scene, origin, direction, 1);
        }
    }

    ImageIO().saveAsPng(scene, pixels);

}

Vector3 Whitted::trace(Scene scene, Vector3 origin, Vector3 direction, int depth)
{
    //determinar la intersección más cercana de rayo con un objeto;
    bool intersectedObject = false; // Hay objeto intersecado
    if (intersectedObject) {
        //calcular la normal en la intersección;
        //return shadow(obj.intersecado más cercano, rayo, intersección, normal, depth);
        return shadow(scene, depth);
    }
    else
        return scene.getBackgroundColor();
}

Vector3 Whitted::shadow(Scene scene, int depth)
//Vector3 shadow(objeto, rayo, punto, normal, int profundidad)
{
    Vector3 color = Vector3(0, 0, 0); // todo
    /*Vector3 color = término del ambiente;
    for (cada luz) {
        rayo_s = rayo desde el punto a la luz;
        if (producto punto entre normal y dirección de la luz es positivo) {
            Calcular cuánta luz es bloqueada por sup.opacas y transp., y usarlo para escalar los términos difusos y especulares antes de añadirlos a color;
        }
    }

    if (profundidad < profundidad_max) {
        if (objeto es reflejante) {
            rayo_r = rayo en la dirección de reflexión desde punto;
            color_r = traza_RR(rayo_r, profundidad + 1);
            escalar color_r por el coeficiente especular y añadir a color;
        }
        if (objeto es transparente) {
            if (no ocurre la reflexión interna total) {
                rayo_t = rayo en la dirección de refracción desde punto;
                color_t = traza_RR(rayo_t, profundidad + 1);
                escalar color_t por el coeficiente de transmisión y añadir a color;
            }
        }
    }*/
    return color; /* Devolver color del rayo. */
}