#include "API.h"

Gazua::API::API(): token{}
{}

bool Gazua::API::access(const std::string& key, const std::string& secret) {
    return true;
}

bool Gazua::API::refresh() {
    return true;
}
