#include "blurredsidebar.h"
#include "qgraphicseffect.h"
#include "iostream"

BlurredSidebar::BlurredSidebar(QWidget* parent):
    QLabel(parent)
{
    this->parent = parent;
}

void BlurredSidebar::blurBackground()
{
    //std::cout << "painting\n";// << std::endl;
    hide();

    int radius = 100;
    QRect rectangle(pos().x() - radius, pos().y(), width() + 2* radius, height());
    QPixmap background = parent->grab(rectangle);

    QLabel tempLabel;
    tempLabel.setGeometry(rectangle);
    tempLabel.hide();
    tempLabel.setPixmap(background);
    tempLabel.setAlignment(Qt::AlignCenter);
    QGraphicsBlurEffect* effect = new QGraphicsBlurEffect;
    effect->setBlurRadius(radius);
    effect->setEnabled(true);

    tempLabel.setGraphicsEffect(effect);

    QPixmap blurred = tempLabel.grab(rectangle);


    setPixmap(blurred);
    //setStyleSheet(QString("background-color: red;"));
    show();
}
