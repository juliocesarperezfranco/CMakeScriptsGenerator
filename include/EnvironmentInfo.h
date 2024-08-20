#ifndef ENVIRONMENTINFO_H
#define ENVIRONMENTINFO_H

#pragma once

#include "VariableInfo.h"
#include <vector>

struct EnvironmentInfo
{
  std::string name = "";
  std::string description = "";
  std::string enabled = "true";
  std::vector<VariableInfo> variables;
};

#endif // ENVIRONMENTINFO_H