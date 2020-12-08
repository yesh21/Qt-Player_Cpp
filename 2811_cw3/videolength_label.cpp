#include "videolength_label.h"
#include <QTime>

void LengthLabel::setLength(qint64 position) {
    setNum(static_cast<int>(position));

    QString tStr;
        QTime currentTimed((position / 60000) / 60, (position / 1000) / 60, (position / 1000), (position % 1000));
        QString format = "mm:ss"; //sets label formatting if less than an hour
        if (position > 60000){
            format = "hh:mm:ss"; //sets label formatting if longer than an hour
        }
        tStr = currentTimed.toString(format) + "   /      " ;//+ totalTime.toString(format);
        setText(tStr);
}
