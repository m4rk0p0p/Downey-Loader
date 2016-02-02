#include <gmock/gmock.h>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <string>

#include "downloads.h"

using namespace testing;

class Downloads
{
public:
    bool isEmpty()
    {
        return 0 == m_downloads.size();
    }
    size_t count()
    {
        return m_downloads.size();
    }
    void add(const std::string &item)
    {
        m_downloads.push_back(item);
    }
    void addFromFile(const std::string &filePath)
    {
        std::ifstream inputStream(filePath);
        addFromStream(inputStream);
    }
    void addFromStream(std::istream &inputStream)
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

    void remove(const std::string &item)
    {
        auto iter = std::find(m_downloads.cbegin(), m_downloads.cend(), item);
        m_downloads.erase(iter);
    }

private:
    std::vector<std::string> m_downloads;
};

TEST(ADownloads, IsEmptyOnCreation)
{
    Downloads downloads;

    ASSERT_TRUE(downloads.isEmpty());
}

//https://www.dropbox.com/s/bg2rq3jqy6y0emm/update.exe?dl=1
//https://www.dropbox.com/s/2449ff5dexu4h61/WindowWrapper.sdf?dl=1
//https://www.dropbox.com/s/e6ut789kcfljd6f/testapp.exe?dl=1

TEST(ADownloads, KeepsTrackOfDownloadItems)
{
    Downloads downloads;

    downloads.add("https://www.dropbox.com/s/bg2rq3jqy6y0emm/update.exe?dl=1");
    downloads.add("https://www.dropbox.com/s/e6ut789kcfljd6f/testapp.exe?dl=1");

    ASSERT_THAT(downloads.count(), Eq(2));
}

TEST(ADownloads, SizeReflectsAddedAndRemovedElements)
{
    Downloads downloads;

    downloads.add("https://www.dropbox.com/s/bg2rq3jqy6y0emm/update.exe?dl=1");
    downloads.add("https://www.dropbox.com/s/2449ff5dexu4h61/WindowWrapper.sdf?dl=1");
    downloads.add("https://www.dropbox.com/s/e6ut789kcfljd6f/testapp.exe?dl=1");

    downloads.remove("https://www.dropbox.com/s/bg2rq3jqy6y0emm/update.exe?dl=1");

    ASSERT_THAT(downloads.count(), Eq(2));
}

TEST(ADownloads, DoesNotAddDownloadsIfInputFileIsEmpty)
{
    Downloads downloads;

    downloads.add("https://www.dropbox.com/s/bg2rq3jqy6y0emm/update.exe?dl=1");
    std::string dummyFileContents;
    std::istringstream fileStreamStub(dummyFileContents);

    downloads.addFromStream(fileStreamStub);

    ASSERT_THAT(downloads.count(), Eq(1));
}

TEST(ADownloads, LoadsNonemptyDownloadListFromFile)
{
    Downloads downloads;

    std::string dummyFileContents =
        "http://www.stash.com/files/1\r\n"
        "http://www.stash.com/files/2\r\n"
        "http://www.stash.com/files/3\r\n"
        "http://www.stash.com/files/4\r\n";
    std::istringstream fileStreamStub(dummyFileContents);

    downloads.addFromStream(fileStreamStub);

    ASSERT_THAT(downloads.count(), Eq(4));
}