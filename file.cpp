#include <QFile>
#include "file.h"

File::File(QString path)
{
    _pathFile = path;
    readFile();

}

HeaderFile *File::headerFile()
{
    return _headerFile;
}

VariableLengthRecordsFile *File::variableLengthRecordsFile()
{
    return _variableLengthRecordsFile;
}

QList<PointDataRecords *> File::points()
{
    return _points;
}

void File::readFile()
{
    QFile file(_pathFile);

    if (file.open(QIODevice::ReadOnly))
    {
        QByteArray localByteArray = file.readAll();
        _headerFile = new HeaderFile(localByteArray.mid(0, 227));
        _variableLengthRecordsFile = new VariableLengthRecordsFile(localByteArray.mid(_headerFile->headerSize(), 54));
        _points = getPoints(localByteArray.mid(_headerFile->offsetToPointData()));
        file.close();
    }
}

QList<PointDataRecords*> File::getPoints(const QByteArray& bytes)
{
    QList<PointDataRecords*> result;
    int count = bytes.size() / 26;

    for (int i = 0; i < count; i++)
    {
        PointDataRecords* point = new PointDataRecords(bytes.mid(i * 26, 26));
        result.append(point);
    }

    return result;
}


