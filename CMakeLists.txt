cmake_minimum_required(VERSION 3.25)
project(cmake-scripts-generator VERSION 1.0.0 DESCRIPTION "Generador de guiones de construccion, generacion, instalacion y empaquetamiento")

find_package(wxWidgets COMPONENTS core base xml)
include(${wxWidgets_USE_FILE})

add_executable(cmake-scripts-generator 
  include/EnvironmentInfo.h
  include/ScriptInfo.h
  include/VariableInfo.h
  include/ConfigurationInfo.h
  src/Utilities.h
  src/Utilities.cxx
  src/ScriptParser.h
  src/ScriptParser.cxx
  src/CommandApp.cxx
)

target_include_directories(cmake-scripts-generator 
  PRIVATE
    include
    ${PROJECT_SRC_DIR}
    ${wxWidgets_INCLUDE_DIRS}
)

target_link_libraries(cmake-scripts-generator 
  PRIVATE 
    ${wxWidgets_LIBRARIES}
)
