#include <QDataStream>
#include <QtEndian>
#include <QIODevice>
#include "pointdatarecords.h"
#include "converter.h"


PointDataRecords::PointDataRecords(const QByteArray &bytes)
{
    _x = Converter::byteToLond(bytes.mid(0, 4));
    _y = Converter::byteToLond(bytes.mid(4, 4));
    _z = Converter::byteToLond(bytes.mid(8, 4));
    _intensity = Converter::byteToUShort(bytes.mid(12, 2));
    _neponyatno = Converter::byteToUchar(bytes.mid(14, 1));
    _classification = Converter::byteToUchar(bytes.mid(15, 1));
    _scanAngleRank = Converter::byteToUchar(bytes.mid(16, 1));
    _userData = Converter::byteToUchar(bytes.mid(17, 1));
    _pointSourceId = Converter::byteToUShort(bytes.mid(18, 2));
    _red = Converter::byteToUShort(bytes.mid(20, 2));
    _green = Converter::byteToUShort(bytes.mid(22, 2));
    _blue = Converter::byteToUShort(bytes.mid(24, 2));
}

long PointDataRecords::x()
{
    return _x;
}

long PointDataRecords::y()
{
    return _y;
}

long PointDataRecords::z()
{
    return _z;
}

void PointDataRecords::setX(long x)
{
    _x = x;
}

void PointDataRecords::setY(long y)
{
    _y = y;
}

void PointDataRecords::setZ(long z)
{
    _z = z;
}

ushort PointDataRecords::intensity()
{
    return  _intensity;
}

uchar PointDataRecords::classification()
{
    return _classification;
}

uchar PointDataRecords::scanAngleRank()
{
    return  _scanAngleRank;
}

uchar PointDataRecords::userData()
{
    return _userData;
}

ushort PointDataRecords::pointSourceId()
{
    return _pointSourceId;
}

ushort PointDataRecords::red()
{
    return _red;
}

ushort PointDataRecords::green()
{
    return _green;
}

ushort PointDataRecords::blue()
{
    return _blue;
}

QByteArray PointDataRecords::pointByteArray()
{
   QByteArray byteArray;
   QDataStream stream(&byteArray, QIODevice::WriteOnly);

   stream << qToBigEndian((quint32)_x);
   stream << qToBigEndian((quint32)_y);
   stream << qToBigEndian((quint32)_z);
   stream << qToBigEndian(_intensity);
   stream << _neponyatno;
   stream << _classification;
   stream << _scanAngleRank;
   stream << _userData;
   stream << qToBigEndian(_pointSourceId);
   stream << qToBigEndian(_red);
   stream << qToBigEndian(_green);
   stream << qToBigEndian(_blue);

   return byteArray;
}
