#include "HumanView.h"
#include"tiny_obj_loader.h"
#include<qdebug.h>
#include<qopenglfunctions_3_2_core.h>
#include<qfile.h>
#include<qapplication.h>

HumanView::HumanView(QWidget* parent, const char* path)
    : QOpenGLWidget(parent), QOpenGLFunctions(),
    rotX(0), rotY(0), rotZ(0), scale(1),
      tranX(0), tranY(0), tranZ(0)
{
    //resize(1200, 800);
    setFocusPolicy(Qt::StrongFocus);

    std::string inputfile(path);
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string err;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, inputfile.c_str());

    if (!err.empty()) { // `err` may contain warning message.
        qDebug() << "load obj failed" << path;
    }

    if (!ret) {
        exit(1);
    }

    // Loop over shapes
    for (size_t s = 0; s < shapes.size(); s++) {
        // Loop over faces(polygon)
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            int fv = shapes[s].mesh.num_face_vertices[f];

            //qDebug() << "fv: " << fv;
             //Loop over vertices in the face.
            for (size_t v = 0; v < fv; v++) {
                // access to vertex
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                tinyobj::real_t vx = attrib.vertices[3 * idx.vertex_index + 0];
                tinyobj::real_t vy = attrib.vertices[3 * idx.vertex_index + 1];
                tinyobj::real_t vz = attrib.vertices[3 * idx.vertex_index + 2];
                tinyobj::real_t tx = attrib.texcoords[2 * idx.texcoord_index + 0];
                tinyobj::real_t ty = attrib.texcoords[2 * idx.texcoord_index + 1];

                vertices.push_back(vx);
                vertices.push_back(vy);
                vertices.push_back(vz);
            }
            index_offset += fv;
        }
    }
    //分别求出x,y,z的最大最小值
    float min_x, max_x, min_y, max_y, min_z, max_z;
    min_x = max_x = vertices[0];
    min_y = max_y = vertices[1];
    min_z = max_z = vertices[2];

    for (int i = 0; i < vertices.size() / 3; i++) {
        float x = vertices[i * 3 + 0], y = vertices[i * 3 + 1], z = vertices[i * 3 + 2];

        if (x < min_x) {
            min_x = x;
        }
        if (x > max_x) {
            max_x = x;
        }

        if (y < min_y) {
            min_y = y;
        }
        if (y > max_y) {
            max_y = y;
        }

        if (z < min_z) {
            min_z = z;
        }
        if (z > max_z) {
            max_z = z;
        }
    }

    //将x、y、z变换到[-1, 1],并缩小
    for (int i = 0; i < vertices.size() / 3; i++) {
        vertices[i * 3 + 0] = 2.0 / (max_x - min_x) * (vertices[i * 3 + 0] - max_x) + 1.0;
        vertices[i * 3 + 1] = 2.0 / (max_y - min_y) * (vertices[i * 3 + 1] - max_y) + 1.0;
        vertices[i * 3 + 2] = 2.0 / (max_z - min_z) * (vertices[i * 3 + 2] - max_z) + 1.0;
        vertices[i * 3 + 0] = vertices[i * 3 + 0] * 0.3;
        vertices[i * 3 + 1] = vertices[i * 3 + 1] * 0.3;
        vertices[i * 3 + 2] = vertices[i * 3 + 2] * 0.3;

    }

}

