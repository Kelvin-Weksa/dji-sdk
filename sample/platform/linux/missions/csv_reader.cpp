
#include "csv_reader.hpp"

std::istream& operator >>(std::istream& str, CSVRow& data)
{
    data.readNextRow(str);
    return str;
}   


int main_CSVRow()
{
    std::ifstream file("SampleWaypoints.csv");
    CSVRow row;
    while(file >> row)
    {
        std::cout << std::string{row[3]} << std::endl;
    }


    std::cout << std::endl;
    std::ifstream file2("SampleWaypoints.csv");
    for(CSVIterator loop(file2); loop != CSVIterator(); ++loop)
    {
        std::cout << "4th Element(" << (*loop)[3] << ")\n";
    }

    std::cout << std::endl;
    std::ifstream file3("SampleWaypoints.csv");
    for(auto& row3: CSVRange(file3))
    {
        std::cout << "4th Element(" << row3[3] << ")\n";
    }
    return 0;
}