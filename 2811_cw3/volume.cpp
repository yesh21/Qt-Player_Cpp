#include "volume.h"

void VolumeButton::setMute(bool flipMute)
{
    muteValue = !flipMute;
}

void VolumeButton::flipIcon()
{

    if (!muteValue){
        setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));

    }
    else
    {
        setIcon(style()->standardIcon(QStyle::SP_MediaVolume));

    }
        setMute(muteValue);

}



