#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <string_view>

class CSVRow
{
    public:
        std::string_view operator[](std::size_t index) const
        {
            std::basic_string_view<char>::size_type pos = m_data[index-1] + 1;
            return std::string_view{&m_line[pos], m_data[index] -  pos};
        }
        std::size_t size() const
        {
            return m_data.size();
        }
        void readNextRow(std::istream& str)
        {
            std::getline(str, m_line);
            m_data.clear();
            std::string::size_type pos = 0;
            while((pos = m_line.find(',', pos)) != std::string::npos)
            {
                m_data.emplace_back(pos);
                ++pos;
            }
            // This checks for a trailing comma with no data after it.
            pos = m_line.size();
            m_data.emplace_back(pos);
        }
    private:
        std::string         m_line;
        std::vector<int>    m_data;
};


std::istream& operator >>(std::istream& str, CSVRow& data)
{
    data.readNextRow(str);
    return str;
}   

class CSVIterator
{   
    public:
        typedef std::input_iterator_tag     iterator_category;
        typedef CSVRow                      value_type;
        typedef std::size_t                 difference_type;
        typedef CSVRow*                     pointer;
        typedef CSVRow&                     reference;

        explicit CSVIterator(std::istream& str)  :m_str(str.good()?&str:NULL) { ++(*this); }
        CSVIterator()                   :m_str(NULL) {}

        // Pre Increment
        CSVIterator& operator++()               {if (m_str) { if (!((*m_str) >> m_row)){m_str = NULL;}}return *this;}
        // Post increment
        CSVIterator operator++(int)             {CSVIterator    tmp(*this);++(*this);return tmp;}
        CSVRow const& operator*()   const       {return m_row;}
        CSVRow const* operator->()  const       {return &m_row;}

        bool operator==(CSVIterator const& rhs) {return ((this == &rhs) || ((this->m_str == NULL) && (rhs.m_str == NULL)));}
        bool operator!=(CSVIterator const& rhs) {return !((*this) == rhs);}
    private:
        std::istream*       m_str;
        CSVRow              m_row;
};

class CSVRange
{
    std::istream&   stream;
    public:
        explicit CSVRange(std::istream& str)
            : stream(str)
        {}
        CSVIterator begin() const {return CSVIterator{stream};}
        CSVIterator end()   const {return CSVIterator{};}
};

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