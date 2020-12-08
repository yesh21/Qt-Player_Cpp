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

using namespace std;

void ResponsiveLayout::setGeometry(const QRect &r) {

    QLayout::setGeometry(r);

    for (int i = 0; i < list_.size(); i++) { //iterates through all of our added widgets

        QLayoutItem *o = list_.at(i);

        try { //then specific geometries will be set for each one, depending on the widget
            QScrollArea *qw = dynamic_cast<QScrollArea *>(o->widget());
            QVideoWidget *videoWidget = dynamic_cast<QVideoWidget *>(o->widget());
            VolumeSlider *volumeSlider = dynamic_cast<VolumeSlider *>(o->widget());
            VolumeButton *muteButton = dynamic_cast<VolumeButton *>(o->widget());
            QSlider *videoSlider = dynamic_cast<QSlider *>(o->widget());
            ForwardButton *forwardSkipBtn = dynamic_cast<ForwardButton *>(o->widget());
            BackwardButton *backwardSkipBtn = dynamic_cast<BackwardButton *>(o->widget());
            PlayButton *playBtn = dynamic_cast<PlayButton *>(o->widget());
            LengthLabel *lengthLabel = dynamic_cast<LengthLabel *>(o->widget());
            FullScreenButton *fullScreen = dynamic_cast<FullScreenButton *>(o->widget());
            videoSearch *searchBox = dynamic_cast<videoSearch *>(o->widget());
            if(qw) {
                qw->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
                qw->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
                qw->setGeometry(0+r.x(),r.height()-175+r.y(),r.width(), 165);
            } else if(fullScreen) {
                fullScreen->setGeometry(r.width()-130,(0.625)*r.height()+10,120, 60);
            } else if(videoWidget && !videoWidget->isFullScreen()) {
                   videoWidget->setGeometry(0+r.x(),0,r.width(), 0.625*r.height()-35);
            } else if(videoWidget && videoWidget->isFullScreen()) {
                   videoWidget->showFullScreen();
            } else if(muteButton) {
                muteButton->setGeometry(r.x()+390,(0.625)*r.height()+10,60, 60);
            } else if(volumeSlider) {
                volumeSlider->setGeometry(460+r.x(),(0.625)*r.height()+25,r.width()-600, 30);
            } else if(videoSlider) {
                videoSlider->setGeometry(r.x()+5,(0.625)*r.height()-25,r.width()-125, 30);
            } else if(forwardSkipBtn) {
                forwardSkipBtn->setGeometry(195+r.x(),(0.625)*r.height()+10,60, 60);
            } else if(playBtn) {
                playBtn->setGeometry(260+r.x(),(0.625)*r.height()+10,60, 60);
            } else if(backwardSkipBtn) {
                backwardSkipBtn->setGeometry(325+r.x(),(0.625)*r.height()+10,60, 60);
            } else if (searchBox) {
                searchBox->setGeometry(10, (0.625)*r.height()+15, 180, 50);
            } else if(lengthLabel->whatsThis()=="length_label") {
                lengthLabel->setGeometry(r.width()-100,(0.625)*r.height()-25,60, 30);
            } else if(lengthLabel->whatsThis()=="duration_label") {
                lengthLabel->setGeometry(r.width()-40,(0.625)*r.height()-25,60, 30);
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
