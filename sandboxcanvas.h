#ifndef SANDBOXCANVAS_H
#define SANDBOXCANVAS_H

#include "qlabel.h"
#include "math.h"
#include "vector"
#include "qsvgrenderer.h"

struct Point{
public:
    int x, y;
    Point(): x(0), y(0) {}
    Point(int a, int b): x(a), y(b){}
};

class Node;

struct Line{
public:
    Point p1;
    Point p2;
    Node* n1;
    Node* n2;
    int n1Endpoint;
    int n2Endpoint;
    Line(){}
    Line(Point start, Point end): p1(start), p2(end) {}
};

struct Endpoint {
public:
    Point pos;
    Line *wire;
    Endpoint(){}
    Endpoint(Point p, Line* w): pos(p), wire(w){}
};

class Node {
public:
    int posx;
    int posy;
    std::vector<Endpoint> endpoints;
    QSvgRenderer* svg;

    Node(): svg(nullptr){}
};



class SandboxCanvas: public QLabel
{
    Q_OBJECT

    QImage* image;

    QSvgRenderer arrow;

    std::vector<Line*> lines;
    std::vector<Node*> nodes;
    Node* snappedNode;
    int indexOfSnappedEndpoint;
    Line workingLine;
    bool p1Free;

    int mode;

public:
    SandboxCanvas(QWidget* parent);

    void mouseMoveEvent(QMouseEvent *ev) override;
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;

    void snapTo(Point p);

public slots:
    void selectPressed();
    void wirePressed();
    void gatePressed();

};

#endif // SANDBOXCANVAS_H
