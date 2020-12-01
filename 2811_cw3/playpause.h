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
    //void clicked();
    void setState(QMediaPlayer::State state);
};


#endif // PLAYPAUSE_H
