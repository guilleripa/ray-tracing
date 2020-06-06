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
    float nearDistance = 2; // todo configurable
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

            Vector3 pixel = LeftTopPoint - (upOffset * j) - (leftOffset * i);
            Vector3 rayDirection = (pixel - rayOrigin).normalize();
            //cout << "x " << pixel.getX() << " y " << pixel.getY() << " z " << pixel.getZ() << "\n";
           
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

    Vector3 colorAmbience = object->getColor() * scene.getAmbientLight();
    Vector3 colorDiffuse = Vector3(0, 0, 0);
    Vector3 colorSpeculate = Vector3(0, 0, 0);
    Vector3 colorRefraction = Vector3(0, 0, 0);
    Vector3 colortransmission = Vector3(0, 0, 0);

    for (Light light : scene.getLights()) {
        Vector3 rayLightDirection = (light.getPosition() - intersection).normalize(); 
        float dotNormalLigth = normal.dot(rayLightDirection);
        if (dotNormalLigth > 0 ) {
            // Calcular cuánta luz es bloqueada por sup.opacas y transp., y usarlo para escalar los términos difusos y especulares antes de añadirlos a color; ??

            float distanceToLight = (light.getPosition() - intersection).mod();

            float diffuseFactorR = object->getDiffuseCoefficient();
            float diffuseFactorG = object->getDiffuseCoefficient();
            float diffuseFactorB = object->getDiffuseCoefficient();
            float speculateFactorR = object->getSpeculateCoefficient();
            float speculateFactorG = object->getSpeculateCoefficient();
            float speculateFactorB = object->getSpeculateCoefficient();

            // Chequear si hay objetos en el medio
            float distance = std::numeric_limits<float>::infinity();
            Vector3 pointOfIntersection;
            for (Object* otherObject : scene.getObjects()) {
                if (otherObject != object) { // todo check
                    otherObject->intersects(rayOrigin, rayDirection, &distance, &pointOfIntersection);

                    if (distance + 0.001 < distanceToLight) { // todo 0.001

                        diffuseFactorR *= otherObject->getTransmissionCoefficient() * (otherObject->getColor().getX() / 255); // porque el / 255?
                        diffuseFactorG *= otherObject->getTransmissionCoefficient() * (otherObject->getColor().getY() / 255);
                        diffuseFactorB *= otherObject->getTransmissionCoefficient() * (otherObject->getColor().getZ() / 255);
                        speculateFactorR *= otherObject->getSpeculateCoefficient() * (otherObject->getColor().getX() / 255);
                        speculateFactorG *= otherObject->getSpeculateCoefficient() * (otherObject->getColor().getY() / 255);
                        speculateFactorB *= otherObject->getSpeculateCoefficient() * (otherObject->getColor().getZ() / 255);

                    }
                }
            }

            // Luz difusa
            Vector3 colorDifusoEstaLuz = Vector3(light.getColor().getX() * object->getColor().getX() * diffuseFactorR * dotNormalLigth / (pow(distanceToLight, 2)),
                                                 light.getColor().getY() * object->getColor().getY() * diffuseFactorG * dotNormalLigth / (pow(distanceToLight, 2)),
                                                 light.getColor().getZ() * object->getColor().getZ() * diffuseFactorB * dotNormalLigth / (pow(distanceToLight, 2)));

            // Luz especular
           /* Point luzReflejada = reflejar(direccionLuz * -1, normal);
            float prodInternoReflejado = pow(luzReflejada.dotProduct(rayo->getDireccion() * -1), factorN);
            Color colorEspecularEstaLuz = Color(0, 0, 0);
            if (prodInternoReflejado > 0) {
                colorEspecularEstaLuz = Color(luz->getColor().getR() * prodInternoReflejado * factorEspecularR,
                    luz->getColor().getG() * prodInternoReflejado * factorEspecularG,
                    luz->getColor().getB() * prodInternoReflejado * factorEspecularB);
            }*/

            colorDiffuse = colorDiffuse + colorDifusoEstaLuz;
            //colorSpeculate = colorSpeculate + colorEspecularEstaLuz;
           
        }
    }
    
    if (depth < scene.getMaxDepth()) {
       
        if (object->getSpeculateCoefficient() > 0) {
            Vector3 rayOriginReflection; // rayo_r = rayo en la dirección de reflexión desde punto;
            Vector3 rayDirectionReflection;
            Vector3 colorReflection = trace(scene, rayOriginReflection, rayDirectionReflection, depth + 1);
            //escalar colorReflection por el coeficiente especular y añadir a color;
        }
        if (object->getTransmissionCoefficient() > 0) {
            //if (no ocurre la reflexión interna total) {
                Vector3 rayOriginTransparent; // rayo_t = rayo en la dirección de refracción desde punto; */
                Vector3 rayDirectionTransparent;
                Vector3 colorTransparent = trace(scene, rayOriginTransparent, rayDirectionTransparent, depth + 1);
                //escalar color_t por el coeficiente de transmisión y añadir a color;
            //}
        }
       
    }

    return colorAmbience + colorDiffuse + colorSpeculate + colorRefraction + colortransmission;
}

Object* Whitted::intersection(Scene scene, Vector3 rayOrigin, Vector3 rayDirection, Vector3 nearestPointOfIntersection) {

    float distanceMin = std::numeric_limits<float>::infinity();
    float distance = std::numeric_limits<float>::infinity();
    Object* nearestObject = NULL;
    Vector3 pointOfIntersection;
    for (Object* object : scene.getObjects()) {
        if (object->intersects(rayOrigin, rayDirection, &distance, &pointOfIntersection) && distance < distanceMin) {
            nearestObject = object;
            distanceMin = distance;
            nearestPointOfIntersection = pointOfIntersection;
        }
    }
    return nearestObject;
}
