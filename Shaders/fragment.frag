#version 330 core

in vec2 Tex_coord;

out vec4 outColor;

uniform sampler2D tex;

void main() {
    outColor = texture(tex, Tex_coord);
}
