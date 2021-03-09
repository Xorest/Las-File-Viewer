#include <QFile>
#include <QFileDialog>
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
    QByteArray pointsData;

    int minX, minY, minZ, maxX, maxY, maxZ;
    minX = _points[0]->x();
    minY = _points[0]->y();
    minZ = _points[0]->z();
    maxX = _points[0]->x();
    maxY = _points[0]->y();
    maxZ = _points[0]->z();

    for (PointDataRecords* p : qAsConst(_points))
    {
        bool condition1 = (p->x() > beginPoint.x()  && p->x() < endPoint.x() && p->y() > beginPoint.y() && p->y() < endPoint.y());
        bool condition2 = (p->x() < beginPoint.x()  && p->x() > endPoint.x() && p->y() > beginPoint.y() && p->y() < endPoint.y());
        bool condition3 = (p->x() < beginPoint.x()  && p->x() > endPoint.x() && p->y() < beginPoint.y() && p->y() > endPoint.y());
        bool condition4 = (p->x() > beginPoint.x()  && p->x() < endPoint.x() && p->y() < beginPoint.y() && p->y() > endPoint.y());

        if (condition1 || condition2 || condition3 || condition4)
        {
            pointsData.append(p->pointByteArray());
            maxX = maxX < p->x() ? p->x() : maxX;
            maxY = maxY < p->y() ? p->y() : maxY;
            maxZ = maxZ < p->z() ? p->z() : maxZ;
            minX = minX > p->x() ? p->x() : minX;
            minY = minY > p->y() ? p->y() : minY;
            minZ = minZ > p->z() ? p->z() : minZ;
        }
    }

    HeaderFile* newHeaderFile = _headerFile;
    VariableLengthRecordsFile* newVariableLengthRecordsFile = _variableLengthRecordsFile;
    QByteArray nullBytes;
    newHeaderFile->setMaxX(maxX);
    newHeaderFile->setMaxX(maxY);
    newHeaderFile->setMaxX(maxZ);
    newHeaderFile->setMinX(minX);
    newHeaderFile->setMinX(minY);
    newHeaderFile->setMinX(minZ);

    if (newHeaderFile->headerByteArray().size() + newVariableLengthRecordsFile->variableLengthRecordsFileByteArray().size() < (int)_headerFile->offsetToPointData())
    {
        int  count =  (int)_headerFile->offsetToPointData() - (newHeaderFile->headerByteArray().size() + newVariableLengthRecordsFile->variableLengthRecordsFileByteArray().size());

        for (int i = 0; i < count; i++)
        {
            nullBytes.append('\x00');
        }
    }
//    newHeaderFile->setOffsetToPointData(newHeaderFile->headerByteArray().size() + newVariableLengthRecordsFile->variableLengthRecordsFileByteArray().size());
//    for (PointDataRecords* p : qAsConst(newPoints))
//    {
//        pointsData.append(p->pointByteArray());
//    }

    QFile newFile("newFile.las");
    newFile.open(QIODevice::WriteOnly);
    newFile.write(newHeaderFile->headerByteArray());
    newFile.write(newVariableLengthRecordsFile->variableLengthRecordsFileByteArray());
    newFile.write(nullBytes);
    newFile.write(pointsData);
}

