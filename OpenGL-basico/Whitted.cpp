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

    int fov = 30;// scene.getCamera().getFov();
    int nearDistance = scene.getCamera()->getNearDistance();
    Vector3 eye = scene.getCamera()->getEye();
    Vector3 pov = scene.getCamera()->getPov();
    Vector3 up = scene.getCamera()->getUp();
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
    vector<vector<Vector3>> pixelsReflection(scene.getHeight(), vector<Vector3>(scene.getWidth(), Vector3()));
    vector<vector<Vector3>> pixelsTransmision(scene.getHeight(), vector<Vector3>(scene.getWidth(), Vector3()));

    Vector3 leftOffset = left * (WidthViewPlane / (scene.getWidth() - 1));
    Vector3 upOffset = up * (HeightViewPlane / (scene.getHeight() - 1));

    for (int j = 0; j < scene.getHeight(); ++j) {
        for (int i = 0; i < scene.getWidth(); ++i) {

            Vector3 pixel = LeftTopPoint - (upOffset * j) - (leftOffset * i);
            Vector3 rayDirection = (pixel - rayOrigin).normalize();

            vector<Vector3> pixelsVector = trace(scene, rayOrigin, rayDirection, 1);
            pixels[j][i] = pixelsVector[0];
            pixelsReflection[j][i] = pixelsVector[1];
            pixelsTransmision[j][i] = pixelsVector[2];
        }
    }

    ImageIO().saveAsPng(scene, pixels, pixelsReflection, pixelsTransmision);
}

vector<Vector3> Whitted::trace(Scene scene, Vector3 rayOrigin, Vector3 rayDirection, int depth )
{
    vector<Vector3> result(3, Vector3());
    Vector3 pointOfIntersection;
    Object* object = intersection(scene, rayOrigin, rayDirection, &pointOfIntersection);
    if (object != NULL) {
        Vector3 normal = object->getNormalIn(pointOfIntersection);
        result[0] = shadow(scene, object, rayOrigin, rayDirection, pointOfIntersection, normal, depth);
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

Vector3 Whitted::shadow(Scene scene, Object* object, Vector3 rayOrigin, Vector3 rayDirection, Vector3 intersection, Vector3 normal, int depth)
{

    Vector3 colorAmbience = object->getColor() * object->getAmbienceCoefficient();
    Vector3 colorDiffuse = Vector3(0, 0, 0);
    Vector3 colorSpeculate = Vector3(0, 0, 0);
    Vector3 colorRefraction = Vector3(0, 0, 0);
    Vector3 colorReflection = Vector3(0, 0, 0);

    // todo separar a metodo
    for (Light light : scene.getLights()) {
        Vector3 rayLightDirection = (intersection - light.getPosition()).normalize();
        float dotNormalLight = normal.dot(rayLightDirection);

        if (dotNormalLight > 0 ) {

            float distanceToLight = (light.getPosition() - intersection).mod();

            Vector3 diffuseFactor = Vector3(object->getDiffuseCoefficient(), object->getDiffuseCoefficient(), object->getDiffuseCoefficient());
            Vector3 speculateFactor = Vector3(object->getSpeculateCoefficient(), object->getSpeculateCoefficient(), object->getSpeculateCoefficient());

            // Para cada objeto en el medio
            float distance = std::numeric_limits<float>::infinity();
            Vector3 pointOfIntersection;
            for (Object* otherObject : scene.getObjects()) {
                if (otherObject != object) {
                    
                    if (otherObject->intersects(light.getPosition(), rayLightDirection, &distance, &pointOfIntersection) && distance + 0.001 < distanceToLight) {
                        diffuseFactor = diffuseFactor * otherObject->getTransmissionCoefficient() * (otherObject->getColor() /255);
                        speculateFactor = speculateFactor * otherObject->getSpeculateCoefficient() * (otherObject->getColor() / 255);
                    }
                }
            }

            Vector3 rayDirectionReflection = reflect(rayLightDirection, normal);
            float internalReflectedProd = pow(rayDirectionReflection.dot(rayDirection), 30); // todo investigar este numero
            Vector3 colorSpeculateLight = Vector3(0, 0, 0);
            if (internalReflectedProd > 0) {
                colorSpeculateLight = Vector3(light.getColor() * internalReflectedProd * speculateFactor);
            }
            colorSpeculate = colorSpeculate + colorSpeculateLight;

            Vector3 colorDiffuseLight = Vector3(light.getColor() * object->getColor() * diffuseFactor * dotNormalLight / (pow(distanceToLight, 2)));
            colorDiffuse = colorDiffuse + colorDiffuseLight;
           
        }
    }
    
    if (depth < scene.getMaxDepth()) {
       
        if (object->getSpeculateCoefficient() > 0) { // objeto es reflejante
            
            Vector3 rayDirectionReflection = reflect(rayDirection, normal);
            vector<Vector3> colorR = trace(scene, intersection, rayDirectionReflection, depth + 1);
            colorReflection = colorR[0] * object->getSpeculateCoefficient();
            
        }
        if (object->getTransmissionCoefficient() > 0) { // objeto es transparente
            //float n2 = ;
            //float n1 = ;

            //if (asin(n2 / n1)) { // (no ocurre la reflexión interna total)

                Vector3 rayDirectionRefraction = refract(rayDirection, normal, object->getIndexRefraction());
                vector<Vector3> colorT = trace(scene, intersection, rayDirectionRefraction, depth + 1);
                colorRefraction = colorT[0] * object->getTransmissionCoefficient();

            //}
        }
       
    }

    return colorAmbience + colorDiffuse + colorSpeculate + colorRefraction + colorReflection;
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