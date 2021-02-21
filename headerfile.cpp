#include <QDebug>
#include <QDataStream>
#include <iostream>
#include <QtEndian>
#include "headerfile.h"
#include "converter.h"

HeaderFile::HeaderFile(const QByteArray &bytes)
{
    _signatureLASF = QString::fromLocal8Bit(bytes.mid(0,4));
    _sourceId = Converter::byteToUInt(bytes.mid(4, 2));
    _globalEncoding = Converter::byteToUInt((bytes.mid(6, 2)));
    _projectId_GUID_data_1 = Converter::byteToULond(bytes.mid(8, 4));
    _projectId_GUID_data_2 = Converter::byteToUInt(bytes.mid(12, 2));
    _projectId_GUID_data_3 = Converter::byteToUInt(bytes.mid(14, 2));
    _projectId_GUID_data_4 = Converter::byteToCharArray(bytes.mid(16, 8));
    _versionMajor = Converter::byteToUchar(bytes.mid(24, 1));
    _versionMinor = Converter::byteToUchar(bytes.mid(25, 1));
    _systemIdentifier = QString::fromLocal8Bit(bytes.mid(26, 32));
    _generationSoftware = QString::fromLocal8Bit(bytes.mid(58, 32));
    _fileCreateDayAndYear = Converter::byteToUShort(bytes.mid(90, 2));
    _fileCreateYear = Converter::byteToUInt(bytes.mid(92, 2));
    _headerSize = Converter::byteToUInt(bytes.mid(94, 2));
    _offsetToPointData = Converter::byteToULond(bytes.mid(96, 4));
    _numberOfVariableLenghtRecords = Converter::byteToULond(bytes.mid(100, 4));
    _pointDataFormatId = Converter::byteToUchar(bytes.mid(104, 1));
    _pointDataRecordLength = Converter::byteToUInt(bytes.mid(105, 2));
    _numberOfPointRecords  = Converter::byteToULond(bytes.mid(107, 4));

    int pos = 111;
    for (int i = 0; i < 5; i++)
    {
        _numberOfPointsByReturn.append(Converter::byteToULond(bytes.mid(pos, 4)));
        pos = pos + 4;
    }

    _scaleFactorX = Converter::byteToDouble(bytes.mid(131, 8));
    _scaleFactorY = Converter::byteToDouble(bytes.mid(139, 8));
    _scaleFactorZ = Converter::byteToDouble(bytes.mid(147, 8));
    _offsetX = Converter::byteToDouble(bytes.mid(155, 8));
    _offsetY = Converter::byteToDouble(bytes.mid(163, 8));
    _offsetZ = Converter::byteToDouble(bytes.mid(171, 8));
    _maxX = Converter::byteToDouble(bytes.mid(179, 8));
    _minX = Converter::byteToDouble(bytes.mid(187, 8));
    _maxY = Converter::byteToDouble(bytes.mid(195, 8));
    _minY = Converter::byteToDouble(bytes.mid(203, 8));
    _maxZ = Converter::byteToDouble(bytes.mid(211, 8));
    _minZ = Converter::byteToDouble(bytes.mid(219, 8));
}

HeaderFile::HeaderFile()
{

}

QString HeaderFile::signatureLASF()
{
    return  _signatureLASF;
}

uint HeaderFile::sourceId()
{
    return _sourceId;
}

uint HeaderFile::globalEncoding()
{
    return _globalEncoding;
}

ulong HeaderFile::projectId_GUID_data_1()
{
    return _projectId_GUID_data_1;
}

uint HeaderFile::projectId_GUID_data_2()
{
    return _projectId_GUID_data_2;
}

uint HeaderFile::projectId_GUID_data_3()
{
    return _projectId_GUID_data_3;
}

QList<uchar> HeaderFile::projectId_GUID_data_4()
{
    return _projectId_GUID_data_4;
}

uchar HeaderFile::versionMajor()
{
    return _versionMajor;
}

uchar HeaderFile::versionMinor()
{
    return _versionMinor;
}

QString HeaderFile::systemIdentifier()
{
    return _systemIdentifier;
}

QString HeaderFile::generationSoftware()
{
    return _generationSoftware;
}

ushort HeaderFile::fileCreateDayAndYear()
{
    return  _fileCreateDayAndYear;
}

uint HeaderFile::fileCreateYear()
{
    return _fileCreateYear;
}

uint HeaderFile::headerSize()
{
    return _headerSize;
}

