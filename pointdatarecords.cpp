#include "pointdatarecords.h"
#include "converter.h"
#include <QDebug>

PointDataRecords::PointDataRecords(const QByteArray &bytes)
{
    _x = Converter::byteToLond(bytes.mid(0, 4));
    _y = Converter::byteToLond(bytes.mid(4, 4));
    _z = Converter::byteToLond(bytes.mid(8, 4));
    _intensity = Converter::byteToUShort(bytes.mid(12, 2));
    _classification = Converter::byteToUchar(bytes.mid(15, 1));
    _scanAngleRank = Converter::byteToUchar(bytes.mid(16, 1));
    _userData = Converter::byteToUchar(bytes.mid(17, 1));
    _pointSourceId = Converter::byteToUInt(bytes.mid(18, 2));
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

uint PointDataRecords::intensity()
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

uint PointDataRecords::pointSourceId()
{
    return _pointSourceId;
}

uint PointDataRecords::red()
{
    return _red;
}

uint PointDataRecords::green()
{
    return _green;
}

uint PointDataRecords::blue()
{
    return _blue;
}
