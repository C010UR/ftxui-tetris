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

namespace Tetris::Config
{
class YAMLParser
{

  public:

    inline const static std::string fileName = "config.yaml";

    template <typename T>
    static void decodeOptionalScalar(
        const YAML::Node &node, const std::string &name, T &value, std::function<bool(T)> validate
    );

    template <typename T>
    static void decodeOptionalVector(
        const YAML::Node &node, const std::string &name, std::vector<T> &value, std::function<bool(T)> validate
    );

    static void decodeOptionalBool(const YAML::Node &node, const std::string &name, int &value);

    static void loadData(Tetris::Config::Config &config, Tetris::Config::Controls &controls);
    static void saveData(const Tetris::Config::Config &config, const Tetris::Config::Controls &controls);
};
} // namespace Tetris::Config

namespace YAML
{
template <>
struct convert<Tetris::Config::Config>
{
    static YAML::Node encode(const Tetris::Config::Config &config);
    static bool       decode(const YAML::Node &node, Tetris::Config::Config &config);
};

template <>
struct convert<Tetris::Config::Controls>
{
    static YAML::Node encode(const Tetris::Config::Controls &controls);
    static bool       decode(const YAML::Node &node, Tetris::Config::Controls &controls);
};

template <>
struct convert<ftxui::Color>
{
    static YAML::Node encode(const ftxui::Color &color);
    static bool       decode(const YAML::Node &node, ftxui::Color &color);
};

template <>
struct convert<Tetris::Config::Theme>
{
    static YAML::Node encode(const Tetris::Config::Theme &theme);
    static bool       decode(const YAML::Node &node, Tetris::Config::Theme &theme);
};

template <>
struct convert<std::vector<Tetris::Config::Theme>>
{
    static YAML::Node encode(const std::vector<Tetris::Config::Theme> &themes);
    static bool       decode(const YAML::Node &node, std::vector<Tetris::Config::Theme> &themes);
};
} // namespace YAML