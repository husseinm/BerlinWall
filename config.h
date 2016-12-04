#ifndef BERLIN_WALL_CONFIG_H
#define BERLIN_WALL_CONFIG_H

#define BERLIN_WALL_VERSION_MAJOR 1
#define BERLIN_WALL_VERSION_MINOR 0

#ifdef __APPLE__
#include "ResourcePath.hpp"
std::string baseDir = resourcePath();
#else
std::string baseDir = "";
#endif

#endif
