cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(CrannBethadh VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 23)
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs")

# setup CPM
set(CPM_DOWNLOAD_VERSION 0.34.0)
set(CPM_DOWNLOAD_LOCATION "${LIB_DIR}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")

if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
    message(STATUS "Downloading CPM.cmake to ${CPM_DOWNLOAD_LOCATION}")
    file(DOWNLOAD
         https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake
         ${CPM_DOWNLOAD_LOCATION})
endif()

include(${CPM_DOWNLOAD_LOCATION})
# end of CPM setup

CPMAddPackage(
    NAME JUCE
    GITHUB_REPOSITORY juce-framework/JUCE
    GIT_TAG 7.0.5
    SOURCE_DIR ${LIB_DIR}/juce
)

set(TARGET_NAME CrannBethadhPlugin)

juce_add_plugin(${TARGET_NAME}
    COMPANY_NAME BearSoundProductions
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    PLUGIN_MANUFACTURER_CODE BRSD
    PLUGIN_CODE CRBH
    FORMATS AU VST3
    PRODUCT_NAME "Crann Bethadh"
)

juce_generate_juce_header(${TARGET_NAME})

target_sources(${TARGET_NAME}
    PRIVATE
        Source/ColourMenu.cpp
        Source/MenuStyleSheet.cpp
        Source/PluginEditor.cpp
        Source/PluginProcessor.cpp
        Source/RotaryKnobStyleSheet.cpp
        Source/Title.cpp 
)

target_include_directories(${TARGET_NAME}
    PRIVATE
        Sources
)

target_compile_definitions(${TARGET_NAME}
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0    
)


juce_add_binary_data(Images SOURCES
 Resources/CrannBethadh.png
 Resources/Mask.png
 Resources/title.png
)

set(JUCE_DEPENDENCIES
    juce::juce_audio_utils
    juce::juce_dsp
)

target_link_libraries(${TARGET_NAME}
    PRIVATE
        ${JUCE_DEPENDENCIES}
        Images
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

