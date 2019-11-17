#ifndef SANDBOXCANVAS_H
#define SANDBOXCANVAS_H

#include "qlabel.h"
#include "math.h"
#include "vector"

struct Point{
public:
    int x, y;
    Point(): x(0), y(0) {}
    Point(int a, int b): x(a), y(b){}
};

struct Line{
public:
    Point p1;
    Point p2;
    Line(){}
    Line(Point start, Point end): p1(start), p2(end) {}
};



class SandboxCanvas: public QLabel
{
    Q_OBJECT

    QImage* image;
    std::vector<Line> lines;
    Line workingLine;
    bool p1Free;

public:
    SandboxCanvas(QWidget* parent);

    void mouseMoveEvent(QMouseEvent *ev) override;
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;

};

#endif // SANDBOXCANVAS_H
