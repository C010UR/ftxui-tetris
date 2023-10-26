#include "t_config/t_config.hpp"
#include "t_config/t_controls.hpp"
#include "t_config/t_yaml_parser.hpp"
#include "t_engine/t_renderer.hpp"

int main(void)
{
    Tetris::Config::Config   config;
    Tetris::Config::Controls controls;

    Tetris::Config::YAMLParser::loadData(config, controls);

    int exitCode = Tetris::Engine::Renderer::mainLoop(config, controls);

    Tetris::Config::YAMLParser::saveData(config, controls);

    return exitCode;
}