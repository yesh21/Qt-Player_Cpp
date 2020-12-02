#ifndef VOLUME_H
#define VOLUME_H


#include <QPushButton>
#include <QStyle>
#include <QWidget>
#include <QSlider>

class VolumeButton : public QPushButton {
    Q_OBJECT

public:
     VolumeButton(QWidget *parent) :  QPushButton(parent) {
         setIconSize(QSize(60,60));
         setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
         connect(this, SIGNAL(released()), this, SLOT (flipIcon()));
     }
    void setMute(bool flipMute);

private slots:
    void flipIcon();

private:
    bool muteValue = true;
};

#endif // VOLUME_H
