#pragma once

#include <string>
#include <vector>
#include <fstream>

class Downloads
{
public:
    bool isEmpty() const
    {
        return 0 == m_downloads.size();
    }
    size_t count() const
    {
        return m_downloads.size();
    }
    void add(const std::string &item)
    {
        m_downloads.push_back(item);
    }
    void addFromFile(const std::string &filePath);
    void addFromStream(std::istream &inputStream);
    void remove(const std::string &item);

private:
    std::vector<std::string> m_downloads;
};