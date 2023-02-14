#ifndef TIMEUTILS_H
#define TIMEUTILS_H

#include <QString>

class TimeUtils
{
private:
    TimeUtils() {};

public:
    static int round(const int value);
    static QString convertToReadable(const int value);
    static QString makeTimeString(QString time);
};

#endif // TIMEUTILS_H
