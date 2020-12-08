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
         //qstyle used to set button icon
         connect(this, SIGNAL(released()), this, SLOT (clicked()));
     }
    void setMute(bool flipMute); //boolean for muted or not

private slots:
    void clicked();
    void changeIcon(int volVal); //icon changes depending on muted or not

signals:
    void mute(bool muted);
    void moveSlider(int volume); //allows button to affect the slider

private:
    //video starts muted
    bool muteValue = true;
};


class VolumeSlider : public QSlider {
    Q_OBJECT
public:
    VolumeSlider(QWidget *parent) :  QSlider(Qt::Horizontal, parent) {
        setTracking(true);
        setRange(0,100);
   }

private slots:
    void moveSlider(int volume);
};

#endif // VOLUME_H