void File::cutPoints()
{
    int countPointsInFile = 30000000;
    int count = (_points.size() / countPointsInFile) + 1;
    int lastPoint = 0;



    for (int i = 0; i < count; i++)
    {
        int minX, minY, minZ, maxX, maxY, maxZ;
        minX = _points[lastPoint]->x();
        minY = _points[lastPoint]->y();
        minZ = _points[lastPoint]->z();
        maxX = _points[lastPoint]->x();
        maxY = _points[lastPoint]->y();
        maxZ = _points[lastPoint]->z();

        QByteArray pointsData;

        for(int j = 0; j < countPointsInFile; j++)
        {
            maxX = maxX < _points[lastPoint]->x() ? _points[lastPoint]->x() : maxX;
            maxY = maxY < _points[lastPoint]->y() ? _points[lastPoint]->y() : maxY;
            maxZ = maxZ < _points[lastPoint]->z() ? _points[lastPoint]->z() : maxZ;
            minX = minX > _points[lastPoint]->x() ? _points[lastPoint]->x() : minX;
            minY = minY > _points[lastPoint]->y() ? _points[lastPoint]->y() : minY;
            minZ = minZ > _points[lastPoint]->z() ? _points[lastPoint]->z() : minZ;

            pointsData.append(_points[lastPoint++]->pointByteArray());
            if (_points.size() == lastPoint)
            {
                break;
            }
        }

        HeaderFile* newHeaderFile = _headerFile;
        VariableLengthRecordsFile* newVariableLengthRecordsFile = _variableLengthRecordsFile;
        QByteArray nullBytes;
        newHeaderFile->setMaxX(maxX);
        newHeaderFile->setMaxX(maxY);
        newHeaderFile->setMaxX(maxZ);
        newHeaderFile->setMinX(minX);
        newHeaderFile->setMinX(minY);
        newHeaderFile->setMinX(minZ);

        if (newHeaderFile->headerByteArray().size() + newVariableLengthRecordsFile->variableLengthRecordsFileByteArray().size() < (int)_headerFile->offsetToPointData())
        {
            int  count =  (int)_headerFile->offsetToPointData() - (newHeaderFile->headerByteArray().size() + newVariableLengthRecordsFile->variableLengthRecordsFileByteArray().size());
            for (int i = 0; i < count; i++)
            {
                nullBytes.append('\x00');
            }
        }

        QFile newFile(QString("New LAS File %1").arg(i + 1));
        newFile.open(QIODevice::WriteOnly);
        newFile.write(newHeaderFile->headerByteArray());
        newFile.write(newVariableLengthRecordsFile->variableLengthRecordsFileByteArray());
        newFile.write(nullBytes);
        newFile.write(pointsData);
    }
}

void File::save(QList<PointDataRecords *> points)
{
    QByteArray pointsData;

    int minX, minY, minZ, maxX, maxY, maxZ;
    minX = _points[0]->x();
    minY = _points[0]->y();
    minZ = _points[0]->z();
    maxX = _points[0]->x();
    maxY = _points[0]->y();
    maxZ = _points[0]->z();


    for (PointDataRecords* p : qAsConst(points))
    {
        pointsData.append(p->pointByteArray());
        maxX = maxX < p->x() ? p->x() : maxX;
        maxY = maxY < p->y() ? p->y() : maxY;
        maxZ = maxZ < p->z() ? p->z() : maxZ;
        minX = minX > p->x() ? p->x() : minX;
        minY = minY > p->y() ? p->y() : minY;
        minZ = minZ > p->z() ? p->z() : minZ;
    }

    HeaderFile* newHeaderFile = _headerFile;
    VariableLengthRecordsFile* newVariableLengthRecordsFile = _variableLengthRecordsFile;
    QByteArray nullBytes;
    newHeaderFile->setMaxX(maxX);
    newHeaderFile->setMaxX(maxY);
    newHeaderFile->setMaxX(maxZ);
    newHeaderFile->setMinX(minX);
    newHeaderFile->setMinX(minY);
    newHeaderFile->setMinX(minZ);

    savingLasFile(newHeaderFile, newVariableLengthRecordsFile, pointsData);
}

void File::savingLasFile(HeaderFile* newHeaderFile, VariableLengthRecordsFile* newVariableLengthRecordsFile, QByteArray pointsData)
{

    QString nameNewFile = QFileDialog::getSaveFileName();
    QByteArray nullBytes;

    if (newHeaderFile->headerByteArray().size() + newVariableLengthRecordsFile->variableLengthRecordsFileByteArray().size() < (int)_headerFile->offsetToPointData())
    {
        int  count =  (int)_headerFile->offsetToPointData() - (newHeaderFile->headerByteArray().size() + newVariableLengthRecordsFile->variableLengthRecordsFileByteArray().size());

        for (int i = 0; i < count; i++)
        {
            nullBytes.append('\x00');
        }
    }

    QFile newFile(nameNewFile + ".las");
    newFile.open(QIODevice::WriteOnly);
    newFile.write(newHeaderFile->headerByteArray());
    newFile.write(newVariableLengthRecordsFile->variableLengthRecordsFileByteArray());
    newFile.write(nullBytes);
    newFile.write(pointsData);
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
    qDebug()<< count;
//    int count = 20000;

    for (int i = 0; i < count; i++)
    {
        PointDataRecords* point = new PointDataRecords(bytes.mid(i * 26, 26));
        result.append(point);
    }

    return result;
}


