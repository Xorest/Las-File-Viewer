#include <QFile>
#include <QDebug>
#include "file.h"

File::File(QString path)
{
    _pathFile = path;
    readFile();

}

HeaderFile* File::headerFile()
{
    return _headerFile;
}

VariableLengthRecordsFile* File::variableLengthRecordsFile()
{
    return _variableLengthRecordsFile;
}

QList<PointDataRecords*> File::points()
{
    return _points;
}

void File::cutPoints(QPoint beginPoint, QPoint endPoint)
{
    QList<PointDataRecords*> newPoints;
    int minX, minY, minZ, maxX, maxY, maxZ;
    minX = _points[0]->x();
    minY = _points[0]->y();
    minZ = _points[0]->z();
    maxX = _points[0]->x();
    maxY = _points[0]->y();
    maxZ = _points[0]->z();

    for (PointDataRecords* p : qAsConst(_points))
    {
        bool var_1 = (p->x() > beginPoint.x()  && p->x() < endPoint.x() && p->y() > beginPoint.y() && p->y() < endPoint.y());
        bool var_2 = (p->x() < beginPoint.x()  && p->x() > endPoint.x() && p->y() > beginPoint.y() && p->y() < endPoint.y());
        bool var_3 = (p->x() < beginPoint.x()  && p->x() > endPoint.x() && p->y() < beginPoint.y() && p->y() > endPoint.y());
        bool var_4 = (p->x() > beginPoint.x()  && p->x() < endPoint.x() && p->y() < beginPoint.y() && p->y() > endPoint.y());
        qDebug()<<p->x() << p->y()<<beginPoint<<endPoint;
        if (var_1 || var_2 || var_3 || var_4)
        {
            newPoints.append(p);

            maxX = maxX < p->x() ? p->x() : maxX;
            maxY = maxY < p->y() ? p->y() : maxY;
            maxZ = maxZ < p->z() ? p->z() : maxZ;
            minX = minX > p->x() ? p->x() : minX;
            minY = minY > p->y() ? p->y() : minY;
            minZ = minZ > p->z() ? p->z() : minZ;
        }
    }

//    HeaderFile* newHeaderFile = _headerFile;


    qDebug()<<newPoints.size();
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
//    int count = 20000;

    for (int i = 0; i < count; i++)
    {
        PointDataRecords* point = new PointDataRecords(bytes.mid(i * 26, 26));
        result.append(point);
    }

    return result;
}


