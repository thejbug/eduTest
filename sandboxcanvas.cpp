#include "sandboxcanvas.h"
#include "iostream"
#include "QMouseEvent"
#include "qpainter.h"
#include "qsvgrenderer.h"
#include "qpen.h"

float dist(Point p1, Point p2)
{
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    return sqrt(dx*dx + dy*dy);
}

SandboxCanvas::SandboxCanvas(QWidget * parent):
    QLabel(parent)
{
    image = new QImage(width(), height(), QImage::Format_RGB32);
    setMouseTracking(true);
    p1Free = true;
}

void SandboxCanvas::mouseMoveEvent(QMouseEvent *mouse)
{
    int x1 = mouse->x();
    int y1 = mouse->y();

    delete image;
    image = new QImage(width(), height(), QImage::Format_RGB32);
    for(int row = 0; row < height(); row ++){
        for (int col = 0; col < width(); col ++){
            QColor c(255,255,255,255);
            image->setPixelColor(col, row, c);
        }
    }

    QPainter painter(image);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen;
    pen.setWidth(8);
    pen.setColor(QColor(255,100,0));
    painter.setPen(pen);

    for(Line line: lines){
        painter.drawLine(line.p1.x, line.p1.y, line.p2.x, line.p2.y);
    }

    //workingLine.p1 = Point(x1, y1);
    Point p1;
    Point p2;

    float radius = 15;
    if(p1Free)
    {

        p1 = Point(x1, y1);

        float dmin = 1 << 20;
        for(Line line: lines){
            float dist1 = dist(p1, line.p1);
            float dist2 = dist(p1, line.p2);

            if(dist1 < radius && dist1 < dmin){
                dmin = dist1;
                p1 = line.p1;
            }
            if(dist2 < radius && dist2 < dmin){
                dmin = dist2;
                p1 = line.p2;
            }
        }

        workingLine.p1 = p2 = p1;
    }
    else
    {
        p1 = workingLine.p1;
        p2 = Point(x1, y1);


        float dmin = 1 << 20;
        for(Line line: lines){
            float dist1 = dist(p2, line.p1);
            float dist2 = dist(p2, line.p2);

            if(dist1 < radius && dist1 < dmin){
                dmin = dist1;
                p2 = line.p1;
            }
            if(dist2 < radius && dist2 < dmin){
                dmin = dist2;
                p2 = line.p2;
            }
        }
        workingLine.p2 = p2;
    }


    pen.setColor(QColor(175,175,175));
    painter.setPen(pen);

    painter.drawLine(p1.x, p1.y, p2.x, p2.y);
    setPixmap(QPixmap::fromImage(*image));
}

void SandboxCanvas::mousePressEvent(QMouseEvent *ev)
{
    std::cout << width() << ", " << height();

    if(!p1Free){
        lines.push_back(workingLine);
    }

    p1Free = !p1Free;

    mouseMoveEvent(ev);
}

void SandboxCanvas::mouseReleaseEvent(QMouseEvent *ev)
{

}

//        p1 = Point(x1, y1);
//        p2 = Point(x1, y1);

//        float dmin = 1 << 20;
//        Point snapPoint;
//        int whichPoint = 0;

//        for(Line line: lines){
//            float dist1_1 = dist(p1, line.p1);
//            float dist1_2 = dist(p1, line.p2);
//            float dist2_1 = dist(p2, line.p1);
//            float dist2_2 = dist(p2, line.p2);

//            if(dist1_1 < radius && dist1_1 < dmin){
//                dmin = dist1_1;
//                snapPoint = line.p1;
//                whichPoint = 1;
//            }
//            if(dist1_2 < radius && dist1_2 < dmin){
//                dmin = dist1_2;
//                snapPoint = line.p2;
//                whichPoint = 1;
//            }
//            if(dist2_1 < radius && dist2_1 < dmin){
//                dmin = dist2_1;
//                snapPoint = line.p1;
//                whichPoint = 2;
//            }
//            if(dist2_2 < radius && dist2_2 < dmin){
//                dmin = dist2_2;
//                snapPoint = line.p2;
//                whichPoint = 2;
//            }
//        }

//        if(whichPoint == 1){
//            p1 = snapPoint;
//        } else if(whichPoint == 2){
//            p2 = snapPoint;
//            std::swap(p2, p1);
//        }
//        workingLine.p1 = p1;
//        workingLine.p2 = p2;
