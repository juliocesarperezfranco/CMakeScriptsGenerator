#ifndef UTILITIES_H
#define UTILITIES_H

#pragma once

#include "ScriptInfo.h"
#include "ConfigurationInfo.h"
#include "VariableInfo.h"

#include <string>
#include <iostream>

const bool IsValid(const ScriptInfo& scriptInfo);
const bool IsValid(const ConfigurationInfo& configurationInfo);
const bool IsValid(const EnvironmentInfo& environmentInfo);
const bool IsValid(const VariableInfo& variableInfo);

void Print(const std::string& message, const bool newLine = true);
void PrintVariable(const std::string& variableName, const std::string& value);

#endif // UTILITIES_H