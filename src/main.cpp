#include <glm/gtc/matrix_transform.hpp>

#include "Window.h"
#include "Shader.h"
#include "Texture.h"
#include "BlockRenderer.h"
#include "Block.h"
#include "Camera.h"
#include "Globals.h"
#include "GuiRenderer.h"
#include "Widget.h"

int main(int argc, char* argv[]) {
    Window window = Window(800, 600, "Minecraft");
    window.init();

    Shader shader = Shader(RESOURCES_PATH "shaders/vertex.glsl", RESOURCES_PATH "shaders/fragment.glsl");
    Shader guiShader = Shader(RESOURCES_PATH "shaders/guiVertex.glsl", RESOURCES_PATH "shaders/guiFragment.glsl");

    Camera camera = Camera({16.0f, 130.0f, 16.0f});
    Globals::camera = &camera;

    Texture blockAtlas = Texture(RESOURCES_PATH "textures/blockAtlas.png");
    Texture inventory = Texture(RESOURCES_PATH "textures/inventory.png");
    Texture crosshairTex = Texture(RESOURCES_PATH "textures/crosshair.png");

    glm::mat4 model = glm::mat4(1.0f);

    shader.use();
    shader.setInt("textureAtlas", 0);
    shader.setMat4("model", model);

    guiShader.use();
    guiShader.setInt("image", 0);

    BlockRenderer blockRenderer = BlockRenderer(shader);
    blockRenderer.initRenderData();

    GuiRenderer guiRenderer = GuiRenderer(guiShader);
    guiRenderer.initRenderData();

    Globals::blockRenderer = &blockRenderer;

    for (unsigned int x = 0; x < 32; x++) {
        for (unsigned int y = 0; y < 128; y++) {
            for (unsigned int z = 0; z < 32; z++) {
                Block block = Block(y != 127 ? DIRT : GRASS, {x, y, z});
                blockRenderer.addBlock(block);
            }
        }
    }

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    Widget crosshair = Widget({window.getWidth() / 2.0f - 25.0f, window.getHeight() / 2.0f - 25.0f}, 0.0f, {50.0f, 50.0f}, crosshairTex);

    while (!window.windowShouldClose()) {
        float currentFrame = glfwGetTime();

		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

        window.update();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(glm::radians(camera.zoom), (float) window.getWidth() / (float) window.getHeight(), 0.1f, 100.0f);
        glm::mat4 projection2D = glm::ortho(0.0f, (float) window.getWidth(), (float) window.getHeight(), 0.0f, -1.0f, 1.0f);

        shader.use();
        shader.setMat4("projection", projection);
        shader.setMat4("view", camera.getViewMatrix());

        guiShader.use();
        guiShader.setMat4("projection", projection2D);
        guiShader.setMat4("view", glm::mat4(1.0f));

        blockAtlas.bind();
        blockRenderer.render();

        glDisable(GL_DEPTH_TEST);
        guiRenderer.renderWidget(crosshair);
        glEnable(GL_DEPTH_TEST);

        Window::inputPerFrame(window.getWindow(), deltaTime);
    }

    window.cleanup();
}
