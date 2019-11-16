#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpainter.h"
#include <QSvgRenderer>
#include "iostream"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ui->testLabel.set


    //ON MOUSE CLICK / ENTER PRESSED (WHEN THE MODEL IS CHANGED)
    //create image
    //for each component in the model
        //identify which type it is (wire / gate / etc)
        //draw it using the appropriate qt tool
        //(for svgs: QSvgRenderer, for lines: drawLine())
    //save that qimage as a member

    //send a signal with info about the component that was just dropped,
    //(if it was placed freely, it's not connected to anything, it will be an isolated vertex in the graph.
    //if any part of it was snapped, tell the model which part and what it snapped on to.


    //ON MOUSE MOVEMENT:
    //add the following to the image (that already contains the components that have been added to the model)


    //if a component is being dragged:
    //depending on it's type:
        //if it's a wire:
            //if it's brand new (both of it's endpoints are free):
                //check if any of the endpoints is near a vertex
                    //if it is, snap the coords of the closest point to that vertex
                //else do nothing with the points
            //it it's not brand new (one of it's endpoints is already placed, that endpoint will be locked)
                //check if the other is near a vertex
                    //if it is, snap the coords to the vertex
            //drawLine(x1,x2,y1,y2) (this is just a highlight, it will need a different color than placed wires)
                //check if the line intersects other lines
                    //if it does, break it up into multiple segments and draw an arc between
        //if its a gate:
            //check if any of it's input / or output wire endpoints is near a vertex
                //if they are, snap the closest point onto that vertex
            //else do nothing to the coords
            //render the svg in the appropriate spot

    //if no component is selected, you are in 'select' mode
    //just check which component is closest to your mouse and highlight it
    //redraw it with a different color, on top of the old one?)







//    QImage image(100,100, QImage::Format_RGB32);
//    for(int row = 0; row < image.height(); row ++){
//        for (int col = 0; col < image.width(); col ++){
//            QColor c(255,255,255,255);
//            image.setPixelColor(col, row, c);
//        }
//    }

//    QPen pen;

//    pen.setColor(QColor(255,0,0));
//    pen.setWidth(10);




//    QPainter painter(&image);

//    QSvgRenderer svg(QString("/Users/jaredemery/Downloads/hourglass-half-solid.svg"));

//    std::cout << "is valid: " << svg.isValid() << std::endl;
//    svg.render(&painter);

//    painter.setPen(pen);

//    painter.drawLine(5,5, 20, 20);


//    ui->testLabel->setPixmap(QPixmap::fromImage(image));
//    ui->testLabel->setScaledContents(true);

    //ui->testLabel = new SandboxCanvas(this);
    ui->testLabel->setStyleSheet(QString("background-color: black;"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

