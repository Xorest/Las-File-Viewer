#ifndef TREATMENTCGAL_H
#define TREATMENTCGAL_H

#include <CGAL/IO/read_xyz_points.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <QVector>
#include <QList>
#include <QHash>
#include "pointdatarecords.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::Point_3 PointCGAL;

class TreatmentCGAL
{
    public:
        static QList<PointDataRecords*> removeOutliers(const QList<PointDataRecords*> &points, int k);
        static QList<PointDataRecords*> gridSimplify(const QList<PointDataRecords*> &points, int k);
        static QList<PointDataRecords*> randomSimplify(const QList<PointDataRecords*> &points, int k);
        static QList<PointDataRecords*> hierarchySimplify(const QList<PointDataRecords*> &points, int k);
        static QList<PointDataRecords*> jetSmooth(const QList<PointDataRecords*> &points, int k);

    private:
        static QHash<long, PointCGAL> getQHash(const QList<PointDataRecords*> &points);
        static QVector<PointCGAL> getQVector(const QList<PointDataRecords*> &points);
        static QHash<long, QHash<long, QHash<long, PointDataRecords *> > > getQHashXYZ(const QList<PointDataRecords*> &points, QVector<PointCGAL> &vectorResultCGAL);
        static QList<PointDataRecords*> convertVectorToListPointsDataRecords(const QVector<PointCGAL> &PointsCGAL, const QHash<long, QHash<long, QHash<long, PointDataRecords*>>> &pointsQHash);
        static std::vector<PointCGAL> getStdVectorPointCGAL(const QList<PointDataRecords*> &points, QHash<long, QHash<long, QHash<long, PointDataRecords*>>> &pointsQHash);
        static QVector<PointCGAL> stdIterratorToQVector(std::vector<PointCGAL> &points, std::vector<PointCGAL>::iterator iterator);

};

#endif // TREATMENTCGAL_H
