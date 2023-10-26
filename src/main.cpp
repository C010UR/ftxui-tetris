#include "ini.h"
#include "t_config/t_config.hpp"
#include "t_config/t_controls.hpp"
#include "t_config/t_serializer.hpp"
#include "t_engine/t_renderer.hpp"

int main(void)
{
    mINI::INIFile      file("config.ini");
    mINI::INIStructure ini;

    file.read(ini);

    Tetris::Config::Config   config;
    Tetris::Config::Controls controls;

    Tetris::Config::Serializer::Unserialize(ini, config);
    Tetris::Config::Serializer::Unserialize(ini, controls);

    int exitCode = Tetris::Engine::Renderer::mainLoop(config, controls);

    Tetris::Config::Serializer::Serialize(ini, config);
    Tetris::Config::Serializer::Serialize(ini, controls);

    file.write(ini);

    return exitCode;
}