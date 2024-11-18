#include "shader.h"
#include "spriterenderer.h"

Shader::Shader() {}

void Shader::compile()
{
    if (!shader.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/vertexShader.vert"))
        return;
    if (!shader.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/fragShader.frag"))
        return;
    if (!shader.link())
        return;
}
