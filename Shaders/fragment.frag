#version 330 core

in vec2 Tex_coord;

out vec4 outColor;

// This texture contains the data calculated by Raymarcher.cpp
uniform sampler2D tex;

// This shader does not perform anything besides taking
// the data calculated by Raymarcher.cpp and displaying it to the screen
void main() {
    outColor = texture(tex, Tex_coord);
}
