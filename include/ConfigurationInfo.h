#ifndef CONFIGURATIONINFO_H
#define CONFIGURATIONINFO_H

#pragma once

#include "EnvironmentInfo.h"
#include "VariableInfo.h"
#include <vector>

struct ConfigurationInfo
{
  bool enabled = false;
  std::string name = "";
  std::string version = "0.0.0";
  std::string description = "";
  std::string generator = "";
  std::string architecture = "";
  std::string sourceDir = "";
  std::string binaryDir = "";
  EnvironmentInfo environment;
  std::vector<VariableInfo> variables;
};

#endif // CONFIGURATIONINFO_H