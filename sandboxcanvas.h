#ifndef SANDBOXCANVAS_H
#define SANDBOXCANVAS_H

#include "qlabel.h"

class SandboxCanvas: public QLabel
{
    Q_OBJECT

    QImage* image;

public:
    SandboxCanvas(QWidget* parent);

    void mouseMoveEvent(QMouseEvent *ev) override;
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;

};

#endif // SANDBOXCANVAS_H
