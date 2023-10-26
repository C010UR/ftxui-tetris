#pragma once

#include "ftxui/screen/color.hpp"
#include "ini.h"
#include "t_config/t_config.hpp"
#include "t_config/t_controls.hpp"
#include "t_config/t_theme.hpp"

#include <iomanip>
#include <istream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

namespace Tetris::Config
{
class Serializer
{
  private:

    template <typename T>
    static bool isConvertible(const std::string &value);

    template <typename T>
    static T convert(const std::string &value, T min, T max, T defaultValue);

    static std::string escapeString(const std::string &value);
    static std::string unEscapeString(const std::string &value, std::string defaultValue = "");

    static std::string convertToString(bool value);
    static std::string convertToString(double value);
    static std::string convertToString(int value);

    static std::vector<std::string> splitEscapedString(const std::string &value);
    static void joinString(const std::vector<std::string> &values);

    static bool isBool(const std::string &value);
    static bool convertToBool(const std::string &value);

    static bool         isColor(const std::string &value);
    static ftxui::Color convertToColor(const std::string &value, ftxui::Color defaultValue = ftxui::Color::Default);

    static std::vector<ftxui::Color> convertToColorArray(const std::string &value);

    static Tetris::Config::Theme unserializeTheme(mINI::INIStructure &ini, const std::string &name);

  public:

    inline static const std::string configSection   = "config";
    inline static const std::string controlsSection = "controls";

    static void Serialize(mINI::INIStructure &ini, Tetris::Config::Config &config);
    static void Unserialize(mINI::INIStructure &ini, Tetris::Config::Config &config);

    static void Serialize(mINI::INIStructure &ini, Tetris::Config::Controls &controls);
    static void Unserialize(mINI::INIStructure &ini, Tetris::Config::Controls &controls);
};
} // namespace Tetris::Config