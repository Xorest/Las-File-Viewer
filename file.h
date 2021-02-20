#ifndef FILE_H
#define FILE_H

#include <QString>
#include <QList>
#include <QPoint>
#include "headerfile.h"
#include "variablelengthrecordsfile.h"
#include "pointdatarecords.h"

class File
{
    public:
        File(QString path);
        HeaderFile* headerFile();
        VariableLengthRecordsFile* variableLengthRecordsFile();
        QList<PointDataRecords*> points();
        void cutPoints(QPoint beginPoint, QPoint endPoint);
    private:
        QString _pathFile;
        HeaderFile* _headerFile;
        VariableLengthRecordsFile* _variableLengthRecordsFile;
        QList<PointDataRecords*> _points;
        void readFile();
        QList<PointDataRecords*> getPoints(const QByteArray& bytes);

};

#endif // FILE_H