void HumanView::initializeGL() {
    initializeOpenGLFunctions();

    QOpenGLFunctions_3_2_Core *f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_2_Core>();

    f->glGenVertexArrays(1, &VAO);
    f->glBindVertexArray(VAO);

    f->glGenBuffers(1, &VBO);
    f->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    f->glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    f->glEnableVertexAttribArray(0);

    f->glBindVertexArray(0);
    f->glBindBuffer(GL_ARRAY_BUFFER, 0);

    model.setToIdentity();
    view.setToIdentity();
    proj.setToIdentity();
    proj.ortho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    //vertexShader
    const char* vertexShaderPath = "C:\\Users\\lenovo-pc\\Desktop\\3DGarment\\3DGarment\\default.vs";
    const char* fragmentShaderPath = "C:\\Users\\lenovo-pc\\Desktop\\3DGarment\\3DGarment\\default.fs";
    QFile vsFile(vertexShaderPath);
    if (!vsFile.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << vsFile.errorString();
    }
    QTextStream vsIn(&vsFile);
    std::string vsString = vsIn.readAll().toStdString();
    const char *vertexShaderSource = vsString.c_str();
    vsFile.close();

    //fragmentShader
    QFile fsFile(fragmentShaderPath);
    if (!fsFile.open(QFile::ReadOnly | QFile::Text)) {

        qDebug() << fsFile.errorString();
    }
    QTextStream fsIn(&fsFile);
    std::string fsString = fsIn.readAll().toStdString();
    const char *fragmentShaderSource = fsString.c_str();
    fsFile.close();
    //compile and link shader
    int vertexShader = f->glCreateShader(GL_VERTEX_SHADER);
    f->glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    f->glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    f->glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        f->glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        qDebug() << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog;
    }

    // fragment shader
    int fragmentShader = f->glCreateShader(GL_FRAGMENT_SHADER);
    f->glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    f->glCompileShader(fragmentShader);
    // check for shader compile errors
    f->glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        f->glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        qDebug() << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog;
    }
    // link shaders
    program = f->glCreateProgram();
    f->glAttachShader(program, vertexShader);
    f->glAttachShader(program, fragmentShader);
    f->glLinkProgram(program);
    // check for linking errors
    f->glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        f->glGetProgramInfoLog(program, 512, NULL, infoLog);
        qDebug() << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog;
    }
    f->glDeleteShader(vertexShader);
    f->glDeleteShader(fragmentShader);

}

void HumanView::resizeGL(int width, int height) {

    QOpenGLFunctions_3_2_Core *f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_2_Core>();
    f->glViewport(0, 0, width, height);
    update();
}

void HumanView::paintGL() {

    QOpenGLFunctions_3_2_Core *f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_2_Core>();
    f->glClearColor(0.2, 0.2, 0.2, 1.0);
    f->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    f->glUseProgram(program);
    f->glBindVertexArray(VAO);

    transform();
    f->glUniformMatrix4fv(f->glGetUniformLocation(program, "model"), 1, GL_FALSE, model.constData());
    f->glUniformMatrix4fv(f->glGetUniformLocation(program, "view"), 1, GL_FALSE, view.constData());
    f->glUniformMatrix4fv(f->glGetUniformLocation(program, "proj"), 1, GL_FALSE, proj.constData());
    f->glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);

    f->glBindVertexArray(0);
    f->glUseProgram(0);
}

void HumanView::keyPressEvent(QKeyEvent* event) {
    switch (event->key())
    {
    case Qt::Key_F1:
        if (QApplication::keyboardModifiers() == Qt::ControlModifier)
        {
            rotX -= 10.0f;
        }
        else
        {
            rotX += 10.0f;
        }
        update();
        break;
    case Qt::Key_F2:
        if (QApplication::keyboardModifiers() == Qt::ControlModifier)
        {
            rotY -= 10.0f;
        }
        else
        {
            rotY += 10.0f;
        }
        update();
        break;
    case Qt::Key_F3:
        if (QApplication::keyboardModifiers() == Qt::ControlModifier)
        {
            rotZ -= 10.0f;
        }
        else
        {
            rotZ += 10.0f;
        }
        update();
        break;
    case Qt::Key_Up:
        tranY += 0.1f;
        if (tranY >= 1.0f)
        {
            tranY = 0.0f;
        }
        update();
        break;
    case Qt::Key_Down:
        tranY -= 0.1f;
        if (tranY <= -1.0f)
        {
            tranY = 0.0f;
        }
        update();
        break;
    case Qt::Key_Right:
        tranX += 0.1f;
        if (tranX >= 1.0f)
        {
            tranX = 0.0f;
        }
        update();
        break;
    case Qt::Key_Left:
        tranX -= 0.1f;
        if (tranX <= -1.0f)
        {
            tranX = 0.0f;
        }
        update();
        break;
    default:
        break;
    }
}

void HumanView::mouseReleaseEvent(QMouseEvent *event) {
    switch (event->button())
    {
    case Qt::RightButton:
        scale = 1.0f;
        update();
        break;
    case Qt::LeftButton:
        scale += 1.0f;
        update();
        break;
    default:
        break;
    }
}

void HumanView::transform() {

    model.setToIdentity();
    view.setToIdentity();

    model.translate(tranX, tranY, tranZ);
    model.rotate(rotZ, 0, 0, 1);
    model.rotate(rotY, 0, 1, 0);
    model.rotate(rotX, 1, 0, 0);
    //model.translate(tranX, tranY, tranZ);
    model.scale(scale, scale, scale);

}
