#include "videolength_label.h"
#include <QTime>

void LengthLabel::setLength(qint64 position)
{
    setNum(static_cast<int>(position));

    QString tStr;
        QTime currentTimed((position / 60000) / 60, (position / 1000) / 60, (position / 1000), (position % 1000));
        QString format = "mm:ss";
        if (position > 60000)
            format = "hh:mm:ss";
        tStr = currentTimed.toString(format) + "   /      " ;//+ totalTime.toString(format);
        setText(tStr);
}
