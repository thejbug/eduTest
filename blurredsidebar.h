#ifndef BLURREDSIDEBAR_H
#define BLURREDSIDEBAR_H

#include "qlabel.h"

class BlurredSidebar: public QLabel
{
    Q_OBJECT

    QWidget* parent;

public:
    BlurredSidebar(QWidget* parent);

    //void paintEvent(QPaintEvent *) override;
public slots:
    void blurBackground();
};

#endif // BLURREDSIDEBAR_H
