#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOffscreenSurface>
#include <QList>
#include <QVector3D>
#include <QVector>
#include <QWidget>
#include "pointdatarecords.h"
#include "camera.h"

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram);

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    public:
        OpenGLWidget(QWidget* parent);
        ~OpenGLWidget() override;
        void setPointsByOpenGL(QList<PointDataRecords*> points);
    protected:
        void initializeGL() override;
        void paintGL() override;
        void mousePressEvent(QMouseEvent* event) override;
        void mouseReleaseEvent(QMouseEvent* event) override;
        void mouseMoveEvent(QMouseEvent* event) override;
        void keyPressEvent(QKeyEvent* event) override;
        void wheelEvent(QWheelEvent *event) override;
    private:
        QList<PointDataRecords*> _points;
        QOpenGLBuffer _vbo;
        QOpenGLShaderProgram* _shaderProgramm;
        GLint _position;
        GLint _color;
        GLint _size;
        QVector<QVector3D> _pointsPosion;
        QVector<QVector3D> _pointsColor;
        QVector<int> _maxPoint;
        QVector<int> _minPoint;
        int _matrixLoc;
        Camera* _camera;
        bool _debug;
        bool _pressed = false;
        QPoint _lastPos;
        int _zoom;
        void initCamera(QVector3D position);
        void initShader();
        void initVBO();

};

#endif // OPENGLWIDGET_H
