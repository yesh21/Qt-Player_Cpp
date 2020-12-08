#ifndef SKIP_BUTTONS_H
#define SKIP_BUTTONS_H


#include <QPushButton>
#include <QStyle>
#include <QWidget>

class ForwardButton : public QPushButton {
    Q_OBJECT
public:
    ForwardButton(QWidget *parent) :  QPushButton( parent) {
        setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
   }

};
// as with the play button, QStyle is used for the button icon
class BackwardButton : public QPushButton {
    Q_OBJECT
public:
    BackwardButton(QWidget *parent) :  QPushButton( parent) {
        setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
   }

};

#endif // SKIP_BUTTONS_H
