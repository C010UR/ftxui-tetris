#pragma once

#include "ftxui/screen/color.hpp"
#include "t_config/t_config.hpp"
#include "t_config/t_controls.hpp"
#include "t_config/t_theme.hpp"
#include "t_renderer/t_data_transformer.hpp"

#include <fstream>
#include <functional>
#include <regex>
#include <vector>
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/node/type.h>
#include <yaml-cpp/yaml.h>

namespace Tetris::Config {
class YAMLParser
{
  public:
    inline const static std::string fileName = "config.yaml";

    template<typename T>
    static void decodeOptionalScalar(
        const YAML::Node      &node,
        const std::string     &name,
        T                     &value,
        std::function<bool(T)> validate = [](T) -> bool {
            return true;
        });

    template<typename T>
    static void decodeOptionalVector(
        const YAML::Node      &node,
        const std::string     &name,
        std::vector<T>        &value,
        std::function<bool(T)> validate = [](T) -> bool {
            return true;
        });

    static void decodeOptionalString(const YAML::Node &node, const std::string &name, std::string &value);

    static void loadData(Config &config, Controls &controls);
    static void saveData(const Config &config, const Controls &controls);
};
} // namespace Tetris::Config

namespace YAML {

using Tetris::Config::Config;
using Tetris::Config::Controls;
using Tetris::Config::Theme;
using Tetris::Config::YAMLParser;

template<>
struct convert<Config>
{
    static YAML::Node encode(const Config &config);
    static bool       decode(const YAML::Node &node, Config &config);
};

template<>
struct convert<Controls>
{
    static YAML::Node encode(const Controls &controls);
    static bool       decode(const YAML::Node &node, Controls &controls);
};

template<>
struct convert<ftxui::Color>
{
    static YAML::Node encode(const ftxui::Color &color);
    static bool       decode(const YAML::Node &node, ftxui::Color &color);
};

template<>
struct convert<Theme>
{
    static YAML::Node encode(const Theme &theme);
    static bool       decode(const YAML::Node &node, Theme &theme);
};

template<>
struct convert<std::vector<Theme>>
{
    static YAML::Node encode(const std::vector<Theme> &themes);
    static bool       decode(const YAML::Node &node, std::vector<Theme> &themes);
};
} // namespace YAML