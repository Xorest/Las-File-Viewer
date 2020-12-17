//#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QtGui/QMatrix4x4>
#include <QtGui/QScreen>
#include <QPainter>
#include <QtGui/QOpenGLFunctions>
#include "openglwidget.h"


OpenGLWidget::OpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent),
      _isInitialized(false)
{

}

OpenGLWidget::~OpenGLWidget()
{
//    delete _context;
//    delete _shaderProgramm;
//    delete _paintDevice;
}

void OpenGLWidget::setPointsByOpenGL(QList<PointDataRecords*> points)
{
    _pointsPosion.resize(points.size());
    _pointsColor.resize(points.size());

    int maxX = points[0]->x();
    int maxY = points[0]->y();
    int maxZ = points[0]->z();
    int minX = points[0]->x();
    int minY = points[0]->y();
    int minZ = points[0]->z();

    for (int i = 0; i < points.size(); i++)
    {
        maxX = maxX < points[i]->x() ? points[i]->x() : maxX;
        maxY = maxY < points[i]->y() ? points[i]->y() : maxY;
        maxZ = maxZ < points[i]->z() ? points[i]->z() : maxZ;
        minX = minX > points[i]->x() ? points[i]->x() : minX;
        minY = minY > points[i]->y() ? points[i]->y() : minY;
        minZ = minZ > points[i]->z() ? points[i]->z() : minZ;


        _pointsPosion[i].setX(points[i]->x());
        _pointsPosion[i].setY(points[i]->y());
        _pointsPosion[i].setZ(points[i]->z());
        _pointsColor[i].setX(points[i]->red());
        _pointsColor[i].setX(points[i]->green());
        _pointsColor[i].setX(points[i]->blue());
    }

    qDebug()<<"max"<<maxX<<maxY<<maxZ;
    qDebug()<<"main"<<minX<<minY<<minZ;

    for(QVector3D& v : _pointsPosion)
    {
        v.setX((v.x() - (minX + (maxX - minX) / 2)));
        v.setY((v.y() - (minY + (maxY - minY) / 2)));
        v.setZ((v.z() - (minZ + (maxZ - minZ) / 2)));
    }

    qDebug()<<_pointsPosion[0].x()<<_pointsPosion[0].y(),_pointsPosion[0].z();

    _maxPoint.append(maxX);
    _maxPoint.append(maxY);
    _maxPoint.append(maxZ);
    _minPoint.append(minX);
    _minPoint.append(minY);
    _minPoint.append(minZ);

}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    static const char* vertexShaderSource =
        "in vec3 position;\n"
        "uniform mat4 matrix;\n"
        "uniform float size;\n"
        "void main() {\n"
        "   gl_Position = matrix * vec4(position[0], position[1], position[2], 1.0);\n"
        "   gl_PointSize = size;\n"
        "}\n";

    static const char* fragmentShaderSource =
        "uniform vec4 color;\n"
        "void main() {\n"
        "   gl_FragColor = color;\n"
        "}\n";

    _shaderProgramm = new QOpenGLShaderProgram(this);
    _shaderProgramm->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    _shaderProgramm->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    _shaderProgramm->link();

    _position = _shaderProgramm->attributeLocation("position");
    _matrixUniform = _shaderProgramm->uniformLocation("matrix");
    _size = _shaderProgramm->uniformLocation("size");
    _color = _shaderProgramm->uniformLocation("color");

    _isInitialized = true;
}

void OpenGLWidget::paintGL()
{
    if (_isInitialized && updatesEnabled())
    {
        QPainter painter(this);

        painter.setClipRect(contentsRect(), Qt::IntersectClip);
        QColor bg = palette().color(QPalette::Background);
        QOpenGLFunctions* gl = QOpenGLContext::currentContext()->functions();

        painter.beginNativePainting();
        gl->glClearColor(bg.redF(), bg.greenF(), bg.blueF(), bg.alphaF());
        gl->glClear(GL_COLOR_BUFFER_BIT);
        gl->glEnable(GL_PROGRAM_POINT_SIZE);
        gl->glEnable(GL_POINT_SPRITE);

        glViewport(0, 0, width(), height());

        int count = _pointsPosion.size();

        QOpenGLBuffer buffer;
        buffer.create();
        buffer.bind();
        buffer.setUsagePattern(QOpenGLBuffer::StreamDraw);
        buffer.allocate(3 * sizeof (float) * count);
        float* ptr = (float*) buffer.map(QOpenGLBuffer::WriteOnly);

        // point
        for (const QVector3D& v : _pointsPosion)
        {
            *ptr++ = v.x();
            *ptr++ = v.y();
            *ptr++ = v.z();
        }

        buffer.unmap();

        QMatrix4x4 matrix;
        matrix.perspective(5.0f, 4.0f / 3.0f, 0.1f, 10000000.0f);
        matrix.translate( 0, 0, -100000);

        _shaderProgramm->bind();
        _shaderProgramm->enableAttributeArray(_position);
        _shaderProgramm->setAttributeBuffer(_position, GL_FLOAT, 0, 3);
        _shaderProgramm->setUniformValue(_matrixUniform, matrix);
        _shaderProgramm->setUniformValue(_size, 1.0f);
        _shaderProgramm->setUniformValue(_color, QColor(Qt::red));

        gl->glDisable(GL_MULTISAMPLE);
        gl->glDrawArrays(GL_POINTS, 0, count);
        gl->glEnable(GL_MULTISAMPLE);

        _shaderProgramm->release();

        buffer.release();
        buffer.destroy();

        painter.endNativePainting();
    }
}
