#include <gmock/gmock.h>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <string>

#include "downloads.h"

using namespace testing;

TEST(ADownloads, IsEmptyOnCreation)
{
    Downloads downloads;

    ASSERT_TRUE(downloads.isEmpty());
}

TEST(ADownloads, KeepsTrackOfDownloadItems)
{
    Downloads downloads;

    downloads.add("http://www.stash.com/files/1");
    downloads.add("http://www.stash.com/files/3");

    ASSERT_THAT(downloads.count(), Eq(2));
}

TEST(ADownloads, SizeReflectsAddedAndRemovedElements)
{
    Downloads downloads;

    downloads.add("http://www.stash.com/files/1");
    downloads.add("http://www.stash.com/files/2");
    downloads.add("http://www.stash.com/files/3");

    downloads.remove("http://www.stash.com/files/1");

    ASSERT_THAT(downloads.count(), Eq(2));
}

TEST(ADownloads, DoesNotAddDownloadsIfInputFileIsEmpty)
{
    Downloads downloads;

    downloads.add("http://www.stash.com/files/1");
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