#pragma once

namespace ownfos
{
    // A utility template for generating visitor instance (for std::visit) with multiple lambdas
    //
    // Example:
    // std::visit(Visitor{
    //     [](auto& something){std::cout << something; }
    // }, variant);
    template<typename... Lambda>
    struct Visitor : Lambda... { using Lambda::operator()...; };
    template<typename... Lambda>
    Visitor(Lambda...)->Visitor<Lambda...>;
}