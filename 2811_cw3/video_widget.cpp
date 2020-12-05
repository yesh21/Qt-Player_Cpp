#include "video_widget.h"
#include <QMouseEvent>
#include <QKeyEvent>

void VideoScreen::mouseDoubleClickEvent(QMouseEvent *event)
{
    setFullScreen(!isFullScreen());
  event->accept();
}

void VideoScreen::keyPressEvent(QKeyEvent *event)
{
    setFullScreen(!isFullScreen());
   event->accept();
}

void VideoScreen::setFullScr(bool value)
{
    setFullScreen(!value);
}
