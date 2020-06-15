#include "Whitted.h"
#include <vector>
#include <limits>
#include <cmath>

#include "Vector3.h"
#include "ImageIO.h"
#include <iostream>

#define PI 3.14159265

float toDegrees(float radians) {
    return radians * PI / 180.0;
}

void Whitted::run(Scene scene) {

    int fov = scene.getCamera()->getFov();
    int nearDistance = scene.getCamera()->getNearDistance();
    Vector3 eye = scene.getCamera()->getEye();
    Vector3 pov = scene.getCamera()->getPov();
    Vector3 up = scene.getCamera()->getUp();
    Vector3 direction = (pov - eye).normalize();

    // http://www.lighthouse3d.com/tutorials/view-frustum-culling/view-frustums-shape/
    float WidthViewPlane = 2 * tan(toDegrees(fov/2)) * nearDistance;
    float HeightViewPlane = WidthViewPlane * ((float)scene.getHeight()/ (float)scene.getWidth());

    // http://www.lighthouse3d.com/tutorials/view-frustum-culling/geometric-approach-extracting-the-planes/
    Vector3 centerPoint = eye + direction * nearDistance;
    Vector3 left = up.cross(direction).normalize()*-1;
    // Vector3 LeftTopPoint = centerPoint + (up * HeightViewPlane / 2.0) + ( left * WidthViewPlane / 2.0);
    Vector3 RightBottomPoint = centerPoint - (up * HeightViewPlane / 2.0) - ( left * WidthViewPlane / 2.0);

    Vector3 rayOrigin = Vector3(eye.getX(), eye.getY(), eye.getZ());
    vector<vector<Vector3>> pixels(scene.getHeight(), vector<Vector3>(scene.getWidth(), Vector3()));
    vector<vector<Vector3>> pixelsReflection(scene.getHeight(), vector<Vector3>(scene.getWidth(), Vector3()));
    vector<vector<Vector3>> pixelsTransmision(scene.getHeight(), vector<Vector3>(scene.getWidth(), Vector3()));

    Vector3 leftOffset = left * (WidthViewPlane / (scene.getWidth() - 1));
    Vector3 upOffset = up * (HeightViewPlane / (scene.getHeight() - 1));
    std::stack<Object*> intersectedObjectsStack;

    for (int j = 0; j < scene.getHeight(); ++j) {
        for (int i = 0; i < scene.getWidth(); ++i) {

            Vector3 pixel = RightBottomPoint + (upOffset * j) + (leftOffset * i);
            Vector3 rayDirection = (pixel - rayOrigin).normalize();
            // cout << " y: " << rayDirection.getY() << "\n";
            vector<Vector3> pixelsVector = trace(scene, rayOrigin, rayDirection, 1, intersectedObjectsStack);
            
            pixels[j][i] = pixelsVector[0];
            pixelsReflection[j][i] = pixelsVector[1];
            pixelsTransmision[j][i] = pixelsVector[2];
        }
    }

    ImageIO().saveAsPng(scene, pixels, pixelsReflection, pixelsTransmision);
}

vector<Vector3> Whitted::trace(Scene scene, Vector3 rayOrigin, Vector3 rayDirection, int depth, std::stack<Object*> intersectedObjectsStack)
{
    vector<Vector3> result(3, Vector3());
    Vector3 pointOfIntersection;
    Object* object = intersection(scene, rayOrigin, rayDirection, &pointOfIntersection);
    if (object != NULL) {
        Vector3 normal = object->getNormalIn(pointOfIntersection);
        result[0] = shadow(scene, object, rayOrigin, rayDirection, pointOfIntersection, normal, depth, intersectedObjectsStack);
        result[1] = Vector3(object->getSpeculateCoefficient() * 255, object->getSpeculateCoefficient() * 255, object->getSpeculateCoefficient() * 255);
        result[2] = Vector3(object->getTransmissionCoefficient() * 255, object->getTransmissionCoefficient() * 255, object->getTransmissionCoefficient() * 255);
    }
    else {
        result[0] = scene.getBackgroundColor();
        result[1] = Vector3(0, 0, 0);
        result[2] = Vector3(0, 0, 0);
    }
    return result;
}

