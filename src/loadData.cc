#include "loadData.hh"

std::vector<double> loadFromTxt(const std::string &fileName)
{
    std::ifstream inputFile(fileName);
    std::string dataString;
    if (inputFile.is_open()) // Check if the file is open
    {
        std::getline(inputFile, dataString); // Read the content of the file into a string
        inputFile.close();                   // Close the file
    }
    else
    {
        std::cout << "Can't open " << fileName << std::endl;
        return {}; // return empty vector
    }

    // Now, parse the string and store values in a vector
    std::istringstream iss(dataString);
    std::vector<double> data;

    double value;
    while (iss >> value)
    {
        data.push_back(value);
    }

    return data;
}
