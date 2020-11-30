#include "volume.h"

void VolumeButton::setMute(bool flipMute)
{
    muteValue = !flipMute;
}

void VolumeButton::clicked()
{

    if (!muteValue){
        setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
        emit moveSlider(0);
    }
    else
    {
        setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
        emit(moveSlider(10));
    }
        setMute(muteValue);
        emit mute(muteValue);
}

void VolumeButton::changeIcon(int volVal)
{

    if (volVal == 0)
    {
        setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
    }
    if (volVal != 0 && muteValue == false)
    {
        setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    }
}

void VolumeSlider::moveSlider(int volume)
{
    setSliderPosition(volume);
}
