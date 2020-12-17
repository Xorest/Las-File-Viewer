#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLContext>
#include <QOpenGLFunctions_3_0>
#include <QOpenGLPaintDevice>
#include <QtGui/QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QList>
#include <QVector3D>
#include <QVector>
#include <QWidget>
#include "pointdatarecords.h"


class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_0
{
    public:
        OpenGLWidget(QWidget* parent);
        ~OpenGLWidget() override;
        void setPointsByOpenGL(QList<PointDataRecords*> points);
    protected:
        void initializeGL() override;
        void paintGL() override;
    private:
        bool _isInitialized;
        QVector<QVector3D> _points;
        QOpenGLContext* _context;
        QOpenGLShaderProgram* _shaderProgramm;
        QOpenGLPaintDevice* _paintDevice;
        GLint _position;
        GLint _color;
        GLint _matrixUniform;
        GLint _size;
        QVector<QVector3D> _pointsPosion;
        QVector<QVector3D> _pointsColor;
        QList<int> _maxPoint;
        QList<int> _minPoint;


};

#endif // OPENGLWIDGET_H
