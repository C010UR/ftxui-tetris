#include "t_config/t_serializer.hpp"

#include "t_config/t_theme.hpp"

#include <vector>

namespace Tetris::Config
{
bool Serializer::isBool(const std::string &value)
{
    std::string lowerValue = value;

    std::transform(lowerValue.begin(), lowerValue.end(), lowerValue.begin(), [](unsigned char c) {
        return std::tolower(c);
    });

    return lowerValue == "true" || lowerValue == "false" || lowerValue == "1" || lowerValue == "0";
}

bool Serializer::convertToBool(const std::string &value)
{
    std::string lowerValue = value;

    std::transform(lowerValue.begin(), lowerValue.end(), lowerValue.begin(), [](unsigned char c) {
        return std::tolower(c);
    });

    return lowerValue == "true" || lowerValue == "1";
}

std::vector<std::string> Serializer::splitEscapedString(const std::string &value)
{
    std::vector<std::string> result;
    std::string              current;
    std::size_t              startPos = value.find_first_of('"');
    std::size_t              endPos   = value.find_first_of('"', startPos + 1);

    while (startPos != std::string::npos && endPos != std::string::npos)
    {
        current = value.substr(startPos + 1, endPos - startPos - 1);
        result.push_back(current);

        startPos = value.find_first_of('"', endPos + 1);
        endPos   = value.find_first_of('"', startPos + 1);
    }

    return result;
}

bool Serializer::isColor(const std::string &value)
{
    std::regex rgbPattern(
        "\\s*rgb\\((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|\\d{1,2})\\s*,\\s*(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|\\d{1,2})\\s*,"
        "\\s*(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|\\d{1,2})\\)\\s*",
        std::regex_constants::icase
    );
    std::regex hexPattern("\\s*#([A-Fa-f0-9]{2})([A-Fa-f0-9]{2})([A-Fa-f0-9]{2})\\s*");

    return std::regex_match(value, rgbPattern) || std::regex_match(value, hexPattern);
}

ftxui::Color Serializer::convertToColor(const std::string &value, ftxui::Color defaultValue)
{
    std::regex rgbPattern(
        "\\s*rgb\\((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|\\d{1,2})\\s*,\\s*(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|\\d{1,2})\\s*,"
        "\\s*(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|\\d{1,2})\\)\\s*",
        std::regex_constants::icase
    );
    std::regex hexPattern("\\s*#([A-Fa-f0-9]{2})([A-Fa-f0-9]{2})([A-Fa-f0-9]{2})\\s*", std::regex_constants::icase);

    std::smatch match;

    if (std::regex_match(value, match, rgbPattern))
    {
        return ftxui::Color::RGB(std::stoi(match[1].str()), std::stoi(match[2].str()), std::stoi(match[3].str()));
    }
    else if (std::regex_match(value, match, hexPattern))
    {
        return ftxui::Color::RGB(
            std::stoi(match[1].str(), nullptr, 16),
            std::stoi(match[2].str(), nullptr, 16),
            std::stoi(match[3].str(), nullptr, 16)
        );
    }

    return defaultValue;
}

std::vector<ftxui::Color> Serializer::convertToColorArray(const std::string &value)
{
    std::vector<std::string>  colorsStr = splitEscapedString(value);
    std::vector<ftxui::Color> colors;

    for (int i = 0; i < (int)colorsStr.size(); i++)
    {
        if (isColor(colorsStr[i]))
        {
            colors.push_back(convertToColor(colorsStr[i]));
        }
    }

    return colors;
}

template <typename T>
bool Serializer::isConvertible(const std::string &value)
{
    std::istringstream iss(value);

    T result;

    return iss >> result && iss.eof();
}

template <typename T>
T Serializer::convert(const std::string &value, T min, T max, T defaultValue)
{
    std::istringstream iss(value);

    T result;

    iss >> result;

    if (result < min || (max > min && result > max))
    {
        return defaultValue;
    }

    return result;
}

std::string Serializer::convertToString(bool value)
{
    return value ? "true" : "false";
}

std::string Serializer::convertToString(double value)
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(3) << value;

    return stream.str();
}

std::string Serializer::convertToString(int value)
{
    return std::to_string(value);
}

std::string Serializer::escapeString(const std::string &value)
{
    return "\"" + value + "\"";
}

std::string Serializer::unEscapeString(const std::string &value, std::string defaultValue)
{
    if (value.empty())
    {
        return defaultValue;
    }

    std::string unescapedString = value;

    if (unescapedString.size() >= 2 && unescapedString[0] == '"' && unescapedString[unescapedString.size() - 1] == '"')
    {
        unescapedString = unescapedString.substr(1, unescapedString.size() - 2);
    }

    if (unescapedString.empty())
    {
        return defaultValue;
    }

    return unescapedString;
}

void Serializer::Serialize(mINI::INIStructure &ini, Tetris::Config::Config &config)
{
    ini[configSection]["isDebug"]          = convertToString((bool)config.isDebug);
    ini[configSection]["isEasyMode"]       = convertToString((bool)config.isEasyMode);
    ini[configSection]["storeDelay"]       = convertToString(config.storeDelay);
    ini[configSection]["softDropDelay"]    = convertToString(config.softDropDelay);
    ini[configSection]["comboDelay"]       = convertToString(config.comboDelay);
    ini[configSection]["updatesPerSecond"] = convertToString(config.updatesPerSecond);
    ini[configSection]["level"]            = convertToString(config.level);
    ini[configSection]["currentTheme"]     = escapeString(config.themes[config.currentTheme].name);
}

