#include "Symbol.h"

#include <unordered_map>

namespace symboltable {
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