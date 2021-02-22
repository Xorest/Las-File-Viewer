#include <QDataStream>
#include <QtEndian>
#include "variablelengthrecordsfile.h"
#include "converter.h"

VariableLengthRecordsFile::VariableLengthRecordsFile(const QByteArray &bytes)
{
    _reserved = Converter::byteToUShort(bytes.mid(0, 2));
    _userId = QString::fromLocal8Bit(bytes.mid(2,16));
    _recordId = Converter::byteToUShort(bytes.mid(18,2));
    _recordLengthAfterHeader = Converter::byteToUShort(bytes.mid(20, 2));
    _description = QString::fromLocal8Bit(bytes.mid(22,32));
}

ushort VariableLengthRecordsFile::reserved()
{
    return _reserved;
}

QString VariableLengthRecordsFile::userId()
{
    return _userId;
}

ushort VariableLengthRecordsFile::recordId()
{
    return _recordId;
}

ushort VariableLengthRecordsFile::recordLengthAfterHeader()
{
    return _recordLengthAfterHeader;
}

QString VariableLengthRecordsFile::description()
{
    return _description;
}

QByteArray VariableLengthRecordsFile::variableLengthRecordsFileByteArray()
{
    QByteArray byteArray;
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);

    stream << qToBigEndian(_reserved);
    byteArray.append(data);

    QByteArray _userIdArray(_userId.toLocal8Bit());
    byteArray.append(_userId.toLocal8Bit());

    if (_userIdArray.size() < 16)
    {
        for (int i = _userIdArray.size(); i < 16 ; i++)
        {
            byteArray.append('\x00');
        }
    }

    QByteArray data1;
    QDataStream stream1(&data1, QIODevice::WriteOnly);
    stream1 << qToBigEndian(_recordId);
    stream1 << qToBigEndian(_recordLengthAfterHeader);
    byteArray.append(data1);

    QByteArray _descriptionArray(_description.toLocal8Bit());
    byteArray.append(_description.toLocal8Bit());

    if (_descriptionArray.size() < 32)
    {
        for (int i = _descriptionArray.size(); i < 32 ; i++)
        {
            byteArray.append('\x00');
        }
    }

    return byteArray;
}
