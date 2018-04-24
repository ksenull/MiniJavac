#pragma once

#include <iostream>
#include <unordered_map>

namespace symboltable {

    class Symbol {
    public:
        Symbol() = default;

        Symbol(const std::string& name) : name(name) {}

        Symbol(std::string&& name) : name(std::move(name)) {}

        Symbol(const Symbol&) = delete;

        Symbol operator=(const Symbol&) = delete;

    private:
        std::string name;
    };

    Symbol* getIntern(const std::string& src) {
        static std::unordered_map<std::string, Symbol*> allStrings;

        auto cached = allStrings.find(src);
        if (cached != allStrings.end()) {
            return cached->second;
        }

        auto* newVal = new Symbol(src);
        allStrings.insert({src, newVal});
        return newVal;
    }

}