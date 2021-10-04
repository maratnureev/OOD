#include <iostream>
#include <string>
#include <cstdint>
#include "CFileInputStream.h"
#include "CFileOutputStream.h"
#include "CMemoryInputStream.h"
#include "CMemoryOutputStream.h"
#include "COutputCompressStreamDecorator.h"
#include "COutputEncryptStreamDecorator.h"
#include "CInputDecompressStreamDecorator.h"
#include "CInputDecryptStreamDecorator.h"
#include <optional>

using namespace std;

struct Args {
    string inputFileName;
    string outputFileName;
    string searchString;
    string replaceString;
};

const string COMPRESS_OPTION = "--compress";
const string DECOMPRESS_OPTION = "--decompress";
const string ENCRYPT_OPTION = "--encrypt";
const string DECRYPT_OPTION = "--decrypt";

struct StreamStorage {
    IInputDataStreamPtr inputStream;
    IOutputDataStreamPtr outputStream;
};

void ShowUsage()
{
    cout << "Invalid arguments" << endl;
    cout << "Usage: transform.exe [ options ] <intputFileName> <outputFileName>" << endl;
    cout << "--encrypt <key> encrypt file" << endl;
    cout << "--decrypt <key> decrypt file" << endl;
    cout << "--compress compress file" << endl;
    cout << "--decompress decompress file" << endl;
}

optional<StreamStorage> BuildInputAndOutputStreams(int argc, char* argv[])
{
    if (argc < 3)
        return nullopt;
    string inputFileName = argv[argc - 2];
    string outputFileName = argv[argc - 1];
    IOutputDataStreamPtr outputStream = make_unique<CFileOutputStream>(outputFileName);
    IInputDataStreamPtr inputStream = make_unique<CFileInputStream>(inputFileName);
    int i = 1;
    while (i < argc - 2)
    {
        string paramName = argv[i++];
        if (paramName == COMPRESS_OPTION)
        {
            outputStream = make_unique<COutputCompressStreamDecorator>(move(outputStream));
        }
        else if (paramName == DECOMPRESS_OPTION)
        {
            inputStream = make_unique<CInputDecompressStreamDecorator>(move(inputStream));
        }
        else if (paramName == ENCRYPT_OPTION)
        { 
            int encryptKey = atoi(argv[i++]);
            outputStream = make_unique<COutputEncryptStreamDecorator>(move(outputStream), encryptKey);
        }
        else if(paramName == DECRYPT_OPTION)
        { 
            int encryptKey = atoi(argv[i++]);
            inputStream = make_unique<CInputDecryptStreamDecorator>(move(inputStream), encryptKey);
        }
        else
        {
            return nullopt;
        }
    }
    StreamStorage storage;
    storage.inputStream = move(inputStream);
    storage.outputStream = move(outputStream);
    return storage;
}

int main(int argc, char* argv[])
{
    auto streams = BuildInputAndOutputStreams(argc, argv);
    if (!streams)
    {
        ShowUsage();
        return 1;
    }
    while (!streams->inputStream->IsEOF())
    {
        auto data = streams->inputStream->ReadByte();
        streams->outputStream->WriteByte(data);
    }

	return 0;
}