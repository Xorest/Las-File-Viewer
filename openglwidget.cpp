#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QPainter>
#include <QMouseEvent>
#include "openglwidget.h"


OpenGLWidget::OpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent),
      _zoom(-50)
{}

OpenGLWidget::~OpenGLWidget()
{

}

void OpenGLWidget::setPointsByOpenGL(QList<PointDataRecords*> points)
{
    _points = points;
//    _pointsPosion.resize(points.size());
//    _pointsColor.resize(points.size());

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


//        _pointsPosion[i].setX(points[i]->x());
//        _pointsPosion[i].setY(points[i]->y());
//        _pointsPosion[i].setZ(points[i]->z());
//        _pointsColor[i].setX((points[i]->red() / 655.35) * 0.01);
//        _pointsColor[i].setY((points[i]->green() / 655.35) * 0.01);
//        _pointsColor[i].setZ((points[i]->blue() / 655.35) * 0.01);
    }

    qDebug()<<"max"<<maxX<<maxY<<maxZ;
    qDebug()<<"min"<<minX<<minY<<minZ;

//    for(QVector3D& v : _pointsPosion)
//    {
//        v.setX((v.x() - (minX + (maxX - minX) / 2)));
//        v.setY((v.y() - (minY + (maxY - minY) / 2)));
//        v.setZ((v.z() - (minZ + (maxZ - minZ) / 2)));
////        qDebug()<<v.x()<<v.y()<<v.z();
//    }

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
    initCamera(QVector3D(0,0,0));
    initVBO();
    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);
    initShader();
}

void OpenGLWidget::paintGL()
{
    QPainter painter(this);
    painter.setClipRect(contentsRect(), Qt::IntersectClip);
    QColor bg = palette().color(QPalette::Background);

    glClearColor(bg.redF(), bg.greenF(), bg.blueF(), bg.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 m = _camera->viewMatrix();
    //m.setToIdentity();

    m.scale(0.2,0.2,0.2);
    m.frustum(-5,5, -5,5, 1, 1000);
    m.translate(0,0,_zoom);


    _shaderProgramm->bind();
    _shaderProgramm->setUniformValue("matrix", m);
    _shaderProgramm->enableAttributeArray(0);
    _shaderProgramm->enableAttributeArray(1);
    _shaderProgramm->setAttributeBuffer(0, GL_FLOAT, 0, 3, 6 * sizeof(GLfloat));
    _shaderProgramm->setAttributeBuffer(1, GL_FLOAT, 3 * sizeof(GLfloat), 3, 6 * sizeof(GLfloat));

    glDrawArrays(GL_POINTS, 0, _points.size());
}

void OpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    _pressed = true;
    _lastPos = event->pos();
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent *)
{
    _pressed = false;
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!_pressed)
        return;

    int dx = event->pos().x() - _lastPos.x();
    int dy = event->pos().y() - _lastPos.y();

    if (dy)
        _camera->pitch(dy / 10.0f);

    if (dx)
        _camera->yaw(dx / 10.0f);

    _lastPos = event->pos();

    update();
}

void OpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    const float amount = event->modifiers().testFlag(Qt::ShiftModifier) ? 1.0f : 0.1f;
    switch (event->key()) {
    case Qt::Key_W:
        _camera->walk(amount);
        break;
    case Qt::Key_S:
        _camera->walk(-amount);
        break;
    case Qt::Key_A:
        _camera->strafe(-amount);
        break;
    case Qt::Key_D:
        _camera->strafe(amount);
        break;
    default:
        break;
    }

    update();
}

void OpenGLWidget::wheelEvent(QWheelEvent *event)
{
    event->angleDelta().y() < 0 ? _zoom-= 20 : _zoom+= 20;

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
        "   gl_PointSize = 3;\n"
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
    int k = 50;

    for (PointDataRecords* p : _points)
    {
        vertData.append((p->x() - (_minPoint[0] + (_maxPoint[0] - _minPoint[0]) / 2)));
        vertData.append((p->y() - (_minPoint[1] + (_maxPoint[1] - _minPoint[1]) / 2)));
        vertData.append((p->z() - (_minPoint[2] + (_maxPoint[2] - _minPoint[2]) / 2))/100);
        vertData.append((p->red() / 655.35) * 0.01);
        vertData.append((p->green()/ 655.35) * 0.01);
        vertData.append((p->blue()/ 655.35) * 0.01);

//        vertData.append(p->x());
//        vertData.append(p->y());
//        vertData.append(p->z());
//        vertData.append((p->red() / 655.35) * 0.01);
//        vertData.append((p->green()/ 655.35) * 0.01);
//        vertData.append((p->blue()/ 655.35) * 0.01);

    }
    _points.size() > 30 ? qDebug()<< _points.size():qDebug()<<vertData;

    _vbo.create();
    _vbo.bind();
    _vbo.allocate(vertData.constData(), vertData.count() * sizeof(GLfloat));
}
