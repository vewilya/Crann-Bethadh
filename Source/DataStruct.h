#pragma once 

#include "BinaryData.h"

/*
    DataStruct written by Eyal Amir
*/

struct DataStruct
{
    explicit DataStruct(const char* fileToFind)
    {
        for (int index = 0; index < BinaryData::namedResourceListSize; ++index)
        {
            auto binaryName = BinaryData::namedResourceList[index];
            auto fileName = BinaryData::getNamedResourceOriginalFilename(binaryName);

            if (fileName == fileToFind)
            {
                data = BinaryData::getNamedResource(binaryName, size);
                break;
            }
        }
        jassert(data != nullptr); //File not found
    }

    explicit DataStruct (const juce::String& fileToFind) : DataStruct (static_cast<const char*> (fileToFind.toUTF8())) {}
    // explicit DataStruct (const std::string& fileToFind) : DataStruct (fileToFind.c_str()) {}
    const char* data = nullptr;
    int size = 0;
};