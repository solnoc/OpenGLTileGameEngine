#include <GL\glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <Windows.h>
#include <chrono>

#include "error_checking.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_array.h"
#include "shader.h"
#include "renderer.h"
#include "texture.h"
#include "main_vertex_bufer.h"

#include "game_maps.h"
#include "singleton_assets.h"
#include "map_manager.h"
#include "entities_manager.h"
#include "dyamic_creature.h"
#include "script_processor.h"
#include "text_manager.h"

int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1240, 900, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    GLCall
    (
        if (glewInit() != GLEW_OK)
            std::cout << "ERROR" << std::endl;
    )
    GLCall(std::cout << glGetString(GL_VERSION) << std::endl);
    {
        singletonAssets::get().loadTextures();

        int tileWidth = 64;
        int tileHeight = 64;

        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);

        int screenSizeX = viewport[2];
        int screenSizeY = viewport[3];

        std::cout<<"SCREEN : " << screenSizeX << " " << screenSizeY << std::endl;

        Camera camera(screenSizeX, screenSizeY, 64, 64, 2, 2);

        gameMap* currentMap = new forestMap();
        mapManager* managerMap = new mapManager(&camera);
        managerMap->setCurrentMap(currentMap);

        scriptProcessor scriptProcessor;

        entitiesManager managerEntities(&camera);
        managerEntities.setCurrentMap(currentMap);

        dynamicCreature* player = new dynamicCreature("player",singletonAssets::get().getTexture("characther"));
        player->setPos(0,0);
        managerEntities.addEntity(player);

        dynamicCreature* creature_1 = new dynamicCreature("player2", singletonAssets::get().getTexture("characther"));
        creature_1->setPos(15,1);
        creature_1->setVel(1.0f, 0.0f);
        managerEntities.addEntity(creature_1);

        textManager managerText(&camera);

        dynamic* hello_my_ni = new dynamic("hello_ni");
        hello_my_ni->setTexture(singletonAssets::get().getTexture("hello_my_ni"));
        managerText.changeText(hello_my_ni);

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


        double frameDuration = 0.1f;
        auto lastTime = std::chrono::high_resolution_clock::now();
        bool pressedZ = false;
        while (!glfwWindowShouldClose(window))
        {
            player->setVel(0.0f, 0.0f);

            if (scriptProcessor.controlGiven)

            {
                float vel = 5.0f;
                if (GetKeyState('D') & 0x8000)
                {
                    player->setVel(vel, 0.0f);
                }
                else if (GetKeyState('A') & 0x8000)
                {
                    player->setVel(-vel, 0.0f);
                }
                if (GetKeyState('W') & 0x8000)
                {
                    player->setVel(0.0f, vel);
                }
                else if (GetKeyState('S') & 0x8000)
                {
                    player->setVel(0.0f, -vel);
                }
            }
            if (GetKeyState('Z') & 0x8000 && !pressedZ)
            {
                scriptProcessor.addCommand(new move_command(player, 12, 1, 4));
                scriptProcessor.addCommand(new move_command(player, 12, 20, 4));
                creature_1->setVel(0.0f, 0.0f);
                scriptProcessor.addCommand(new move_command(creature_1, 12, 1, 4));
                scriptProcessor.addCommand(new move_command(creature_1, 12, 19, 5));
                scriptProcessor.addCommand(new display_text(&managerText, true));
                scriptProcessor.addCommand(new move_command(player, 30, 20, 6));
                scriptProcessor.addCommand(new display_text(&managerText, false));
                pressedZ = true;
            }
            else if (pressedZ)
            {
                pressedZ = GetKeyState('Z') & 0x8000;
            }

            scriptProcessor.updateCurrentCommand(frameDuration);
            scriptProcessor.Clean();

            camera.setCamera((int)player->getPosX() - camera.VisibleTilesX()/2, (int)player->getPosY() - camera.VisibleTilesY()/2,
                (player->getPosX() - (int)player->getPosX()) * 64, (player->getPosY() - (int)player->getPosY()) * 64);
            camera.clipCamera();

            std::cout << (int)player->getPosX() << " " << (int)player->getPosY() << std::endl;
            std::cout << camera.CameraX() << " " << camera.CameraY() << std::endl << std::endl;


            managerMap->update(frameDuration);
            managerMap->draw();

            managerEntities.update(frameDuration);
            managerEntities.draw();

            managerText.update(frameDuration);
            managerText.draw();

            /* Swap front and back buffers */
            GLCall(glfwSwapBuffers(window));

            /* Poll for and process events */
            GLCall(glfwPollEvents());

            auto time = std::chrono::high_resolution_clock::now();
            frameDuration = std::chrono::duration_cast<std::chrono::milliseconds>(time - lastTime).count();
            frameDuration /= 1000.0f;

            lastTime = time;
        }
    }
    glfwTerminate();
    return 0;
}