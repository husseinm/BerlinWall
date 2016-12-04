#ifndef BERLIN_WALL_CONFIG_H
#define BERLIN_WALL_CONFIG_H

#define BERLIN_WALL_VERSION_MAJOR 1
#define BERLIN_WALL_VERSION_MINOR 0

#ifdef __APPLE__
#include "ResourcePath.hpp"

static const std::string baseDir = resourcePath();
#else
static const  std::string baseDir = "";
#endif

#endif
