#ifndef PLAYPAUSE_H
#define PLAYPAUSE_H


#include <QPushButton>
#include <QStyle>
#include <QWidget>

class PlayButton : public QPushButton {
    Q_OBJECT
public:
    PlayButton(QWidget *parent) :  QPushButton( parent) {
        setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
   }

};

class PauseButton : public QPushButton {
    Q_OBJECT
public:
    PauseButton(QWidget *parent) :  QPushButton( parent) {
        setIcon(style()->standardIcon(QStyle::SP_MediaPause));
   }

};

#endif // PLAYPAUSE_H
