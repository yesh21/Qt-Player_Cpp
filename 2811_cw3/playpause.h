#ifndef PLAYPAUSE_H
#define PLAYPAUSE_H


#include <QPushButton>
#include <QStyle>
#include <QWidget>
#include <QMediaPlayer>

class PlayButton : public QPushButton {
    Q_OBJECT
public:
    PlayButton(QWidget *parent) :  QPushButton( parent) {
        setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
   }
private slots:
    void setState(QMediaPlayer::State state);
};

class PauseButton : public QPushButton {
    Q_OBJECT
public:
    PauseButton(QWidget *parent) :  QPushButton( parent) {
        setIcon(style()->standardIcon(QStyle::SP_MediaPause));
   }
private slots:
    void setState(QMediaPlayer::State state);
};

#endif // PLAYPAUSE_H
