#ifndef VIDEO_SLIDER_H
#define VIDEO_SLIDER_H


#include <QPushButton>
#include <QStyle>
#include <QWidget>
#include <QSlider>

class VideoSlider : public QSlider {
    Q_OBJECT
public:
    VideoSlider(QWidget *parent) :  QSlider(Qt::Horizontal, parent) {
        setTracking(true);
        setRange(0,0);
   }

private slots:
    void SetValue(qint64 volume);
    void SetRange(qint64 volume);
};

#endif // VIDEO_SLIDER_H
