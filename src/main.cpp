#include "ini.h"
#include "t_config/t_config.hpp"
#include "t_config/t_controls.hpp"
#include "t_config/t_serializer.hpp"
#include "t_engine/t_renderer.hpp"

#include <cstdlib>
#include <stdlib.h>

int main(void)
{
    mINI::INIFile      file("config.ini");
    mINI::INIStructure ini;

    file.read(ini);

    Tetris::Config::Config   config;
    Tetris::Config::Controls controls;

    Tetris::Config::Serializer::Unserialize(ini, config);
    Tetris::Config::Serializer::Unserialize(ini, controls);

    bool isStartGame = false;

    while (true)
    {
        isStartGame = Tetris::Engine::Renderer::menuLoop(config, controls, isStartGame);

        if (!isStartGame)
        {
            break;
        }
    }

    Tetris::Config::Serializer::Serialize(ini, config);
    Tetris::Config::Serializer::Serialize(ini, controls);

    file.write(ini);

    return EXIT_SUCCESS;
}