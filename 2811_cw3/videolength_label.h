#ifndef VIDEOLENGTH_LABEL_H
#define VIDEOLENGTH_LABEL_H


#include <QLabel>
#include <QUrl>
#include <QStyle>
#include <QAudio>
#include <QWidget>
#include <QSlider>
#include <QMediaPlayer>

class LengthLabel : public QLabel {
    Q_OBJECT
public:
        LengthLabel(QWidget *parent) :  QLabel(parent) {

   }
private slots:
        void setLength(qint64);
private:
    bool playValue;
};

#endif // VIDEOLENGTH_LABEL_H
