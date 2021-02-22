#ifndef HEADERFILE_H
#define HEADERFILE_H

#include <QString>
#include <QByteArray>
#include <QList>

class HeaderFile
{
    public:
        HeaderFile(const QByteArray& bytes);
        HeaderFile();
        QString signatureLASF();
        ushort sourceId();
        ushort globalEncoding();
        ulong projectId_GUID_data_1();
        ushort projectId_GUID_data_2();
        ushort projectId_GUID_data_3();
        QList<uchar> projectId_GUID_data_4();
        uchar versionMajor();
        uchar versionMinor();
        QString systemIdentifier();
        QString generationSoftware();
        ushort fileCreateDayAndYear();
        ushort fileCreateYear();
        ushort headerSize();
        ulong offsetToPointData();
        ulong numberOfVariableLenghtRecords();
        uchar pointDataFormatId();
        ushort poitDataRecordLength();
        ulong numberOfPointRecords();
        QList<ulong> numberOfPointsByReturn();
        double scaleFactorX();
        double scaleFactorY();
        double scaleFactorZ();
        double offsetX();
        double offsetY();
        double offsetZ();
        double maxX();
        double maxY();
        double maxZ();
        double minX();
        double minY();
        double minZ();
        void setMaxX(double maxX);
        void setMaxY(double maxY);
        void setMaxZ(double maxZ);
        void setMinX(double minX);
        void setMinY(double minY);
        void setMinZ(double minZ);
        void setOffsetToPointData(ulong offsetToPointData);
        QByteArray headerByteArray();
    private:
        QString _signatureLASF;
        ushort _sourceId;
        ushort _globalEncoding;
        ulong _projectId_GUID_data_1;
        ushort _projectId_GUID_data_2;
        ushort _projectId_GUID_data_3;
        QList<uchar> _projectId_GUID_data_4;
        uchar _versionMajor;
        uchar _versionMinor;
        QString _systemIdentifier;
        QString _generationSoftware;
        ushort _fileCreateDayAndYear;
        ushort _fileCreateYear;
        ushort _headerSize;
        ulong _offsetToPointData;
        ulong _numberOfVariableLenghtRecords;
        uchar _pointDataFormatId;
        ushort _pointDataRecordLength;
        ulong _numberOfPointRecords;
        QList<ulong> _numberOfPointsByReturn;
        double _scaleFactorX;
        double _scaleFactorY;
        double _scaleFactorZ;
        double _offsetX;
        double _offsetY;
        double _offsetZ;
        double _maxX;
        double _maxY;
        double _maxZ;
        double _minX;
        double _minY;
        double _minZ;
};

#endif // HEADERFILE_H
