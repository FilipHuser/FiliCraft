#version 330
layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 normal;

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

uniform vec3 objColor;

out vec3 ex_normal;
out vec3 ex_objColor;

void main() {
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);
    ex_normal = mat3(transpose(inverse(modelMatrix))) * normal;
    ex_objColor = objColor;
}

