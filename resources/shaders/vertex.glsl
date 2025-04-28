/*#version 330 core

layout (location = 0) in vec3 posA;
layout (location = 1) in vec2 texA;
layout (location = 2) in vec3 offsetA;

out vec2 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    texCoords = texA;

    vec3 worldPos = posA + offsetA;
    gl_Position = projection * view * model * vec4(worldPos, 1.0);
}*/

#version 330 core

layout (location = 0) in vec3 posA;
layout (location = 1) in vec3 offsetA;
layout (location = 2) in vec2 uvBack;
layout (location = 3) in vec2 uvFront;
layout (location = 4) in vec2 uvLeft;
layout (location = 5) in vec2 uvRight;
layout (location = 6) in vec2 uvTop;
layout (location = 7) in vec2 uvBottom;

out vec2 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    // Determine face based on vertex index
    int vertexIndex = gl_VertexID / 6;

    vec2 uv;

    // This assumes you draw in the face order you created in cubeVertices.
    if (vertexIndex == 0) uv = uvBack;
    else if (vertexIndex == 1) uv = uvFront;
    else if (vertexIndex == 2) uv = uvLeft;
    else if (vertexIndex == 3) uv = uvRight;
    else if (vertexIndex == 4) uv = uvTop;
    else uv = uvBottom;

    // Offset manually in shader (assuming 1/32 scale atlas tile)
    float atlasTileSize = 1.0 / 16.0;
    vec2 localUVs[] = vec2[](
        vec2(0.0, 0.0), vec2(1.0, 0.0), vec2(1.0, 1.0),
        vec2(1.0, 1.0), vec2(0.0, 1.0), vec2(0.0, 0.0)
    );
    texCoords = uv + localUVs[gl_VertexID % 6] * atlasTileSize;

    gl_Position = projection * view * model * vec4(posA + offsetA, 1.0);
}

