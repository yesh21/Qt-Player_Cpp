#include "player_layout.h"
#include <QScrollArea>
#include <iostream>
#include "the_button.h"
#include <QVideoWidget>
#include <QSlider>
#include <QComboBox>
#include <QStyle>
#include "volume.h"
#include "skip_buttons.h"
#include "playpause.h"
#include "videolength_label.h"
#include "fullscreen_button.h"
#include "videosearch.h"
#include "nextvideo_button.h"

using namespace std;

void ResponsiveLayout::setGeometry(const QRect &r) {

    QLayout::setGeometry(r);

    for (int i = 0; i < list_.size(); i++) { //iterates through all of our added widgets

        QLayoutItem *o = list_.at(i);

        try { //then specific geometries will be set for each one, depending on the widget
            QFrame *frame = dynamic_cast<QFrame *>(o->widget());
            QScrollArea *qw = dynamic_cast<QScrollArea *>(o->widget());
            QVideoWidget *videoWidget = dynamic_cast<QVideoWidget *>(o->widget());
            VolumeSlider *volumeSlider = dynamic_cast<VolumeSlider *>(o->widget());
            QSlider *videoSlider = dynamic_cast<QSlider *>(o->widget());
            FullScreenButton *fullScreen = dynamic_cast<FullScreenButton *>(o->widget());
            videoSearch *searchBox = dynamic_cast<videoSearch *>(o->widget());
            QComboBox *combo = dynamic_cast<QComboBox *>(o->widget());


            if (r.width() > r.height()){ //landscape mode
                if(qw) {
                    qw->setGeometry(0.8*r.width(),r.y(), r.width() - (0.8 * r.width()), r.height());
                } else if(fullScreen) {
                    fullScreen->setGeometry(r.x() + 5 + (0.8*r.width() - 5 - 120),0.8*r.height() - 65,120, 30);
                } else if(videoWidget && !videoWidget->isFullScreen()) {
                       videoWidget->setGeometry(0+r.x(),0,0.8*r.width(), 0.8*r.height() - 70);
                } else if(videoWidget && videoWidget->isFullScreen()) {
                       videoWidget->showFullScreen();
                } else if(volumeSlider) {
                    volumeSlider->setGeometry(r.x() + 5 + 265,0.8 * r.height() - 35 - 5 + 14,0.8*r.width() - 425,30);
                } else if(videoSlider) {
                    videoSlider->setGeometry(r.x() + 5,0.8*r.height() - 65, 0.8*r.width() - 10 - 60 - 60 - 120, 30);
                } else if (combo && combo->whatsThis()=="playrate") {
                    combo->setGeometry(r.x() + 0.8*r.width() - 120,0.8 * r.height() - 35,120,30);
                } else if (searchBox) {
                    searchBox->setGeometry(r.x() + 5, 0.8*r.height() + 25, 240, 30);
                } else if (combo && combo->whatsThis()=="sortby") {
                    combo->setGeometry(r.x() + 5 + 240 + 5,0.8*r.height() + 25, 240, 30);
                } else if(frame->whatsThis()=="duration_label") {
                    frame->setGeometry(r.x() + 5 + (0.8*r.width() - 5 - 60 - 120),0.8*r.height() - 65,60, 30);
                } else if(frame->whatsThis()=="length_label") {
                    frame->setGeometry(r.x() + 5 + (0.8*r.width() - 5 - 60 - 60 - 120),0.8*r.height() - 65,60, 30);
                } else if (frame->whatsThis() == "buttons") {
                    frame->setGeometry(r.x(),0.8 * r.height() - 35 - 5,265, 60);
                }
            }
            else { //portrait mode
                if(qw) {
                    qw->setGeometry(0+r.x(),r.height()-195+r.y(),r.width(), 185);
                } else if(fullScreen) {
                    fullScreen->setGeometry(r.width()-130,(0.625)*r.height()-25,120, 40);
                } else if(videoWidget && !videoWidget->isFullScreen()) {
                       videoWidget->setGeometry(0+r.x(),0,r.width(), 0.625*r.height()-35);
                } else if(videoWidget && videoWidget->isFullScreen()) {
                       videoWidget->showFullScreen();
                } else if(volumeSlider) {
                    volumeSlider->setGeometry(270+r.x(),(0.625)*r.height()+25,r.width()-425, 30);
                } else if(videoSlider) {
                    videoSlider->setGeometry(r.x()+5,(0.625)*r.height()-25,r.width()-255, 30);
                } else if (combo && combo->whatsThis()=="playrate") {
                    combo->setGeometry(r.width()-130,(0.625)*r.height()+25,120, 40);
                } else if (searchBox) {
                    searchBox->setGeometry(10, r.height()-230+r.y(), 150, 25);
                } else if (combo && combo->whatsThis()=="sortby") {
                    combo->setGeometry(210, r.height()-230+r.y(), 150, 25);
                } else if(frame->whatsThis()=="length_label") {
                    frame->setGeometry(r.width()-230,(0.625)*r.height()-25,60, 30);
                } else if(frame->whatsThis()=="duration_label") {
                    frame->setGeometry(r.width()-170,(0.625)*r.height()-25,60, 30);
                } else if (frame->whatsThis() == "buttons") {
                    frame->setGeometry(5+r.x(),(0.625)*r.height()+10,265, 60);
                }
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
