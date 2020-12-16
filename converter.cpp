#include "converter.h"

double Converter::byteToDouble(const QByteArray& byteArray)
{
    double result;
    memcpy(&result, byteArray.data(), byteArray.size());
    return result;
}

uchar Converter::byteToUchar(const QByteArray& byteArray)
{
    uchar result;
    memcpy(&result, byteArray.data(), byteArray.size());
    return result;
}

ulong Converter::byteToULond(const QByteArray& byteArray)
{
    ulong result;
    memcpy(&result, byteArray.data(), byteArray.size());
    return result;
}

long Converter::byteToLond(const QByteArray &byteArray)
{
    long result;
    memcpy(&result, byteArray.data(), byteArray.size());
    return result;
}

uint Converter::byteToInt(const QByteArray& byteArray)
{
    uint result;
    memcpy(&result, byteArray.data(), byteArray.size());
    return result;
}

QList<uchar> Converter::byteToCharArray(const QByteArray& byteArray)
{
    QList<uchar> result;

    for (int i = 0; i < byteArray.size() - 1; i++)
    {
        uchar localChar;
        memcpy(&localChar, byteArray.mid(i,  1).data(), 1);
        result.append(localChar);
    }

    return result;
}
