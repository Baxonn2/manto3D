//
// Created by Braulio Lobo on 02-02-20.
//

#ifndef MANTO_POLYGON2_H
#define MANTO_POLYGON2_H

#include "util/clipper/clipper.hpp"
#include <list>
#include "Figure2.h"
#include "Triangle2.h"
#include "Segment2.h"
#include "Point2.h"
#include "Vector3.h"
#include <Figure3.h>

class Polygon3;

using namespace std;
using namespace ClipperLib;

class Polygon2 : public Figure2{

    // Vectores que forman el poligono
    Path path;          // Vectores del poligono
    Paths solutions;    // Soluciones de las operaciones

    // El valor de precision tiene que ser potencia de 10. Este se utiliza
    // como multiplicador y divisor, con el fin de obtener mayor o menor
    // precision en los calculos de las operaciones realizadas a los
    // poligonos (Como unionWith, intersect, difference, etc)
    float precision = 1000;

private:

    static list<Polygon2*> pathsToPolygons(const Paths& paths);

public:

    /**
     * Cosntructor simple y por defecto
     */
    Polygon2();

    /**
     * Constructor de poligono
     * @param vectores  - Arreglo de vectores. Corresponden a enteros
     *                    pareados, de la forma: {x1,y1,x2,y2..., xn, yn}.
     * @param nVectores - Numero de vectores que conforman el poligono.
     */
    Polygon2(const int* vectores, int nVectores);

    /**
     * Constructor de poligono
     * @param vectores  - Arreglo de vectores. Corresponden a enteros
     *                    pareados, de la forma: {x1,y1,x2,y2..., xn, yn}.
     * @param nVectores - Numero de vectores que conforman el poligono.
     */
    Polygon2(const float* vectores, int nVectores);

    /**
     * Constructor de poligonos con path
     */
    explicit Polygon2(Path path);

    /**
     * Genera una interseccion entre el poligono (this) y el ingresado como
     * parametro.
     * @param polygon   - Poligono con el que se quiere hacer la interseccion.
     * @return          - Retorna los poligonos generados por la interseccion.
     */
    list<Polygon2*> intersect(const Polygon2& polygon);

    /**
     * Genera una union entre el poligono (this) y el ingresado como
     * parametro.
     * @param polygon   - Poligono con el que se quiere hacer la union.
     * @return          - Retorna los poligonos generados por la union.
     */
    list<Polygon2*> unionWith(const Polygon2& polygon);

    /**
     * Genera la diferencia entre el poligono (this) y el ingresado como
     * parametro.
     * @param polygon   - Poligono con el que se quiere hacer la diferencia.
     * @return          - Retorna los poligonos generados por la diferencia.
     */
    list<Polygon2*> difference(const Polygon2& polygon);

    /**
     * Rellena la lista fragments con fragmentos no dominados, los cuales son
     * producto de una fragmentacion generada por el punto ingrasado como
     * parametro.
     * @param p             - Punto que fragmenta al poligono
     * @param fragments     - Lista de fragmentos que se va a llenar.
     */
    void fragmentedBy(Point2* p, std::list<Figure2*> &fragments);

    /**
     * Rellena la lista fragments con fragmentos no dominados, los cuales son
     * producto de una fragmentacion generada por el segmento ingrasado como
     * parametro.
     * @param s             - Segmento que fragmenta al poligono
     * @param fragments     - Lista de fragmentos que se va a llenar.
     */
    void fragmentedBy(Segment2* s, std::list<Figure2*> &fragments);

    /**
     * Rellena la lista fragments con fragmentos no dominados, los cuales son
     * producto de una fragmentacion generada por el triangulo ingrasado como
     * parametro.
     * @param t             - Triangulo que fragmenta al poligono
     * @param fragments     - Lista de fragmentos que se va a llenar.
     */
    void fragmentedBy(Triangle2* t, std::list<Figure2*> &fragments);

    /**
     * Rellena la lista fragments con fragmentos no dominados, los cuales son
     * producto de una fragmentacion generada por el poligono ingrasado como
     * parametro.
     * @param p             - Poligono que fragmeta al poligono
     * @param fragments     - Lista de fragmentos que se va a llenar.
     */
    void fragmentedBy(Polygon2* p, std::list<Figure2*> &fragments);

    /**
     * Calcula la proyeccion de este poligono en el plano del ingresado como
     * parametro
     * @param p3    - Poligono contenido en el plano donde se generará el
     *                poligono en tres dimensiones.
     * @param PROJECTION_PLANE - Plano al que pertenece esta proyeccion
     * @return      - Retorna un poligono de tres dimensiones.
     */
    Polygon3* toPolygon3(Polygon3* p3, int PROJECTION_PLANE);

    const Path &getPath() const;

    // Funciones virutales
    virtual float getKey();
    virtual std::string toString();
    virtual std::string toGraphString(int PROJECTION_PLANE);

};


#endif //MANTO_POLYGON2_H