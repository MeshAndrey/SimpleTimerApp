#include "TimeUtils.h"


int TimeUtils::round(const int value)
{
    if (value == 0)
        return value; // zero
    if ((value >= 1000) && (value % 1000 == 0))
        return value; // already round

    if (((value % 1000) > 500) && ((value % 1000) <= 999))
    {
        return (value - (value % 1000) + 1000);
    }
    else if (((value % 1000) >= 1) && ((value % 1000) <= 500))
    {
        return (value - (value % 1000));
    }

    return value;
}

QString TimeUtils::convertToReadable(const int value)
{
    if (value < 0)
        return "Error value";

    const int h = value / (1000 * 60 * 60);                                 // hours
    const int m = (value - (h  * 1000 * 60 * 60)) / (1000 * 60);            // minutes
    const int s = (value - (h  * 1000 * 60 * 60) - (m * 1000 * 60)) / 1000; // seconds

    if (h > 0)
        return QString("%1:%2:%3").arg(makeTimeString(QString::number(h)),
                                       makeTimeString(QString::number(m)),
                                       makeTimeString(QString::number(s)));

    if (m > 0)
        return QString("%1:%2").arg(makeTimeString(QString::number(m)),
                                    makeTimeString(QString::number(s)));

    if (s > 0)
        return makeTimeString(QString::number(s));

    return "00";
}

QString TimeUtils::makeTimeString(QString time) // don't know how to name this shit
{
    if (time.isEmpty())
        return time;

    return time.length() == 2 ? time : time.prepend("0");
}
