#include "treatmentcgal.h"
#include <CGAL/remove_outliers.h>
#include <QDebug>

QHash<long, PointCGAL> TreatmentCGAL::getQHash(const QList<PointDataRecords*> &points)
{
    QHash<long, PointCGAL> result;

    for (int i = 0; i < points.size(); i++)
    {
        PointDataRecords* p = points[i];
        PointCGAL pointCGAL(p->x(), p->y(), p->z());
        result.insert(i, pointCGAL);
    }

    return result;
}

QVector<PointCGAL> TreatmentCGAL::getQVector(const QList<PointDataRecords *> &points)
{
    QVector<PointCGAL> result;

    for (auto& p : points)
    {
        PointCGAL pointCGAL(p->x(), p->y(), p->z());
        result.append(pointCGAL);
    }

    return result;
}

QHash<long, QHash<long, QHash<long, PointDataRecords*>>> TreatmentCGAL::getQHashXYZ(const QList<PointDataRecords *> &points, QVector<PointCGAL> &vectorResultCGAL)
{
    QHash<long, QHash<long, QHash<long, PointDataRecords*>>> result;
    vectorResultCGAL.clear();

    for (PointDataRecords* p : points)
    {
        result[p->x()][p->y()][p->z()] = p;
        PointCGAL pointCGAL(p->x(), p->y(), p->z());
        vectorResultCGAL.append(pointCGAL);
    }

    return result;
}

QList<PointDataRecords*> TreatmentCGAL::removeOutliers(const QList<PointDataRecords*> &points)
{
    QVector<PointCGAL> vectorResultCGAL;
    QHash<long, QHash<long, QHash<long, PointDataRecords*>>> pointsQHashXYZ = getQHashXYZ(points, vectorResultCGAL);
    std::vector<PointCGAL> pointStdVector = std::vector<PointCGAL>(vectorResultCGAL.begin(), vectorResultCGAL.end());
    std::vector<PointCGAL>::iterator outIter = CGAL::remove_outliers<CGAL::Sequential_tag>(pointStdVector, 200);
    pointStdVector.erase(outIter, pointStdVector.end());
    QVector<PointCGAL> outQVector(pointStdVector.begin(), pointStdVector.end());
    QList<PointDataRecords*> outPoints;

    for (auto& p: outQVector)
    {
        PointDataRecords* myPoint = pointsQHashXYZ[p.x()][p.y()][p.z()];
        outPoints.append(myPoint);
    }
    qDebug()<<outPoints.size();
    return outPoints;
}
