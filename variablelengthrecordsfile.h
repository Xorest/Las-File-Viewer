#ifndef VARIABLELENGTHRECORDSFILE_H
#define VARIABLELENGTHRECORDSFILE_H

#include <QByteArray>
#include <QString>

class VariableLengthRecordsFile
{
    public:
        VariableLengthRecordsFile(const QByteArray& bytes);
        uint reserved();
        QString userId();
        uint recordId();
        uint recordLengthAfterHeader();
        QString description();
    private:
        uint _reserved;
        QString _userId;
        uint _recordId;
        uint _recordLengthAfterHeader;
        QString _description;
};

#endif // VARIABLELENGTHRECORDSFILE_H
