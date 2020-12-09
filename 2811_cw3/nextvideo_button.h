#ifndef NEXTVIDEO_BUTTON_H
#define NEXTVIDEO_BUTTON_H

#include <QPushButton>
#include <QStyle>
#include <QWidget>

class NextButton : public QPushButton {
    Q_OBJECT
public:
    NextButton(QWidget *parent) :  QPushButton( parent) {
        setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
        setFixedSize(40,40);
   }

};
// as with the play button, QStyle is used for the button icon
class PrevButton : public QPushButton {
    Q_OBJECT
public:
    PrevButton(QWidget *parent) :  QPushButton( parent) {
        setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
        setFixedSize(40,40);
   }

};

#endif // NEXTVIDEO_BUTTON_H
