cmake_minimum_required(VERSION 3.22)

project(CrannBethadhTest)

enable_testing()

add_executable(CrannBethadhTest
                Test.cpp)

target_include_directories(CrannBethadhTest PRIVATE
                ${CMAKE_CURRENT_SOURCE_DIR}/../Source
                ${CMAKE_BINARY_DIR}/CrannBethadhPlugin_artefacts/JuceLibraryCode
                ${CMAKE_BINARY_DIR}/juce_binarydata_Images/JuceLibraryCode
                ${JUCE_SOURCE_DIR}/modules
                ${GOOGLETEST_SOURCE_DIR}/googletest/include)

target_compile_definitions(CrannBethadhTest PRIVATE JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED=1)

target_link_libraries(CrannBethadhTest PRIVATE GTest::gtest_main CrannBethadhPlugin)

include(GoogleTest)

gtest_discover_tests(CrannBethadhTest)