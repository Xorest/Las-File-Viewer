#ifndef CONVERTER_H
#define CONVERTER_H

#include <QByteArray>
#include <QList>
#include <QString>

class Converter
{
public:
    static double byteToDouble(const QByteArray& byteArray);
    static uchar byteToUchar(const QByteArray& byteArray);
    static ulong byteToLond(const QByteArray&byteArray);
    static uint byteToInt(const QByteArray& byteArray);
    static QList<uchar> byteToCharArray(const QByteArray& byteArray);
};

#endif // CONVERTER_H
