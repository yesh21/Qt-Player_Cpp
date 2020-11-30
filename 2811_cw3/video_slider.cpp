#include "video_slider.h"

void VideoSlider::SetValue(qint64 position)
{
    setValue(position);
}
void VideoSlider::SetRange(qint64 position)
{
    setRange(0,position);
}
