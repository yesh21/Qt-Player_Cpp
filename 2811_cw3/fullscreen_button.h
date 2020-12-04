#ifndef FULLSCREEN_BUTTON_H
#define FULLSCREEN_BUTTON_H

#include <QPushButton>
#include <QWidget>

class FullScreenButton : public QPushButton {
    Q_OBJECT
public:
    FullScreenButton(QWidget *parent) :  QPushButton( parent) {
        setGeometry(0,0,100,100);
        setText("full Screen");
   }

};
#endif // FULLSCREEN_BUTTON_H
