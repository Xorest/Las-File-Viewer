#include <QFile>
#include "file.h"

File::File(QString path)
{
    _pathFile = path;
    readHeader();
}

HeaderFile *File::headerFile()
{
    return _headerFile;
}

VariableLengthRecordsFile *File::variableLengthRecordsFile()
{
    return _variableLengthRecordsFile;
}
#include <QDebug>
void File::readHeader()
{
    QFile file(_pathFile);

    if (file.open(QIODevice::ReadOnly))
    {
        QByteArray localByteArray = file.readAll();

        _headerFile = new HeaderFile(localByteArray.mid(0, 227));
        _variableLengthRecordsFile = new VariableLengthRecordsFile(localByteArray.mid(228,54));

        file.close();
    }
}
