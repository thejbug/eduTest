#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpainter.h"
#include <QSvgRenderer>
#include "iostream"
#include "QGraphicsBlurEffect"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    effect = new QGraphicsBlurEffect();
    ui->widget->setGraphicsEffect(effect);
    effect->setEnabled(false);
    sidebar = new QLabel(this);
    //sidebar->setMinimumWidth(300);
    //sidebar->setMaximumWidth(300);
    //sidebar->setMinimumHeight(300);
    //sidebar->setMaximumHeight(300);
    sidebar->setGeometry(-300, 0, 300, height());
    //sidebar->setGraphicsEffect(new QGraphicsBlurEffect);
    //sidebar->setPixmap(QPixmap::grabWidget(this));

    sidebar->setStyleSheet(QString("background-color: rgba(255,255,255,150);"));
//    ui->widget->setStyleSheet(QString("background-color: rgba(0,0,0,150);"));
//    ui->widget->setMask()

    //this->setWindowOpacity(0.5);
    //this->setAttribute(Qt::WA_TranslucentBackground)
//    QImage transparent(300, height(), QImage::Format_ARGB32);
//    for(int i = 0; i < transparent.height(); i ++){
//        //for(int )
//    }

    //sidebar->setPixmap()

    QPushButton * collapseSidebarBtn = new QPushButton("close", sidebar);
    sidebar->show();

    sidebarClose = new QPropertyAnimation(sidebar, "pos");
    sidebarClose->setDuration(150);
    sidebarClose->setStartValue(QPoint(0,0));
    sidebarClose->setEndValue(QPoint(-300,0));

    sidebarVisible = false;

    sidebarOpen = new QPropertyAnimation(sidebar, "pos");
    sidebarOpen->setDuration(150);
    sidebarOpen->setStartValue(QPoint(-300,0));
    sidebarOpen->setEndValue(QPoint(0,0));


    ui->collapseButton->setGeometry(25, 25, 115, 32);

//    buttonOpen = new QPropertyAnimation(ui->collapseButton, "pos");
//    buttonOpen->setDuration(150);
//    buttonOpen->setStartValue(QPoint(25,25));
//    buttonOpen->setEndValue(QPoint(325,25));

//    buttonClose = new QPropertyAnimation(ui->collapseButton, "pos");
//    buttonClose->setDuration(150);
//    buttonClose->setStartValue(QPoint(325,25));
//    buttonClose->setEndValue(QPoint(25,25));


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


    connect(ui->selectButton, &QPushButton::pressed, ui->testLabel, &SandboxCanvas::selectPressed);
    connect(ui->wireButton, &QPushButton::pressed, ui->testLabel, &SandboxCanvas::wirePressed);
    connect(ui->gateButton, &QPushButton::pressed, ui->testLabel, &SandboxCanvas::gatePressed);

//    connect(ui->gateButton, &QPushButton::pressed, [=](){
//        QRect rect = sidebar->rect();
//        std::cout << rect.x() << ", " << rect.y() << ", " << rect.width() << ", " << rect.height() << std::endl;
//        //QImage image = grab(sidebar->rect()).toImage();
//        //this->parentWidget()
//        sidebar->hide();
////        QPixmap pxmp = this->grab();

////        QLabel tempLabel;
////        tempLabel.setGeometry(0,0, sidebar->width(), sidebar->height());
////        tempLabel.setPixmap(pxmp);
////        tempLabel.setGraphicsEffect(new QGraphicsBlurEffect);
////        QPixmap blurred(sidebar->width(), sidebar->height());
////        QPainter painter(&blurred);
////        tempLabel.render(&painter);

////        sidebar->setPixmap(blurred);

//        QImage background = this->grab(rect).toImage();
//        int h = background.height();
//        int w = background.width();
//        QImage blurred(background.width(), background.height(), QImage::Format_RGB32);
//        for(int row = 0; row < background.height(); row ++){
//            for(int col = 0; col < background.width(); col ++){

//                int radius = 5;
//                int rsqr = (radius * 2 + 1)*(radius * 2 + 1);
//                int sumR = 0;
//                int sumG = 0;
//                int sumB = 0;
//                for(int rb = row - radius; rb < row + radius; rb ++){
//                    for(int cb = col - radius; cb < col + radius; cb ++){

//                        if(rb < 0 || rb > h - 1 || cb < 0 || cb > w - 1){
//                            rsqr -= 1;
//                            continue;
//                        }
//                        QColor bc = background.pixelColor(cb, rb);
//                        sumR += bc.red();
//                        sumG += bc.green();
//                        sumB += bc.blue();
//                    }
//                }
//                int avgR = sumR / rsqr;
//                int avgG = sumG / rsqr;
//                int avgB = sumB / rsqr;
//                //std::cout << avgR << ", " << avgG << ", " << avgB << std::endl;
//                //QColor bc = background.pixelColor(col, row);


//                blurred.setPixelColor(col, row, QColor(avgR, avgG, avgB));
//                //blurred.setPixelColor(col, row, bc);

//            }
//        }
//        sidebar->setPixmap(QPixmap::fromImage(blurred));
//        sidebar->show();
//        //sidebar->setScaledContents(true);
//    });

    connect(ui->collapseButton, &QPushButton::pressed, this, &MainWindow::collapseExpand);
    connect(collapseSidebarBtn, &QPushButton::pressed, this, &MainWindow::collapseExpand);
}

void MainWindow::collapseExpand()
{
    if(sidebarVisible){
        ui->collapseButton->show();
        sidebarClose->start();
        effect->setEnabled(false);

    } else {
        ui->collapseButton->hide();
        sidebarOpen->start();
        effect->setEnabled(true);
    }
    sidebarVisible = !sidebarVisible;

}


MainWindow::~MainWindow()
{
    delete ui;
}

