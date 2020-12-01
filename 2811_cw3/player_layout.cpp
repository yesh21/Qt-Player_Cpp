#include "player_layout.h"
#include <QScrollArea>
#include <iostream>
#include "the_button.h"
#include <QVideoWidget>
#include <QSlider>
#include <QComboBox>
#include <QStyle>
#include "playpause.h"


using namespace std;

// you should probably make extensive changes to this function
void ResponsiveLayout::setGeometry(const QRect &r /* our layout should always fit inside r */ ) {

    QLayout::setGeometry(r);

    // for all the Widgets added in ResponsiveWindow.cpp
    for (int i = 0; i < list_.size(); i++) {

        QLayoutItem *o = list_.at(i);

        try {
            QScrollArea *qw = dynamic_cast<QScrollArea *>(o->widget());
            QVideoWidget *videoWidget = dynamic_cast<QVideoWidget *>(o->widget());
            QSlider *videoSlider = dynamic_cast<QSlider *>(o->widget());
            PlayButton *playBtn = dynamic_cast<PlayButton *>(o->widget());
            PauseButton *pauseBtn = dynamic_cast<PauseButton *>(o->widget());
            if(qw){
                qw->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
                qw->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
                qw->setGeometry(0+r.x(),r.height()-175+r.y(),r.width(), 165);
            }
            else if(videoWidget){
                   videoWidget->setGeometry(0+r.x(),0,r.width(), 0.725*r.height()-35);
            }

            else if(videoSlider){
                videoSlider->setGeometry(140+r.x(),(0.725)*r.height()+5-30+r.y(),r.width()-420, 30);
            }
            else if(playBtn){
                playBtn->setGeometry(r.width()/2+r.x(),(0.725)*r.height()+5-30+r.y(),30, 30);
            }
            else if(pauseBtn){
                pauseBtn->setGeometry(r.width()/2-35+r.x(),(0.725)*r.height()+5-30+r.y(),30, 30);
            }
        }
        catch (bad_cast) {
            // bad_case: cast failed on reference...
            cout << "warning, unknown widget class in layout" << endl;
        }
    }
}

// following methods provide a trivial list-based implementation of the QLayout class
int ResponsiveLayout::count() const {
    return list_.size();
}

QLayoutItem *ResponsiveLayout::itemAt(int idx) const {
    return list_.value(idx);
}

QLayoutItem *ResponsiveLayout::takeAt(int idx) {
    return idx >= 0 && idx < list_.size() ? list_.takeAt(idx) : 0;
}

void ResponsiveLayout::addItem(QLayoutItem *item) {
    list_.append(item);
}

QSize ResponsiveLayout::sizeHint() const {
    return minimumSize();
}

QSize ResponsiveLayout::minimumSize() const {
    return QSize(300,300);
}

ResponsiveLayout::~ResponsiveLayout() {
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}
