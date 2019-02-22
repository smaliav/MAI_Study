#include <cstdint>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#define DEFAULT_TXT_NUM 1000

void UsageHelper() {
    std::cout << "ERROR: Incorrect number of arguments" << std::endl;
    std::cout << "Usage: ./tc <Input File> <Number of texts> <Output File>" << std::endl;
}

int main(int argc, char *argv[]) {
    // Some magic localisation
    std::locale::global(std::locale("en_US.UTF-8"));
    std::setlocale(LC_ALL, "en_US.UTF-8");
    std::wcin.imbue(std::locale());
    std::wcout.imbue(std::locale());

    uint32_t txtNum;
    std::string inputFileName;
    std::string outputFileName;
    
    if (argc < 4) {
        txtNum = DEFAULT_TXT_NUM;
    }
    else if (argc > 4 || std::stoi(argv[2]) < 1) {
        UsageHelper();
        return 0;
    }
    else {
        txtNum = std::stoi(argv[2]);
        inputFileName = argv[1];
        outputFileName = argv[3];
    }

    std::wifstream input(inputFileName.c_str());
    std::wofstream output(outputFileName.c_str());
    uint32_t cnt = 0;
    std::wstring str;
    std::wstring end = L"</doc>";

    do {
        std::getline(input, str);

        if (str == end) {
            ++cnt;
        }
        output << str << std::endl;

    } while (cnt < txtNum && !input.eof());
    input.close();
    output.close();

    return 0;
}