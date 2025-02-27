# easyduck CMakeLists.txt

cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 17)

project(easyduck VERSION 0.1.0)

# Write version.json using template
configure_file(${CMAKE_SOURCE_DIR}/pipelines/version_template.json ${CMAKE_BINARY_DIR}/version.json @ONLY)

add_subdirectory(external/JUCE)                  
add_subdirectory(external/BDSP)

juce_add_plugin(easyduck
    # VERSION ...                       # Set this if the plugin version is different to the project version
    # ICON_BIG ...                      # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
    # ICON_SMALL ...
    COMPANY_NAME "butch_warns"          # Specify the name of the plugin's author
    IS_SYNTH FALSE                      # Is this a synth or an effect?
    NEEDS_MIDI_INPUT FALSE              # Does the plugin need midi input?
    NEEDS_MIDI_OUTPUT FALSE             # Does the plugin need midi output?
    IS_MIDI_EFFECT FALSE                # Is this plugin a MIDI effect?
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE   # Does the editor need keyboard focus?
    COPY_PLUGIN_AFTER_BUILD TRUE        # Should the plugin be installed to a default location after building?
    PLUGIN_MANUFACTURER_CODE Buwa       # A four-character manufacturer id with at least one upper-case character
    PLUGIN_CODE Duck                    # A unique four-character plugin id with exactly one upper-case character
                                        # GarageBand 10.3 requires the first letter to be upper-case, and the remaining letters to be lower-case
    FORMATS VST3 AU                     # The formats to build. Valid formats are: VST3 AAX Unity VST AU AUv3 Standalone
    PRODUCT_NAME "easyduck")            # The name of the final executable, which can differ from the target name

###############################################################################
# Sources

juce_generate_juce_header(easyduck)

file(GLOB_RECURSE SOURCE_FILES "source/*.cpp")

target_sources(easyduck
    PRIVATE
        ${SOURCE_FILES})

###############################################################################

target_compile_definitions(easyduck
    PUBLIC
        JUCE_WEB_BROWSER=0                  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_plugin` call
        JUCE_USE_CURL=0                     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_plugin` call
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_DISPLAY_SPLASH_SCREEN=0        # If you disable the splashscreen, you either need a valid JUCE license or release under GPLv3
        JUCE_REPORT_APP_USAGE=0
        JUCE_ENABLE_REPAINT_DEBUGGING=0)

juce_add_binary_data(PluginBinaryData 
    NAMESPACE 
        BinaryData
    SOURCES
        build/version.json
        resources/fonts/Inter-Regular.otf
        resources/fonts/Inter-Italic.otf
        resources/fonts/Inter-Bold.otf
        resources/fonts/Inter-Black.otf)

target_link_libraries(easyduck
    PRIVATE
        BDSP
        PluginBinaryData
        juce::juce_audio_utils
        juce::juce_dsp
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpic") # Position-independent code, needed for linking to binary target on linux