Vector3 Whitted::shadow(Scene scene, Object* object, Vector3 rayOrigin, Vector3 rayDirection, Vector3 intersection, Vector3 normal, int depth, std::stack<Object*> intersectedObjectsStack)
{

    Vector3 colorAmbience = object->getColor() * object->getAmbienceCoefficient();
    Vector3 colorDiffuse = Vector3(0, 0, 0);
    Vector3 colorSpeculate = Vector3(0, 0, 0);

    for (Light light : scene.getLights()) { // para cada luz
        Vector3 rayLightDirection = (intersection - light.getPosition()).normalize();
        float dotNormalLight = normal.dot(rayLightDirection);

        if (dotNormalLight > 0 ) {

            float distanceToLight = (light.getPosition() - intersection).mod();

            
            Vector3 speculateFactor = Vector3(object->getSpeculateCoefficient(), object->getSpeculateCoefficient(), object->getSpeculateCoefficient());
            Vector3 diffuseFactor = Vector3(object->getDiffuseCoefficient(), object->getDiffuseCoefficient(), object->getDiffuseCoefficient());

            float distance = std::numeric_limits<float>::infinity();
            Vector3 pointOfIntersection;
            for (Object* otherObject : scene.getObjects()) {
                if (otherObject != object) {

                    if (otherObject->intersects(light.getPosition(), rayLightDirection, &distance, &pointOfIntersection) && distance < distanceToLight) {
                        speculateFactor = speculateFactor * otherObject->getSpeculateCoefficient() * (otherObject->getColor() / 255);
                        diffuseFactor = diffuseFactor * otherObject->getTransmissionCoefficient() * (otherObject->getColor() / 255);
                    }
                }
            }

            colorDiffuse = colorDiffuse + light.getColor() * object->getColor() * diffuseFactor * dotNormalLight / (pow(distanceToLight, 2));
            colorSpeculate = colorSpeculate + speculateColor(rayLightDirection, rayDirection, normal, light.getColor(), speculateFactor);
            

        }
    }

    Vector3 colorReflection = Vector3(0, 0, 0);
    Vector3 colorRefraction = Vector3(0, 0, 0);
    if (depth < scene.getMaxDepth()) {

        if (object->getSpeculateCoefficient() > 0) { // si objeto es reflejante
            colorReflection = reflectColor(scene, object, rayDirection, intersection, normal, depth, intersectedObjectsStack);
        }

        if (object->getTransmissionCoefficient() > 0) { // si objeto es transparente
            colorRefraction = refractColor(scene, object, rayDirection, intersection, normal, depth, intersectedObjectsStack);
        }

    }

    return colorAmbience + colorDiffuse + colorSpeculate + colorRefraction + colorReflection;
}

Vector3 Whitted::speculateColor(Vector3 rayLightDirection, Vector3 rayDirection, Vector3 normal, Vector3 lightColor, Vector3 speculateFactor) {
    Vector3 rayDirectionReflection = reflect(rayLightDirection, normal);
    float internalReflectedProd = pow(rayDirectionReflection.dot(rayDirection), 30);
    Vector3 colorSpeculateLight = Vector3(0, 0, 0);
    if (internalReflectedProd > 0) { // si producto punto entre normal y dirección de la luz es positivo
        colorSpeculateLight = Vector3(lightColor * internalReflectedProd * speculateFactor);
    }

    return colorSpeculateLight;
}

Vector3 Whitted::reflectColor(Scene scene, Object* object, Vector3 rayDirection, Vector3 intersection, Vector3 normal, int depth, std::stack<Object*> intersectedObjectsStack) {
    Vector3 rayDirectionReflection = reflect(rayDirection, normal);
    vector<Vector3> colorR = trace(scene, intersection, rayDirectionReflection, depth + 1, intersectedObjectsStack);
    return colorR[0] * object->getSpeculateCoefficient();
}

Vector3 Whitted::refractColor(Scene scene, Object* object, Vector3 rayDirection, Vector3 intersection, Vector3 normal, int depth, std::stack<Object*> intersectedObjectsStack) {
    // Para saber el angulo de insidencia tenemos que saber desde que objeto viene el rayo
    // y cual es el indice de refraccion de ese objeto, para eso usamos una pila de objetos que saben su indice
    // a medida que intersectamos objetos los vamos agregando

    float n1;
    float n2;

    if (intersectedObjectsStack.empty()) {
        n1 = 1;
    }
    else {
        n1 = intersectedObjectsStack.top()->getIndexRefraction();
    }

    n2 = object->getIndexRefraction();

    intersectedObjectsStack.push(object);

    float incidenceAngle = rayDirection.angle(normal);

    if (incidenceAngle <= (asin(n2 / n1) * 180.0 / PI)) { // si no ocurre la reflexión interna total
        Vector3 rayDirectionRefraction = refract(rayDirection, normal, object->getIndexRefraction());
        vector<Vector3> colorT = trace(scene, intersection, rayDirectionRefraction, depth + 1, intersectedObjectsStack);
        return colorT[0] * object->getTransmissionCoefficient();
    }

    return Vector3(0, 0, 0);
}

Object* Whitted::intersection(Scene scene, Vector3 rayOrigin, Vector3 rayDirection, Vector3* nearestPointOfIntersection) {

    float distanceMin = std::numeric_limits<float>::infinity();
    float distance = std::numeric_limits<float>::infinity();
    Object* nearestObject = NULL;
    Vector3 pointOfIntersection;
    for (Object* object : scene.getObjects()) {
        if (object->intersects(rayOrigin, rayDirection, &distance, &pointOfIntersection) && distance < distanceMin) {
            nearestObject = object;
            distanceMin = distance;
            *nearestPointOfIntersection = pointOfIntersection - rayDirection * 0.000001;
        }
    }
    return nearestObject;
}

// http://paulbourke.net/geometry/reflected/
Vector3 Whitted::reflect(Vector3 rayIncident, Vector3 normal) {
    return (rayIncident - normal * rayIncident.dot(normal) * 2).normalize();
}

// https://stackoverflow.com/questions/42218704/how-to-properly-handle-refraction-in-raytracing
Vector3 Whitted::refract(Vector3 rayIncident, Vector3 normal, float eta)
{
    eta = 2.0f - eta;
    float cosi = normal.dot(rayIncident);
    return (rayIncident * eta - normal * (-cosi + eta * cosi)).normalize();
}
