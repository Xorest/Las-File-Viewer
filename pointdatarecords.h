//FORMAT: 2
#ifndef POINTDATARECORDS_H
#define POINTDATARECORDS_H

#include <QByteArray>
#include <QString>

class PointDataRecords
{
    public:
        PointDataRecords(const QByteArray& bytes);
        long x();
        long y();
        long z();
        ushort intensity();
        uchar neponyatno();
        uchar classification();
        uchar scanAngleRank();
        uchar userData();
        ushort pointSourceId();
        ushort red();
        ushort green();
        ushort blue();
        QByteArray pointByteArray();
    private:
        long _x;
        long _y;
        long _z;
        ushort _intensity;
        uchar _neponyatno;
        uchar _classification;
        uchar _scanAngleRank;
        uchar _userData;
        ushort _pointSourceId;
        ushort _red;
        ushort _green;
        ushort _blue;
};

#endif // POINTDATARECORDS_H
