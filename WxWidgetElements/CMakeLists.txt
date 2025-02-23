cmake_minimum_required(VERSION 3.29)

add_executable(WxWidgetElements Calculator.cpp)

target_sources(WxWidgetElements PRIVATE
${CMAKE_SOURCE_DIR}/${IncludeFolder}/Constants.ixx 
Application.h
Frame.h
DigitButton.h
InputField.h
Application.cpp
Frame.cpp
DigitButton.cpp
InputField.cpp
)

target_link_directories(WxWidgetElements PRIVATE ${CMAKE_SOURCE_DIR}/${IncludeFolder})
target_include_directories(WxWidgetElements PRIVATE ${CMAKE_SOURCE_DIR}/${IncludeFolder})
find_package(wxWidgets CONFIG REQUIRED)
target_link_libraries(WxWidgetElements PRIVATE wx::core wx::base FunctionEvaluator InputChecker)