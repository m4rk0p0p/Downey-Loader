#include "downloads.h"

void Downloads::addFromFile(const std::string &filePath)
{
    std::ifstream inputStream(filePath);
    addFromStream(inputStream);
}

void Downloads::addFromStream(std::istream &inputStream)
{
    if(inputStream.good())
    {
        std::string line;
        while(std::getline(inputStream, line))
        {
            m_downloads.push_back(line);
        }
    }
}

void Downloads::remove(const std::string &item)
{
    auto iter = std::find(m_downloads.cbegin(), m_downloads.cend(), item);
    m_downloads.erase(iter);
}