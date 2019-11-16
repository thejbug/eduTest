#include "sandboxcanvas.h"
#include "iostream"

SandboxCanvas::SandboxCanvas(QWidget * parent):
    QLabel(parent)
{

}

void SandboxCanvas::mouseMoveEvent(QMouseEvent *mouse)
{

}

void SandboxCanvas::mousePressEvent(QMouseEvent *ev)
{
    std::cout << width() << ", " << height();
    image = new QImage(width(), height(), QImage::Format_RGB32);
    for(int row = 0; row < height(); row ++){
        for (int col = 0; col < width(); col ++){
            QColor c(255,255,255,255);
            image->setPixelColor(col, row, c);
        }
    }
    setPixmap(QPixmap::fromImage(*image));
}

void SandboxCanvas::mouseReleaseEvent(QMouseEvent *ev)
{

}
