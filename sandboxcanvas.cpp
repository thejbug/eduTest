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

void SandboxCanvas::snapTo(Point p){
    float radius = 15;
    float currentMin = 1 << 30;

    //for each wire endpoint
    for(int i = 0; i < nodes.size(); i ++){
        Node* node = nodes[i];

        for(int j = 0; j < node->endpoints.size(); j ++){
            Endpoint end = node->endpoints[j];

            float d = dist(p, end.pos);

            if(d < currentMin && d < radius){
                snappedNode = node;
                indexOfSnappedEndpoint = j;
                currentMin = d;

            }
        }
    }
}

SandboxCanvas::SandboxCanvas(QWidget * parent):
    QLabel(parent)
{
    image = new QImage(width(), height(), QImage::Format_RGB32);
    setMouseTracking(true);
    p1Free = true;
    snappedNode = nullptr;
    mode = 0;

    arrow.load(QString("/Users/jaredemery/Downloads/arrow-right-solid.svg"));
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

    for(Line* line: lines){
        painter.drawLine(line->p1.x, line->p1.y, line->p2.x, line->p2.y);
    }

    for(Node* node: nodes){
        if(node->svg){
            int w = 50;
            int posX = node->posx;
            int posY = node->posy;
            QRect rect(posX - w/2, posY - w/2, w, w);

            node->svg->render(&painter, rect);
        }
    }


    Point p1;
    Point p2;

    snappedNode = nullptr;

    //select mode
    if(mode == 0){

    }    

    //wire mode
    else if (mode == 1){

        pen.setColor(QColor(175,175,175));
        pen.setWidth(8);
        painter.setPen(pen);

        if(p1Free){
            p2 = p1 = Point(x1, y1);

            snapTo(p1);

            if(snappedNode){
                p1 = p2 = snappedNode->endpoints[indexOfSnappedEndpoint].pos;
            }

            workingLine.p1 = p1;
        }
        else {

            p1 = workingLine.p1;
            p2 = Point(x1, y1);

            snapTo(p2);

            if(snappedNode){
                p2 = snappedNode->endpoints[indexOfSnappedEndpoint].pos;
            }

            workingLine.p2 = p2;
        }




        painter.drawLine(p1.x, p1.y, p2.x, p2.y);
    }

    else if (mode == 2){

        int rectw = 50;
        int recth = 50;
        QRect rect(x1 - rectw / 2, y1 - recth/2, 50, 50);

        arrow.render(&painter, rect);
    }


    setPixmap(QPixmap::fromImage(*image));
}

void SandboxCanvas::mousePressEvent(QMouseEvent *mouse)
{

    int mouseX = mouse->x();
    int mouseY = mouse->y();

    if(mode == 1){
        //placing the first point of a wire
        if(p1Free){
            //first line point was placed freely
            if(!snappedNode){
                Node* newNode = new Node;

                //there's no wire yet, so the endpoint has nothing to point to
                newNode->endpoints.push_back(Endpoint(Point(mouseX, mouseY), nullptr));
                workingLine.n1Endpoint = 0;

                nodes.push_back(newNode);
                //nodes should record their pos and have pointers to wires
            }
            //first line point was snapped onto an existing node
            else {
                snappedNode->endpoints.push_back(Endpoint(workingLine.p1, nullptr));
                workingLine.n1Endpoint = snappedNode->endpoints.size() - 1;
            }
        }
        //placing the second point
        else {
            //if the second point was placed freely
            if(!snappedNode){
                Node* newNode = new Node;
                Node* previousNode = nodes[nodes.size() - 1];



                Line* line = new Line(workingLine.p1, Point(mouseX, mouseY));
                line->n1Endpoint = workingLine.n1Endpoint;
                line->n2Endpoint = 0;

                //give the new node an endpoint with a pointer to the wire
                newNode->endpoints.push_back(Endpoint(Point(mouseX, mouseY), line));
                //give the endpoint on the other node a pointer to the wire also
                previousNode->endpoints[workingLine.n1Endpoint].wire = line;

                nodes.push_back(newNode);
                lines.push_back(line);
            }
            //if the second point was snapped onto an existing node
            else {
                Line* line = new Line(workingLine.p1, workingLine.p2);
                line->n1Endpoint = workingLine.n1Endpoint;
                line->n2Endpoint = indexOfSnappedEndpoint;
                //snappedNode->endpoints.push_back(Endpoint(workingLine.p2, ))
            }
        }

        p1Free = !p1Free;
    }
    else if (mode == 2){

        if(!snappedNode){

            Node* newNode = new Node;
            newNode->posx = mouseX;
            newNode->posy = mouseY;
            newNode->svg = new QSvgRenderer(QString("/Users/jaredemery/Downloads/arrow-right-solid.svg"));

            nodes.push_back(newNode);
        }
    }


    //mouseMoveEvent(mouse);
}

void SandboxCanvas::mouseReleaseEvent(QMouseEvent *ev)
{

}
void SandboxCanvas::selectPressed(){
    std::cout << "select" << std::endl;
    mode = 0;
}

void SandboxCanvas::wirePressed(){
    std::cout << "wire" << std::endl;

    mode = 1;
}

void SandboxCanvas::gatePressed(){
    std::cout << "gate" << std::endl;

    mode = 2;
}

