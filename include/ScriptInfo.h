#ifndef SCRIPTINFO_H
#define SCRIPTINFO_H

#pragma once

#include "ConfigurationInfo.h"
#include <vector>

struct ScriptInfo
{
  std::string name;
  std::string version;
  std::string description;
  std::vector<ConfigurationInfo> configurations;
};

#endif // SCRIPTINFO_H