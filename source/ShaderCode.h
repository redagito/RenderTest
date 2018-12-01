#pragma once

const char* vertexCode = R"##(
#version 460 core

layout(location = 0) in vec3 vertexPosition_modelspace;

void main(){
  gl_Position.xyz = vertexPosition_modelspace;
  gl_Position.w = 1.0;
}
)##";

const char* fragmentCode = R"##(
#version 460 core

out vec3 color;

void main(){
  color = vec3(1,0,0);
}
)##";