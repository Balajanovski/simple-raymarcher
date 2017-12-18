#version 330 core

in vec2 position;
in vec2 tex_coord;

out vec2 Tex_coord;

void main() {
    gl_Position = vec4(position, 0.0, 1.0);
    Tex_coord = tex_coord;
}