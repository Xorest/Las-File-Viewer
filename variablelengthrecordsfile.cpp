#include "variablelengthrecordsfile.h"
#include "converter.h"

VariableLengthRecordsFile::VariableLengthRecordsFile(const QByteArray &bytes)
{
    _reserved = Converter::byteToUInt(bytes.mid(0, 2));
    _userId = QString::fromLocal8Bit(bytes.mid(2,16));
    _recordId = Converter::byteToUInt(bytes.mid(18,2));
    _recordLengthAfterHeader = Converter::byteToUInt(bytes.mid(20, 2));
    _description = QString::fromLocal8Bit(bytes.mid(22,32));
}

uint VariableLengthRecordsFile::reserved()
{
    return _reserved;
}

QString VariableLengthRecordsFile::userId()
{
    return _userId;
}

uint VariableLengthRecordsFile::recordId()
{
    return _recordId;
}

uint VariableLengthRecordsFile::recordLengthAfterHeader()
{
    return _recordLengthAfterHeader;
}

QString VariableLengthRecordsFile::description()
{
    return _description;
}
