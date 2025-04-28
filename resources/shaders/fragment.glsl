#version 330 core

in vec2 texCoords;
out vec4 fragColor;

uniform sampler2D textureAtlas;

void main() {
    vec4 texColor = texture(textureAtlas, texCoords);

    if (texColor.a < 0.1) {
        discard;
    }

    fragColor = texColor;
}
