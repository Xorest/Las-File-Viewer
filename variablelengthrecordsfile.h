#ifndef VARIABLELENGTHRECORDSFILE_H
#define VARIABLELENGTHRECORDSFILE_H

#include <QByteArray>
#include <QString>

class VariableLengthRecordsFile
{
    public:
        VariableLengthRecordsFile(const QByteArray& bytes);
        ushort reserved();
        QString userId();
        ushort recordId();
        ushort recordLengthAfterHeader();
        QString description();
        QByteArray variableLengthRecordsFileByteArray();
    private:
        ushort _reserved;
        QString _userId;
        ushort _recordId;
        ushort _recordLengthAfterHeader;
        QString _description;
};

#endif // VARIABLELENGTHRECORDSFILE_H
