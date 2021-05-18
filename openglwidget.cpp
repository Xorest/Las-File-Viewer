#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QPainter>
#include <QMouseEvent>
#include <QCursor>
#include <QtMath>
#include <QColor>
#include <QPalette>
#include "openglwidget.h"


OpenGLWidget::OpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent),
      _zoom(-3000),
      _isContrePress(false),
      _kMoveX(0),
      _kMoveY(0),
      _isDeletePoints(false)
{
}

OpenGLWidget::~OpenGLWidget()
{

}

QList<PointDataRecords*> OpenGLWidget::points()
{
    if (!_points.isEmpty())
    {
        return _points;
    }

    return QList<PointDataRecords*>();
}

void OpenGLWidget::setPointsByOpenGL(QList<PointDataRecords*> points)
{
    _maxPoint.clear();
    _minPoint.clear();
    _points = points;

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
    }

    _maxPoint.append(maxX);
    _maxPoint.append(maxY);
    _maxPoint.append(maxZ);
    _minPoint.append(minX);
    _minPoint.append(minY);
    _minPoint.append(minZ);

    initVBO();
    update();
}

QPoint OpenGLWidget::cutPosBegin()
{
    return _cutPosBegin;
}

QPoint OpenGLWidget::cutPosEnd()
{
    return _cutPosEnd;
}

void OpenGLWidget::deletePoints()
{
    _isDeletePoints = !_isDeletePoints;

    if (_isDeletePoints)
    {
        QCursor cursorTarget = QCursor(QPixmap(":/mouse/icon/coursore_1.png"));
        this->setCursor(cursorTarget);
    }
    else
    {
        this->setCursor(Qt::ArrowCursor);
    }
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    initCamera(QVector3D(0,0,0));

    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);
    initShader();
}

void OpenGLWidget::paintGL()
{
    QPainter painter(this);
    painter.setClipRect(contentsRect(), Qt::IntersectClip);
    QColor bg = palette().color(QPalette::Window);

    glClearColor(bg.redF(), bg.greenF(), bg.blueF(), bg.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (!_points.isEmpty())
    {
        QMatrix4x4 m = _camera->viewMatrix();
        m.frustum(-_zoom,_zoom, -_zoom, _zoom, 25, 10000000);
        m.translate(-(_minPoint[0] + ((_maxPoint[0] - _minPoint[0])/2)),- (_minPoint[1] + ((_maxPoint[1] - _minPoint[1])/2)),-50);
//        m.rotate(5, 1,0,0);
        _shaderProgramm->bind();
        _shaderProgramm->setUniformValue("matrix", m);

        drawVbo();

        if(_isContrePress)
        {
            drawLineLoop(&_vboLineLoop, _shaderProgramm);
        }
    }
}

void OpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    _pressed = true;
    _lastPos = event->pos();

    if (event->modifiers().testFlag(Qt::ControlModifier) && (event->buttons() == Qt::LeftButton))
    {
        _lastPosF = currentOpenGLPosition(event->pos());
    }
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent *)
{
    _pressed = false;
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!_pressed)
        return;
    if (!_isDeletePoints)
    {
        if (!event->modifiers().testFlag(Qt::ControlModifier))
        {
            int dx = event->pos().x() - _lastPos.x();
            int dy = event->pos().y() - _lastPos.y();

            if (dy)
                _camera->pitch(dy / 10.0f);

            if (dx)
                _camera->yaw(dx / 10.0f);

            _lastPos = event->pos();
        }
        else if (event->modifiers().testFlag(Qt::ControlModifier) && (event->buttons() == Qt::LeftButton))
        {
            QPointF point = currentOpenGLPosition(event->pos());
            createVboLineLoop(&_vboLineLoop, _lastPosF, point);
            _cutPosBegin = _lastPosF.toPoint();
            _cutPosEnd = point.toPoint();
        }
    }
    else
    {
        QPointF point = currentOpenGLPosition(event->pos());

        for (PointDataRecords* p : _points)
        {

            int radius = -_zoom / 25;
            bool condition = !((qPow(((p->x()) - point.x()), 2) + qPow(((p->y()) - point.y()), 2) > qPow(radius ,2)));

            if (condition)
            {
                _points.removeOne(p);
            }
        }

        initVBO();
    }

    update();
}

void OpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    const float amount = event->modifiers().testFlag(Qt::ShiftModifier) ? 1.0f : 0.1f;
    switch (event->key()) {
    case Qt::Key_W:
        _camera->walk(-amount);
        _kMoveY -= amount;
        break;
    case Qt::Key_S:
        _camera->walk(amount);
        _kMoveY += amount;
        break;
    case Qt::Key_A:
        _camera->strafe(-amount);
        _kMoveX += amount;
        break;
    case Qt::Key_D:
        _camera->strafe(amount);
        _kMoveX -= amount;
        break;
    default:
        break;
    }

    _isContrePress = event->key() == Qt::Key_Control;

    update();
}

void OpenGLWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (_isContrePress)
    {
        if (event->key() == Qt::Key_Control)
        {
            _isContrePress = false;
            createVboLineLoop(&_vboLineLoop,0,0,0,0);
        }
    }

    update();
}

void OpenGLWidget::wheelEvent(QWheelEvent *event)
{
    event->angleDelta().y() < 0 ? _zoom-=250 : _zoom+=250;
    update();
}


void OpenGLWidget::initCamera(QVector3D position)
{
    _camera = new Camera(position);
}

