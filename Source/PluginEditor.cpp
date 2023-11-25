#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "DataStruct.h"

double numberFromChocValue(const choc::value::ValueView& v) {
    return (
        v.isFloat32() ? (double) v.getFloat32()
            : (v.isFloat64() ? v.getFloat64()
                : (v.isInt32() ? (double) v.getInt32()
                    : (double) v.getInt64())));
}

//==============================================================================
ProcessBlockAudioProcessorEditor::ProcessBlockAudioProcessorEditor (CrannBethadhAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), processorRef (p)
{
    // UI Size and Resizing
    setSize (600, 600);
    // setResizable(true, true);
    // getConstrainer()->setFixedAspectRatio(1.0);
    // setResizeLimits(600, 300, 750, 375);

    choc::ui::WebView::Options opts;
    
    #if JUCE_DEBUG
        opts.enableDebugMode = true;
    #endif
    
    //     opts.fetchResource = [=](const choc::ui::WebView::Options::Path& p) -> std::optional<choc::ui::WebView::Options::Resource> {
    //     auto relPath = "." + (p == "/" ? "/index.html" : p);
    //     auto f = assetDirectory.getChildFile(relPath);
    //     juce::MemoryBlock mb;

    //     if (!f.existsAsFile() || !f.loadFileAsData(mb))
    //         return {};

    //     return choc::ui::WebView::Options::Resource {
    //         std::vector<uint8_t>(mb.begin(), mb.end()),
    //         getMimeType(f.getFileExtension().toStdString())
    //     };
    // };

    webView = std::make_unique<choc::ui::WebView>(opts);

    #if JUCE_MAC
        viewContainer.setView(webView->getViewHandle());
    #elif JUCE_WINDOWS
        viewContainer.setHWND(webView->getViewHandle());
    #else
    #error "No Linux support"
    #endif

    addAndMakeVisible(viewContainer);
    viewContainer.setBounds({0, 0, 600, 600});

    // 
    DataStruct htmlBinary ("Index.html");
    auto htmlFile = String::createStringFromData (htmlBinary.data, htmlBinary.size);

    if (htmlFile.isNotEmpty()) {
        webView->setHTML(htmlFile.toStdString());
    }

    // Install message passing handlers
    webView->bind("__postNativeMessage__", [=](const choc::value::ValueView& args) -> choc::value::Value {
        if (args.isArray()) {
            auto eventName = args[0].getString();

            // When the webView loads it should send a message telling us that it has established
            // its message-passing hooks and is ready for a state dispatch
            if (eventName == "ready") {
                if (auto* ptr = dynamic_cast<CrannBethadhAudioProcessor*>(getAudioProcessor())) {
                    // ptr->dispatchStateChange();
                }
            }

            if (eventName == "setParameterValue") {
                jassert(args.size() > 1);
                std::cout << "setParameterValue: " << args[1]["paramId"].getString() << std::endl;
                
                auto parameterID = args[1]["paramId"].getString();
                auto value = numberFromChocValue(args[1]["value"]);
                
                for (auto& p : processorRef.getParameters()) {
                   if (auto* pf = dynamic_cast<juce::AudioParameterFloat*>(p)) {
                        if (pf->paramID.toStdString() == parameterID) {
                            pf->setValueNotifyingHost(value);
                            break;
                        }
                    }
                }
                
                // return handleSetParameterValueEvent(args[1]);
            }
        }

        return {};
    });
}

ProcessBlockAudioProcessorEditor::~ProcessBlockAudioProcessorEditor()
{
}

//==============================================================================
void ProcessBlockAudioProcessorEditor::paint (juce::Graphics& g)
{
    
}

void ProcessBlockAudioProcessorEditor::resized()
{
    viewContainer.setBounds(getLocalBounds());
   
}

void  ProcessBlockAudioProcessorEditor::colourMenuChanged() {
    {
        juce::File result;
     
        // switch (colourMenu.getSelectedId())
        // {
        //     case 1:    result = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDocumentsDirectory).getChildFile("BearSound/Atmosphere/UB_UB_ACM__RYMDIGARE_01.wav"); break;
        //     case 2:    result = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDocumentsDirectory).getChildFile("BearSound/Atmosphere/UB_UB_ACM__RYMDIGARE_02.wav"); break;
        //     case 3:    result = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDocumentsDirectory).getChildFile("BearSound/Atmosphere/UB_UB_ACM__RYMDIGARE_03.wav"); break;
        //     case 4:    result = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDocumentsDirectory).getChildFile("BearSound/Atmosphere/UB_UB_ACM__RYMDIGARE_04.wav"); break;
        //     case 5:    result = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDocumentsDirectory).getChildFile("BearSound/Noise/UB_UB_ACM__RYMDIGARE_05.wav"); break;
        //     case 6:    result = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDocumentsDirectory).getChildFile("BearSound/Noise/UB_UB_ACM__RYMDIGARE_06.wav"); break;
        //     case 7:    result = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDocumentsDirectory).getChildFile("BearSound/Noise/UB_UB_ACM__RYMDIGARE_07.wav"); break;
        //     case 8:    result = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDocumentsDirectory).getChildFile("BearSound/Noise/UB_UB_ACM__RYMDIGARE_08.wav"); break;
                
        // }
        // if (result.getFileExtension() == ".wav" | result.getFileExtension() == ".mp3")
        // {
        //     juce::FileInputStream stream (result);
        //     if (stream.openedOk())
        //     {
        //         audioProcessor.getConvolver().getSavedFile() = result;
        //         audioProcessor.getConvolver().getRoot() = result.getParentDirectory().getFullPathName();
        //         audioProcessor.getConvolver().getConvolutionEngine().reset();
        //         // audioProcessor.getConvolver().getConvolutionEngine().loadImpulseResponse(result, juce::dsp::Convolution::Stereo::yes, juce::dsp::Convolution::Trim::yes, 0); // 0 to initialise the size of the loaded file dynamically!
        //         audioProcessor.getConvolver().loadIR(result);
        //     }
            
        // }

    }
}

//==============================================================================
choc::value::Value ProcessBlockAudioProcessorEditor::handleSetParameterValueEvent(const choc::value::ValueView& e) {
    // When setting a parameter value, we simply tell the host. This will in turn fire
    // a parameterValueChanged event, which will catch and propagate through dispatching
    // a state change event
    std::cout << "handleSetParameterValueEvent" << std::endl;

    if (e.isObject() && e.hasObjectMember("paramId") && e.hasObjectMember("value")) {
        auto const& paramId = e["paramId"].getString();
        double const v = numberFromChocValue(e["value"]);

        std::cout << "Inside: paramId: " << paramId << " value: " << v << std::endl;

        for (auto& p : getAudioProcessor()->getParameters()) {
            if (auto* pf = dynamic_cast<juce::AudioParameterFloat*>(p)) {
                if (pf->paramID.toStdString() == paramId) {
                    pf->setValueNotifyingHost(v);
                    break;
                }
            }
        }
    }

    return choc::value::Value();
}
