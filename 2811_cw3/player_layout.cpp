#include "player_layout.h"
#include <QScrollArea>
#include <iostream>
#include "the_button.h"
#include <QVideoWidget>
#include <QSlider>
#include <QComboBox>
#include <QStyle>
#include "volume.h"


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
            VolumeSlider *volumeSlider = dynamic_cast<VolumeSlider *>(o->widget());
            VolumeButton *muteButton = dynamic_cast<VolumeButton *>(o->widget());
            if(qw){
                qw->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
                qw->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
                qw->setGeometry(0+r.x(),r.height()-175+r.y(),r.width(), 165);
            }
            else if(videoWidget){
                   videoWidget->setGeometry(0+r.x(),0,r.width(), 0.625*r.height()-35);
            }
            else if(muteButton){
                muteButton->setGeometry(r.width()-270+r.x(),(0.625)*r.height()-30+5+r.y(),30, 30);
            }
            else if(volumeSlider){
                volumeSlider->setGeometry(r.width()-205+r.x(),(0.625)*r.height()-30+5+r.y(),200, 30);
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
