#pragma once

#include <map>
#include <variant>
#include <memory>
#include <string>

namespace ownfos
{
    class Instruction;
    using Data = std::variant<int, std::shared_ptr<Instruction>>;
    using Registers = std::map<std::string, Data>;
    using Memory = std::map<unsigned int, Data>;
}