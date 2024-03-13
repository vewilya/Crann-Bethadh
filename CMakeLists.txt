cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(CrannBethadh VERSION 0.0.12)

set(CMAKE_CXX_STANDARD 20)
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs")

# Get Webview Content Folder
set(ASSETS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ui/dist")

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

CPMAddPackage(
    NAME CLAP
    GITHUB_REPOSITORY free-audio/clap-juce-extensions
    GIT_TAG 9ed8659
    SOURCE_DIR ${LIB_DIR}/clap-juce-extensions
)

CPMAddPackage(
    NAME choc
    GITHUB_REPOSITORY nick-thompson/choc
    GIT_TAG nick/edits
    SOURCE_DIR ${LIB_DIR}/choc
)

CPMAddPackage(
    NAME GOOGLETEST
    GITHUB_REPOSITORY google/googletest
    VERSION 1.14.0
    SOURCE_DIR ${LIB_DIR}/googletest
    OPTIONS "gtest_force_shared_crt"
)

set(TARGET_NAME CrannBethadhPlugin)

juce_add_plugin(${TARGET_NAME}
    COMPANY_NAME BearSoundProductions
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE BRSD
    PLUGIN_CODE CRBH
    APP_SANDBOX_ENABLED TRUE
    APP_SANDBOX_OPTIONS com.apple.security.network.client com.apple.security.files.user-selected.read-write
    FORMATS AU VST3 Standalone
    PRODUCT_NAME "Crann Bethadh"
)

juce_generate_juce_header(${TARGET_NAME})

target_sources(${TARGET_NAME}
    PRIVATE
        Source/ColourMenu.cpp
        Source/MenuStyleSheet.cpp
        Source/PluginEditor.cpp
        Source/PluginProcessor.cpp
        Source/PluginParameters.h
        Source/RotaryKnobStyleSheet.cpp
        Source/Title.cpp 
        Source/Convolver.cpp    
        Source/Saturator.cpp
        Source/SaturatorBoutique.h
        Source/DelayLine.cpp
        Source/DataStruct.h
)

target_include_directories(${TARGET_NAME}
    PRIVATE
        Sources
        ${LIB_DIR}/choc/gui
        ${LIB_DIR}/choc/javascript
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
    ui/dist/Index.html
    ui/dist/manifest.json
    # ui/dist/assets/index-RGnjRSa1.js
    # ui/dist/assets/index-JwSxX1cZ.css
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

clap_juce_extensions_plugin(TARGET ${TARGET_NAME}
        CLAP_ID "com.bearsound.crannbethadh"
        CLAP_FEATURES audio-effect "spatial" reverb convolution mysterious )

enable_testing()
add_subdirectory(test)
