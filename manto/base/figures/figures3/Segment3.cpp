//
// Created by Braulio Lobo on 10-10-19.
//

#include <sstream>
#include <Tester.h>
#include <iostream>
#include <map>
#include <set>
#include "Segment3.h"

Segment3::Segment3(Vector3 p1, Vector3 p2){
    this->p1 = p1;
    this->p2 = p2;
    generateProjections();
}

Segment3::Segment3(float p1x, float p1y, float p1z, float p2x, float p2y,
                   float p2z) {
    this->p1 = Vector3(p1x, p1y, p1z);
    this->p2 = Vector3(p2x, p2y, p2z);
    generateProjections();
}

float Segment3::getMenorX() {
    if(p1.getX() < p2.getX())
        return p1.getX();
    return p2.getX();
}

float Segment3::getMenorY() {
    if(p1.getY() < p2.getY())
        return p1.getY();
    return p2.getY();
}

float Segment3::getMenorZ() {
    if(p1.getZ() < p2.getZ())
        return p1.getZ();
    return p2.getZ();
}

float Segment3::getMaxX() {
    if(p1.getX() > p2.getX())
        return p1.getX();
    return p2.getX();
}

float Segment3::getMaxY() {
    if(p1.getY() > p2.getY())
        return p1.getY();
    return p2.getY();
}

float Segment3::getMaxZ() {
    if(p1.getZ() > p2.getZ())
        return p1.getZ();
    return p2.getZ();
}

bool Segment3::equal(Segment3 *segment) {
    return this->getMenorX() == segment->getMenorX() &&
           this->getMenorY() == segment->getMenorY() &&
           this->getMenorZ() == segment->getMenorZ() &&
           this->getMaxX()   == segment->getMaxX() &&
           this->getMaxY()   == segment->getMaxY() &&
           this->getMaxZ()   == segment->getMaxZ();
}

Segment2 *Segment3::getProjection(int PROJECTION_PLANE) {
    return &projections[PROJECTION_PLANE];
}

std::string Segment3::toString() {
    std::ostringstream ss;
    ss << "S(" << p1.getX() << ", " << p1.getY() << ", " << p1.getZ() << ")";
    ss << "->(" << p2.getX() << ", " << p2.getY() << ", " << p2.getZ() << ")";
    std::string s(ss.str());
    return s;
}

std::string Segment3::toGraphString() {
    std::ostringstream ss;
    ss << (int)p1.getX() << "," <<  Tester::p_fraccionaria(p1.getX()) << ";" <<
       (int)p1.getY() << "," <<  Tester::p_fraccionaria(p1.getY()) << ";" <<
       (int)p1.getZ() << "," <<  Tester::p_fraccionaria(p1.getZ()) << ";" <<
       (int)p2.getX() << "," <<  Tester::p_fraccionaria(p2.getX()) << ";" <<
       (int)p2.getY() << "," <<  Tester::p_fraccionaria(p2.getY()) << ";" <<
       (int)p2.getZ() << "," <<  Tester::p_fraccionaria(p2.getZ());
    std::string s(ss.str());
    return s;
}

Segment3::~Segment3() {
    if(Tester::DEBUG_DELET)
        std::cout << "Destruido el punto 3D" << std::endl;
}

void Segment3::generateProjections() {
    const int pxy = Figure3::PROJECTION_XY;
    const int pxz = Figure3::PROJECTION_XZ;
    const int pyz = Figure3::PROJECTION_YZ;
    projections[pxy] = Segment2(p1.getX(), p1.getY(), p2.getX(), p2.getY());
    projections[pxz] = Segment2(p1.getX(), p1.getZ(), p2.getX(), p2.getZ());
    projections[pyz] = Segment2(p1.getY(), p1.getZ(), p2.getY(), p2.getZ());
}

Vector3 Segment3::getP(float delta) {
    float x = p1.getX() + delta*(p2.getX() - p1.getX());
    float y = p1.getY() + delta*(p2.getY() - p1.getY());
    float z = p1.getZ() + delta*(p2.getZ() - p1.getZ());
    return {x, y, z};
}

Segment3 *Segment3::overlap(Segment3 *segment) {
    // FIXME: esto es asumiendo que ambos segmentos son linealmente
    //  dependientes. Es decir, ambos son parte de la misma linea. Esto no
    //  siempre pasa, asi que hay que hacer un comprobador.
    //  Nota: es probable que en los casos actuales en los que se usa esta
    //  funcion no sea necesario agregar esta comprobacion

    Vector3 pp1 = getMenorPX();
    Vector3 pp2 = getMayorPX();
    Vector3 pp3 = segment->getMenorPX();
    Vector3 pp4 = segment->getMayorPX();

    if(pp2.getX() > pp3.getX() || pp4.getX() > pp1.getX()){
        float inf = std::max(pp3.getX(), pp1.getX());
        float sup = std::min(pp2.getX(), pp4.getX());
        Vector3 vInf = (pp3.getX() > pp1.getX()) ? pp3 : pp1;
        Vector3 vSup = (pp2.getX() < pp4.getX()) ? pp2 : pp4;

        return new Segment3(vInf, vSup);
    }

    return nullptr;
}
