#include "Whitted.h"
#include <vector>
#include <limits>

#include "Vector3.h"
#include "ImageIO.h"

void Whitted::run(Scene scene) {

	//Seleccionar el centro de proyección y la ventana en el plano de vista;
    vector<vector<Vector3>> pixels(scene.getHeight(), vector<Vector3>(scene.getWidth(), Vector3()));
    Vector3 rayOrigin = Vector3(scene.getCamera().getEye().getX(), scene.getCamera().getEye().getY(), scene.getCamera().getEye().getZ());
    for (int j = 0; j < scene.getHeight(); ++j) {
        for (int i = 0; i < scene.getWidth(); ++i) {
            // determinar rayo por centro de proyección y píxel;
            Vector3 rayDirection = Vector3(0, 0, 0); // todo
            pixels[j][i] = trace(scene, rayOrigin, rayDirection, 1);
        }
    }

    ImageIO().saveAsPng(scene, pixels);

}

Vector3 Whitted::trace(Scene scene, Vector3 rayOrigin, Vector3 rayDirection, int depth)
{
    //determinar la intersección más cercana de rayo con un objeto;
    Object* object = intersection(scene, rayOrigin, rayDirection);
    if (object != NULL) {
        Vector3 rayOrigin; // todo
        Vector3 rayDirection; // todo
        Vector3 intersection;
        Vector3 normal;
        //calcular la normal en la intersección;
        //return shadow(obj.intersecado más cercano, rayo, intersección, normal, depth);
        return shadow(scene, object, rayOrigin, rayDirection, intersection, normal, depth);
    }
    else
        return scene.getBackgroundColor();
}

Vector3 Whitted::shadow(Scene scene, Object* object, Vector3 rayOrigin, Vector3 rayDirection, Vector3 intersection, Vector3 normal, int depth)
//Vector3 shadow(objeto, rayo, punto, normal, int profundidad)
{
    Vector3 color = Vector3(0, 0, 0); // todo término del ambiente??  
    for (Light light : scene.getLights()) {
        //rayo_s = rayo desde el punto a la luz;
        Vector3 rayLigthOrigin = Vector3(light.getPosition().getX(), light.getPosition().getY(), light.getPosition().getZ());
        Vector3 rayLigthDirection = Vector3(0,0,0); // todo 
        if (normal.dot(rayLigthDirection) > 0 ){ //if (producto punto entre normal y dirección de la luz es positivo) {
            //Calcular cuánta luz es bloqueada por sup.opacas y transp., y usarlo para escalar los términos difusos y especulares antes de añadirlos a color;
        }
    }
    
    if (depth < scene.getMaxDepth()) {
       
        if (object->getReflectionCoefficient() > 0) {

            Vector3 rayOriginReflection; // rayo_r = rayo en la dirección de reflexión desde punto;
            Vector3 rayDirectionReflection;
            Vector3 colorReflection = trace(scene, rayOriginReflection, rayDirectionReflection, depth + 1);
            //escalar color_r por el coeficiente especular y añadir a color;
        }
        if (object->getRefractiveCoefficient() > 0) {
            //if (no ocurre la reflexión interna total) {
                Vector3 rayOriginTransparent; // rayo_t = rayo en la dirección de refracción desde punto; */
                Vector3 rayDirectionTransparent;
                Vector3 colorTransparent = trace(scene, rayOriginTransparent, rayDirectionTransparent, depth + 1);
                //escalar color_t por el coeficiente de transmisión y añadir a color;
            //}
        }
       
    }
    return color;
}

Object* Whitted::intersection(Scene scene, Vector3 rayOrigin, Vector3 rayDirection) {

    float distanceMin = std::numeric_limits<float>::infinity();
    float distance = std::numeric_limits<float>::infinity();
    Object* nearestObject = NULL;
    for (Object* object : scene.getObjects()) {
        if (object->intersects(rayOrigin, rayDirection, distance) && distance < distanceMin) {
            nearestObject = object;
            distanceMin = distance;
        }
    }
    return nearestObject;
}
