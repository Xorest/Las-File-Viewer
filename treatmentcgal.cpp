#include "treatmentcgal.h"
#include <CGAL/remove_outliers.h>
#include <CGAL/compute_average_spacing.h>
#include <CGAL/grid_simplify_point_set.h>
#include <CGAL/jet_smooth_point_set.h>
#include <CGAL/random_simplify_point_set.h>
#include <CGAL/hierarchy_simplify_point_set.h>
#include <QDebug>

typedef CGAL::Parallel_if_available_tag Concurrency_tag;

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

QList<PointDataRecords *> TreatmentCGAL::convertVectorToListPointsDataRecords(const QVector<PointCGAL> &PointsCGAL,  const QHash<long, QHash<long, QHash<long, PointDataRecords*>>> &pointsQHash)
{
    QList<PointDataRecords*> result;

    for (auto& p: PointsCGAL)
    {
        PointDataRecords* myPoint = pointsQHash[p.x()][p.y()][p.z()];
        result.append(myPoint);
    }

    return result;
}

std::vector<PointCGAL> TreatmentCGAL::getStdVectorPointCGAL(const QList<PointDataRecords *> &points, QHash<long, QHash<long, QHash<long, PointDataRecords *> > > &pointsQHash)
{
    std::vector<PointCGAL> result;
    QVector<PointCGAL> vectorResultCGAL;
    pointsQHash = getQHashXYZ(points, vectorResultCGAL);

    return std::vector<PointCGAL>(vectorResultCGAL.begin(), vectorResultCGAL.end());
}

QVector<PointCGAL> TreatmentCGAL::stdIterratorToQVector(std::vector<PointCGAL> &points, std::vector<PointCGAL>::iterator iterator)
{
    points.erase(iterator, points.end());

    return QVector<PointCGAL>(points.begin(), points.end());
}


QList<PointDataRecords*> TreatmentCGAL::removeOutliers(const QList<PointDataRecords*> &points ,int k)
{
    try
    {
        QHash<long, QHash<long, QHash<long, PointDataRecords*>>> pointsQHashXYZ;
        std::vector<PointCGAL> pointStdVector = getStdVectorPointCGAL(points, pointsQHashXYZ);
        std::vector<PointCGAL>::iterator outIter = CGAL::remove_outliers<CGAL::Sequential_tag>(pointStdVector, k);

        return convertVectorToListPointsDataRecords(stdIterratorToQVector(pointStdVector, outIter), pointsQHashXYZ);
    }
    catch(...)
    {
        return points;
    }
}

QList<PointDataRecords *> TreatmentCGAL::gridSimplify(const QList<PointDataRecords *> &points, int k)
{
    try
    {
        QHash<long, QHash<long, QHash<long, PointDataRecords*>>> pointsQHashXYZ;
        std::vector<PointCGAL> pointStdVector = getStdVectorPointCGAL(points, pointsQHashXYZ);
        double spacing = CGAL::compute_average_spacing<CGAL::Sequential_tag> (pointStdVector, k);
        std::vector<PointCGAL>::iterator outIter = CGAL::grid_simplify_point_set (pointStdVector, 2.0 * spacing);

        return convertVectorToListPointsDataRecords(stdIterratorToQVector(pointStdVector, outIter), pointsQHashXYZ);
    }
    catch(...)
    {
        return points;
    }
}

QList<PointDataRecords *> TreatmentCGAL::randomSimplify(const QList<PointDataRecords *> &points, int k)
{
    try
    {
        QHash<long, QHash<long, QHash<long, PointDataRecords*>>> pointsQHashXYZ;
        std::vector<PointCGAL> pointStdVector = getStdVectorPointCGAL(points, pointsQHashXYZ);
        double spacing = CGAL::compute_average_spacing<CGAL::Sequential_tag> (pointStdVector, k);
        std::vector<PointCGAL>::iterator outIter = CGAL::random_simplify_point_set (pointStdVector, 2.0 * spacing);

        return convertVectorToListPointsDataRecords(stdIterratorToQVector(pointStdVector, outIter), pointsQHashXYZ);
    }
    catch(...)
    {
        return points;
    }
}

QList<PointDataRecords *> TreatmentCGAL::hierarchySimplify(const QList<PointDataRecords *> &points, int k)
{
    try
    {
        QHash<long, QHash<long, QHash<long, PointDataRecords*>>> pointsQHashXYZ;
        std::vector<PointCGAL> pointStdVector = getStdVectorPointCGAL(points, pointsQHashXYZ);
        std::vector<PointCGAL>::iterator outIter = CGAL::hierarchy_simplify_point_set(pointStdVector, CGAL::parameters::size(k).maximum_variation(0.01));

        return convertVectorToListPointsDataRecords(stdIterratorToQVector(pointStdVector, outIter), pointsQHashXYZ);
    }
    catch(...)
    {
        return points;
    }
}

QList<PointDataRecords *> TreatmentCGAL::jetSmooth(const QList<PointDataRecords *> &points, int k)
{
    try
    {
        QList<PointDataRecords*> result = points;

        QHash<long, QHash<long, QHash<long, PointDataRecords*>>> pointsQHashXYZ;
        std::vector<PointCGAL> pointStdVector = getStdVectorPointCGAL(points, pointsQHashXYZ);
        CGAL::jet_smooth_point_set<Concurrency_tag>(pointStdVector, k);
        QVector<PointCGAL> vector(pointStdVector.begin(), pointStdVector.end());

        for (int i = 0; i < vector.size(); i++)
        {
            result[i]->setX((long)vector[i].x());
            result[i]->setY((long)vector[i].y());
            result[i]->setZ((long)vector[i].z());
        }

        return result;
    }
    catch(...)
    {
        return points;
    }
}
