#pragma once

#include <cctype>
#include <string>

namespace Tetris::Renderer
{
class DataTransformer
{
  public:

    static std::string transformKey(std::string key);
};
} // namespace Tetris::Renderer