Tetris::Config::Theme Serializer::unserializeTheme(mINI::INIStructure &ini, const std::string &name)
{
    Tetris::Config::Theme theme;

    theme.mainColors     = convertToColorArray(ini[name]["mainGradientColors"]);
    theme.gameOverColors = convertToColorArray(ini[name]["gameOverGradientColors"]);

    theme.mainColor     = convertToColor(unEscapeString(ini[name]["mainColor"]));
    theme.gameOverColor = convertToColor(unEscapeString(ini[name]["gameOverColor"]));

    theme.valueColor = convertToColor(unEscapeString(ini[name]["valueColor"]));
    theme.trueColor  = convertToColor(unEscapeString(ini[name]["trueColor"]));
    theme.falseColor = convertToColor(unEscapeString(ini[name]["falseColor"]));

    theme.IColor = convertToColor(unEscapeString(ini[name]["IColor"]));
    theme.OColor = convertToColor(unEscapeString(ini[name]["OColor"]));
    theme.TColor = convertToColor(unEscapeString(ini[name]["TColor"]));
    theme.JColor = convertToColor(unEscapeString(ini[name]["JColor"]));
    theme.LColor = convertToColor(unEscapeString(ini[name]["LColor"]));
    theme.SColor = convertToColor(unEscapeString(ini[name]["SColor"]));
    theme.ZColor = convertToColor(unEscapeString(ini[name]["ZColor"]));

    theme.name = name;

    return theme;
}

void Serializer::Unserialize(mINI::INIStructure &ini, Tetris::Config::Config &config)
{
    config.isDebug
        = isBool(ini[configSection]["isDebug"]) ? convertToBool(ini[configSection]["isDebug"]) : config.isDebug;

    config.isEasyMode = isBool(ini[configSection]["isEasyMode"]) ? convertToBool(ini[configSection]["isEasyMode"])
                                                                 : config.isEasyMode;

    config.storeDelay = isConvertible<int>(ini[configSection]["storeDelay"])
                            ? convert<int>(ini[configSection]["storeDelay"], 0, -1, config.storeDelay)
                            : config.storeDelay;

    config.softDropDelay = isConvertible<int>(ini[configSection]["softDropDelay"])
                               ? convert<int>(ini[configSection]["softDropDelay"], 0, -1, config.softDropDelay)
                               : config.softDropDelay;

    config.comboDelay = isConvertible<int>(ini[configSection]["comboDelay"])
                            ? convert<int>(ini[configSection]["comboDelay"], 0, -1, config.comboDelay)
                            : config.comboDelay;

    config.updatesPerSecond = isConvertible<int>(ini[configSection]["updatesPerSecond"])
                                  ? convert<int>(ini[configSection]["updatesPerSecond"], 1, -1, config.updatesPerSecond)
                                  : config.updatesPerSecond;

    config.level = isConvertible<int>(ini[configSection]["level"])
                       ? convert<int>(ini[configSection]["level"], 0, -1, config.level)
                       : config.level;

    std::string currentTheme = unEscapeString(ini[configSection]["currentTheme"], "Default");

    std::vector<std::string> themes = splitEscapedString(ini[configSection]["themes"]);

    Tetris::Config::Theme defaultTheme;
    defaultTheme.setDefault();

    config.themes.push_back(defaultTheme);

    for (int i = 0; i < (int)themes.size(); i++)
    {
        config.themes.push_back(unserializeTheme(ini, themes[i]));

        if (themes[i] == currentTheme) {
            config.currentTheme = config.themes.size() - 1;
        }
    }

    config.applyTheme();
}

void Serializer::Serialize(mINI::INIStructure &ini, Tetris::Config::Controls &controls)
{
    ini[controlsSection]["moveLeft"]    = escapeString(controls.moveLeft);
    ini[controlsSection]["moveRight"]   = escapeString(controls.moveRight);
    ini[controlsSection]["rotateLeft"]  = escapeString(controls.rotateLeft);
    ini[controlsSection]["rotateRight"] = escapeString(controls.rotateRight);
    ini[controlsSection]["swapHold"]    = escapeString(controls.swapHold);
    ini[controlsSection]["softDrop"]    = escapeString(controls.softDrop);
    ini[controlsSection]["hardDrop"]    = escapeString(controls.hardDrop);
    ini[controlsSection]["forfeit"]     = escapeString(controls.forfeit);
}

void Serializer::Unserialize(mINI::INIStructure &ini, Tetris::Config::Controls &controls)
{
    controls.moveLeft    = unEscapeString(ini[controlsSection]["moveLeft"], controls.moveLeft);
    controls.moveRight   = unEscapeString(ini[controlsSection]["moveRight"], controls.moveRight);
    controls.rotateLeft  = unEscapeString(ini[controlsSection]["rotateLeft"], controls.rotateLeft);
    controls.rotateRight = unEscapeString(ini[controlsSection]["rotateRight"], controls.rotateRight);
    controls.swapHold    = unEscapeString(ini[controlsSection]["swapHold"], controls.swapHold);
    controls.softDrop    = unEscapeString(ini[controlsSection]["softDrop"], controls.softDrop);
    controls.hardDrop    = unEscapeString(ini[controlsSection]["hardDrop"], controls.hardDrop);
    controls.forfeit     = unEscapeString(ini[controlsSection]["forfeit"], controls.forfeit);
}

} // namespace Tetris::Config