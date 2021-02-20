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
        uint sourceId();
        uint globalEncoding();
        ulong projectId_GUID_data_1();
        uint projectId_GUID_data_2();
        uint projectId_GUID_data_3();
        QList<uchar> projectId_GUID_data_4();
        uchar versionMajor();
        uchar versionMinor();
        QString systemIdentifier();
        QString generationSoftware();
        uint fileCreateDayAndYear();
        uint fileCreateYear();
        uint headerSize();
        ulong offsetToPointData();
        ulong numberOfVariableLenghtRecords();
        uchar pointDataFormatId();
        uint poitDataRecordLength();
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
    private:
        QString _signatureLASF;
        uint _sourceId;
        uint _globalEncoding;
        ulong _projectId_GUID_data_1;
        uint _projectId_GUID_data_2;
        uint _projectId_GUID_data_3;
        QList<uchar> _projectId_GUID_data_4;
        uchar _versionMajor;
        uchar _versionMinor;
        QString _systemIdentifier;
        QString _generationSoftware;
        uint _fileCreateDayAndYear;
        uint _fileCreateYear;
        uint _headerSize;
        ulong _offsetToPointData;
        ulong _numberOfVariableLenghtRecords;
        uchar _pointDataFormatId;
        uint _pointDataRecordLength;
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
