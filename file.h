#ifndef FILE_H
#define FILE_H

#include <QString>
#include "headerfile.h"
#include "variablelengthrecordsfile.h"

class File
{
    public:
        File(QString path);
        HeaderFile* headerFile();
        VariableLengthRecordsFile* variableLengthRecordsFile();
    private:
        QString _pathFile;
        HeaderFile* _headerFile;
        VariableLengthRecordsFile* _variableLengthRecordsFile;
        void readHeader();

};

#endif // FILE_H