ulong HeaderFile::offsetToPointData()
{
    return _offsetToPointData;
}

ulong HeaderFile::numberOfVariableLenghtRecords()
{
    return _numberOfVariableLenghtRecords;
}

uchar HeaderFile::pointDataFormatId()
{
    return _pointDataFormatId;
}

uint HeaderFile::poitDataRecordLength()
{
    return _pointDataRecordLength;
}

ulong HeaderFile::numberOfPointRecords()
{
    return _numberOfPointRecords;
}

QList<ulong> HeaderFile::numberOfPointsByReturn()
{
    return _numberOfPointsByReturn;
}

double HeaderFile::scaleFactorX()
{
    return _scaleFactorX;
}

double HeaderFile::scaleFactorY()
{
    return _scaleFactorY;
}

double HeaderFile::scaleFactorZ()
{
    return _scaleFactorZ;
}

double HeaderFile::offsetX()
{
    return _offsetX;
}

double HeaderFile::offsetY()
{
    return _offsetY;
}

double HeaderFile::offsetZ()
{
    return _offsetZ;
}

double HeaderFile::maxX()
{
    return _maxX;
}

double HeaderFile::maxY()
{
    return _maxY;
}

double HeaderFile::maxZ()
{
    return _maxZ;
}

double HeaderFile::minX()
{
    return  _minX;
}

double HeaderFile::minY()
{
    return  _minY;
}

double HeaderFile::minZ()
{
    return  _minZ;
}

void HeaderFile::setMaxX(double maxX)
{
    _maxX = maxX;
}

void HeaderFile::setMaxY(double maxY)
{
    _maxY = maxY;
}

void HeaderFile::setMaxZ(double maxZ)
{
    _maxZ = maxZ;
}

void HeaderFile::setMinX(double minX)
{
    _minX = minX;
}

void HeaderFile::setMinY(double minY)
{
    _minY = minY;
}

void HeaderFile::setMinZ(double minZ)
{
    _minZ = minZ;
}

QByteArray HeaderFile::headerByteArray()
{
    QByteArray byteArray;

    byteArray.append(_signatureLASF.toUtf8());
    byteArray.append(_sourceId);
    byteArray.append(_globalEncoding);
    byteArray.append('\x00');
    byteArray.append('\x00');
    byteArray.append('\x00');
    byteArray.append('\x00');
    byteArray.append('\x00');
    byteArray.append('\x00');
    byteArray.append('\x00');
    byteArray.append('\x00');
    byteArray.append('\x00');
    byteArray.append('\x00');
    byteArray.append('\x00');

    for (uchar c : qAsConst(_projectId_GUID_data_4))
    {
        byteArray.append(c);
    }

    byteArray.append(_versionMajor);
    byteArray.append(_versionMinor);

    QByteArray systemIdentifierArray(_systemIdentifier.toLocal8Bit());
    byteArray.append(_systemIdentifier.toLocal8Bit());

    if (systemIdentifierArray.size() < 32)
    {
        for (int i = systemIdentifierArray.size(); i < 32 ; i++)
        {
            byteArray.append('\x00');
        }
    }

    QByteArray generationSoftwareArray(_systemIdentifier.toLocal8Bit());
    byteArray.append(_generationSoftware.toLocal8Bit());

    if (generationSoftwareArray.size() < 32)
    {
        for (int i = generationSoftwareArray.size(); i < 32 ; i++)
        {
            byteArray.append('\x00');
        }
    }

    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream << qToBigEndian(_fileCreateDayAndYear);
    stream << qToBigEndian(_fileCreateYear);
    stream << _headerSize;
    byteArray.append(data);

    byteArray.append(_offsetToPointData);
    byteArray.append(_numberOfVariableLenghtRecords);
    byteArray.append(_pointDataFormatId);
    byteArray.append(_pointDataRecordLength);
    byteArray.append(_numberOfPointRecords);

    for( ulong u : qAsConst(_numberOfPointsByReturn))
    {
        byteArray.append(u);
    }

    byteArray.append(_scaleFactorX);
    byteArray.append(_scaleFactorY);
    byteArray.append(_scaleFactorZ);
    byteArray.append(_offsetX);
    byteArray.append(_offsetY);
    byteArray.append(_offsetZ);
    byteArray.append(_maxX);
    byteArray.append(_minX);
    byteArray.append(_maxY);
    byteArray.append(_minY);
    byteArray.append(_maxZ);
    byteArray.append(_minZ);

    return byteArray;
}
