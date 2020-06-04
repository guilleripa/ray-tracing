#include "Whitted.h"
#include <vector>
#include <limits>
#include <cmath>

#include "Vector3.h"
#include "ImageIO.h"

#define PI 3.14159265

float toDegrees(float radians) {
    return radians * PI / 180.0;
}

void Whitted::run(Scene scene) {

    float fov = 30; // todo configurable
    float nearDistance = 5; // todo configurable
    Vector3 eye = scene.getCamera().getEye();
    Vector3 pov = scene.getCamera().getCenter();
    Vector3 up = scene.getCamera().getUp().normalize();
    Vector3 direction = (pov - eye).normalize();

    // http://www.lighthouse3d.com/tutorials/view-frustum-culling/view-frustums-shape/
    float WidthViewPlane = 2 * tan(toDegrees(fov / 2)) * nearDistance;
    float HeightViewPlane = WidthViewPlane * ((float)scene.getHeight()/ (float)scene.getWidth());

    // http://www.lighthouse3d.com/tutorials/view-frustum-culling/geometric-approach-extracting-the-planes/
    Vector3 centerPoint = eye + direction * nearDistance;
    Vector3 left = up.cross(direction).normalize();
    Vector3 LeftTopPoint = centerPoint + (up * HeightViewPlane / 2.0) + ( left * WidthViewPlane / 2.0);

    Vector3 rayOrigin = Vector3(eye.getX(), eye.getY(), eye.getZ());
    vector<vector<Vector3>> pixels(scene.getHeight(), vector<Vector3>(scene.getWidth(), Vector3()));

    Vector3 leftOffset = left * (WidthViewPlane / (scene.getWidth() - 1));
    Vector3 upOffset = up * (HeightViewPlane / (scene.getHeight() - 1));

    for (int j = 0; j < scene.getHeight(); ++j) {
        for (int i = 0; i < scene.getWidth(); ++i) {

            Vector3 pixel = LeftTopPoint + (upOffset * j) - (leftOffset * i);
            Vector3 rayDirection = (pixel - rayOrigin).normalize();
            // cout << "x " << pixel.getX() << " y " << pixel.getY() << " z " << pixel.getZ() << "\n";
           
            pixels[j][i] = trace(scene, rayOrigin, rayDirection, 1);
        }
    }

    ImageIO().saveAsPng(scene, pixels);

}

Vector3 Whitted::trace(Scene scene, Vector3 rayOrigin, Vector3 rayDirection, int depth)
{

    Vector3 pointOfIntersection;
    Object* object = intersection(scene, rayOrigin, rayDirection, pointOfIntersection);
    if (object != NULL) {
        Vector3 normal = object->getNormalIn(pointOfIntersection);
        return shadow(scene, object, rayOrigin, rayDirection, pointOfIntersection, normal, depth);
    }
    else
        return scene.getBackgroundColor();
}

Vector3 Whitted::shadow(Scene scene, Object* object, Vector3 rayOrigin, Vector3 rayDirection, Vector3 intersection, Vector3 normal, int depth)
{
    Vector3 color = object->getColor() * scene.getAmbientLight();
    for (Light light : scene.getLights()) {
        Vector3 shadowRayOrigin ;
        Vector3 shadowRayDirection;
        //rayo_s = rayo desde el punto(intersection) a la luz;
        Vector3 rayLigthDirection = (light.getPosition() - intersection).normalize(); // todo 
        if (normal.dot(rayLigthDirection) > 0 ) {
            //Calcular cuánta luz es bloqueada por sup.opacas y transp., y usarlo para escalar los términos difusos y especulares antes de añadirlos a color; ?? 
        }
    }
    
    if (depth < scene.getMaxDepth()) {
       
        if (object->getReflectionCoefficient() > 0) {

            Vector3 rayOriginReflection; // rayo_r = rayo en la dirección de reflexión desde punto;
            Vector3 rayDirectionReflection;
            Vector3 colorReflection = trace(scene, rayOriginReflection, rayDirectionReflection, depth + 1);
            //escalar colorReflection por el coeficiente especular y añadir a color;
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

Object* Whitted::intersection(Scene scene, Vector3 rayOrigin, Vector3 rayDirection, Vector3 nearestPointOfIntersection) {
    // todo estas cosas son punteros para poder modificar sino son copias por parametro
    float distanceMin = std::numeric_limits<float>::infinity();
    float distance = std::numeric_limits<float>::infinity();
    Object* nearestObject = NULL;
    Vector3 pointOfIntersection;
    for (Object* object : scene.getObjects()) {
        if (object->intersects(rayOrigin, rayDirection, distance, pointOfIntersection) && distance < distanceMin) {
            nearestObject = object;
            distanceMin = distance;
            nearestPointOfIntersection = pointOfIntersection;
        }
    }
    return nearestObject;
}
