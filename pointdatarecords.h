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
        uint intensity();
        QString neponyatno();
        uchar classification();
        uchar scanAngleRank();
        uchar userData();
        uint pointSourceId();
        uint red();
        uint green();
        uint blue();
    private:
        long _x;
        long _y;
        long _z;
        uint _intensity;
        QString _neponyatno;
        uchar _classification;
        uchar _scanAngleRank;
        uchar _userData;
        uint _pointSourceId;
        uint _red;
        uint _green;
        uint _blue;
};

#endif // POINTDATARECORDS_H