void OpenGLWidget::initShader()
{

    QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    static const char* vertexShaderSource =
        "attribute highp vec3 position;\n"
        "attribute mediump vec3 color;\n"
        "uniform mediump mat4 matrix;\n"
        "varying mediump vec3 outColor;\n"
        "void main() {\n"
        "   gl_Position = matrix *vec4(position, 1.0);\n"
        "   gl_PointSize = 1;\n"
        "   outColor = color;\n"
        "}\n";
    vshader->compileSourceCode(vertexShaderSource);

    QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    static const char* fragmentShaderSource =
        "varying mediump vec3 outColor;\n"
        "void main() {\n"
        "   gl_FragColor = vec4(outColor, 1.0);\n"
        "}\n";
    fshader->compileSourceCode(fragmentShaderSource);

    _shaderProgramm = new QOpenGLShaderProgram;
    _shaderProgramm->addShader(vshader);
    _shaderProgramm->addShader(fshader);
    _shaderProgramm->bindAttributeLocation("position", 0);
    _shaderProgramm->bindAttributeLocation("color", 1);
    _shaderProgramm->link();
}

void OpenGLWidget::initVBO()
{
    QVector<GLfloat> vertData;

    for (PointDataRecords* p : _points)
    {
        vertData.append(p->x());
        vertData.append(p->y());
        vertData.append(0);
        vertData.append((p->red() / 655.35) * 0.01);
        vertData.append((p->green()/ 655.35) * 0.01);
        vertData.append((p->blue()/ 655.35) * 0.01);
    }

    _vbo.create();
    _vbo.bind();
    _vbo.allocate(vertData.constData(), vertData.count() * sizeof(GLfloat));
}

void OpenGLWidget::createVboLineLoop(QOpenGLBuffer* buffer, float x, float y, float w, float h)
{
    float z = 0;
    float vert[] ={x,y,z, x+w,y,z, x+w,y,z, x+w,y+h,z, x+w,y+h,z, x,y+h,z};
    float color[] = {0.5,0.5,0};

    QVector<GLfloat> vertData;
    int count = 6;
    int p = 0;

    for (int i = 0; i < count; i++)
    {
        vertData.append(vert[p++]);
        vertData.append(vert[p++]);
        vertData.append(vert[p++]);
        vertData.append(color[0]);
        vertData.append(color[1]);
        vertData.append(color[2]);
    }
    buffer->create();
    buffer->bind();
    buffer->allocate(vertData.constData(), vertData.count() * sizeof(GLfloat));
}

void OpenGLWidget::createVboLineLoop(QOpenGLBuffer* buffer, QPointF point1, QPointF point2)
{
    float x = point1.x();
    float y = point1.y() ;
    float w = (point2.x() - point1.x());
    float h = (point2.y() - point1.y());
    float z = 0;
    float vert[] =
    {
        x,y,z, x+w,y,z, x+w,y,z, x+w,y+h,z, x+w,y+h,z, x,y+h,z
    };
    float color[] = {0.5,0,0};

    QVector<GLfloat> vertData;
    int count = 6;
    int p = 0;

    for (int i = 0; i < count; i++)
    {
        vertData.append(vert[p++]);
        vertData.append(vert[p++]);
        vertData.append(vert[p++]);
        vertData.append(color[0]);
        vertData.append(color[1]);
        vertData.append(color[2]);
    }

    buffer->create();
    buffer->bind();
    buffer->allocate(vertData.constData(), vertData.count() * sizeof(GLfloat));
}

void OpenGLWidget::drawLineLoop(QOpenGLBuffer* buffer, QOpenGLShaderProgram* programm)
{
    buffer->bind();
    programm->enableAttributeArray(0);
    programm->enableAttributeArray(1);
        programm->setAttributeBuffer(0, GL_FLOAT, 0, 3, 6 * sizeof(GLfloat));
        programm->setAttributeBuffer(1, GL_FLOAT, 3 * sizeof(GLfloat), 3, 6 * sizeof(GLfloat));
        glDrawArrays(GL_LINE_LOOP, 0, 6);
    programm->disableAttributeArray(0);
    programm->disableAttributeArray(1);
}

void OpenGLWidget::drawVbo()
{
    _vbo.bind();
    _shaderProgramm->enableAttributeArray(0);
    _shaderProgramm->enableAttributeArray(1);
        _shaderProgramm->setAttributeBuffer(0, GL_FLOAT, 0, 3, 6 * sizeof(GLfloat));
        _shaderProgramm->setAttributeBuffer(1, GL_FLOAT, 3 * sizeof(GLfloat), 3, 6 * sizeof(GLfloat));
        glDrawArrays(GL_POINTS, 0, _points.size());
    _shaderProgramm->disableAttributeArray(0);
    _shaderProgramm->disableAttributeArray(1);
}

QPointF OpenGLWidget::currentOpenGLPosition(QPoint mousePosition)
{
    QPointF point;
    point.setX(((4.0 * _zoom) * mousePosition.x() / width() -
                (2.0 * _zoom)) + (_minPoint[0] +
               ((_maxPoint[0] - _minPoint[0])/2)) +
                (_kMoveX * -_zoom * 2));
    point.setY(((2.0 * _zoom) - (4.0 * _zoom) *
                mousePosition.y() / height()) +
               (_minPoint[1] + ((_maxPoint[1] - _minPoint[1])/2)) +
            (_kMoveY * -_zoom * 2));

    return point;
}
