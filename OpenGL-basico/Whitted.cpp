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
    Object* object = intersection(scene, rayOrigin, rayDirection, &pointOfIntersection);
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
    Vector3 colorReflection = Vector3(0, 0, 0);

    // todo sacar a metodo
    for (Light light : scene.getLights()) {
        Vector3 rayLightDirection = (intersection - light.getPosition()).normalize();
        float dotNormalLight = normal.dot(rayLightDirection);

        if (dotNormalLight > 0 ) {

            float distanceToLight = (light.getPosition() - intersection).mod();

            Vector3 diffuseFactor = Vector3(object->getDiffuseCoefficient(), object->getDiffuseCoefficient(), object->getDiffuseCoefficient());
            Vector3 speculateFactor = Vector3(object->getSpeculateCoefficient(), object->getSpeculateCoefficient(), object->getSpeculateCoefficient());

            // Chequear si hay objetos en el medio
            float distance = std::numeric_limits<float>::infinity();
            Vector3 pointOfIntersection;
            for (Object* otherObject : scene.getObjects()) {
                if (otherObject != object) { // todo check
                    otherObject->intersects(rayOrigin, rayDirection, &distance, &pointOfIntersection);

                    if (distance + 0.001 < distanceToLight) { // todo 0.001
                        diffuseFactor = diffuseFactor * otherObject->getTransmissionCoefficient() * (otherObject->getColor() /255);
                        speculateFactor = speculateFactor * otherObject->getSpeculateCoefficient() * (otherObject->getColor() / 255);
                    }
                }
            }

            // Luz difusa
            Vector3 colorDiffuseLight = Vector3(light.getColor() * object->getColor() * diffuseFactor * dotNormalLight / (pow(distanceToLight, 2)));

            // Luz especular
            Vector3 rayDirectionReflection = reflect(rayDirection, normal);
            float internalReflectedProd = pow(rayLightDirection.dot(rayDirection), 25);
            Vector3 colorSpeculateLight = Vector3(0, 0, 0);
            if (internalReflectedProd > 0) {
                colorSpeculateLight = Vector3(light.getColor() * internalReflectedProd * speculateFactor);
            }

            colorDiffuse = colorDiffuse + colorDiffuseLight;
            colorSpeculate = colorSpeculate + colorSpeculateLight;
           
        }
    }
    
    if (depth < scene.getMaxDepth()) {
       
        if (object->getSpeculateCoefficient() > 0) {
            
            Vector3 rayDirectionReflection = reflect(rayDirection, normal);
            Vector3 colorR = trace(scene, intersection, rayDirectionReflection, depth + 1);
            colorReflection = colorR * object->getSpeculateCoefficient();

        }
        if (object->getTransmissionCoefficient() > 0) {
            //float n2 = ;
            //float n1 = ;

            //if (asin(n2 / n1)) { // (no ocurre la reflexión interna total)

                Vector3 rayDirectionRefraction = refract(rayDirection, normal, object->getIndexRefraction());
                Vector3 colorT = trace(scene, intersection, rayDirectionRefraction, depth + 1);
                colorRefraction = colorT * object->getTransmissionCoefficient();

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
            *nearestPointOfIntersection = pointOfIntersection - rayDirection * 0.001;
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
    Vector3 o = (rayIncident * eta - normal * (-cosi + eta * cosi));
    return o;
}