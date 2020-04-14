#pragma once

#include <string>
#include "imgui.h"

namespace ownfos
{
    // A utility template for ImGui combo box.
    // Selected item will be saved in selectedItem parameter
    // 
    // converter: A lambda that transforms raw element of container to any wanted type (e.g. return second element from std::pair)
    // formatter: A lambda that returns formatted std::string of "convereted" type
    template<typename ItemType, typename ContainerType, typename Formatter, typename Converter>
    void Selector(std::string label, ItemType& selectedItem, const ContainerType& selectables, Formatter formatter, Converter converter)
    {
        if (ImGui::BeginCombo(label.c_str(), formatter(selectedItem).c_str()))
        {
            for (auto& e : selectables)
            {
                auto item = converter(e);
                auto isSelected = (selectedItem == item);
                if (ImGui::Selectable(formatter(item).c_str(), &isSelected))
                    selectedItem = item;
            }
            ImGui::EndCombo();
        }
    }
}