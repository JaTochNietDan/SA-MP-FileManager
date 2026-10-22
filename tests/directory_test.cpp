#include "../FileManager/directory.h"
#include <cassert>
#include <cstdio>
#include <map>

int main(int argc, char** argv) {
    assert(argc == 2);
    const std::string path = argv[1];
    assert(!DirectoryStream::open(nullptr, true));
    assert(!DirectoryStream::open("", true));
    assert(!DirectoryStream::open((path + "/missing").c_str(), true));
    assert(!DirectoryStream::open((path + "/alpha.txt").c_str(), true));

    std::unique_ptr<DirectoryStream> sorted(DirectoryStream::open(path.c_str(), true));
    std::unique_ptr<DirectoryStream> ordinary(DirectoryStream::open(path.c_str(), false));
    assert(sorted && ordinary);
    std::vector<std::string> names;
    std::map<std::string, int> sortedTypes, ordinaryTypes;
    DirectoryEntry entry;
    while (sorted->next(entry)) {
        names.push_back(entry.name);
        sortedTypes[entry.name] = entry.type;
    }
    assert(!sorted->next(entry));
    while (ordinary->next(entry)) ordinaryTypes[entry.name] = entry.type;
    assert(sortedTypes == ordinaryTypes);
    assert(std::is_sorted(names.begin(), names.end()));
    assert(sortedTypes.at("alpha.txt") == DT_REG);
    assert(sortedTypes.at("folder") == DT_DIR);
    assert(sortedTypes.count(".hidden") == 1);
    std::vector<std::string> expected = {".hidden", "Beta.txt", "alpha.txt", "empty", "folder", "zebra.txt"};
    names.erase(std::remove(names.begin(), names.end(), "."), names.end());
    names.erase(std::remove(names.begin(), names.end(), ".."), names.end());
    assert(names == expected);

    std::unique_ptr<DirectoryStream> snapshot(DirectoryStream::open(path.c_str(), true));
    FILE* added = fopen((path + "/later.txt").c_str(), "w");
    assert(added);
    fclose(added);
    while (snapshot->next(entry)) assert(entry.name != "later.txt");
    std::unique_ptr<DirectoryStream> empty(DirectoryStream::open((path + "/empty").c_str(), true));
    assert(empty);
    while (empty->next(entry)) assert(entry.name == "." || entry.name == "..");
    // Closing before exhaustion must release both native and snapshot resources.
    for (int i = 0; i < 100; ++i) {
        delete DirectoryStream::open(path.c_str(), false);
        delete DirectoryStream::open(path.c_str(), true);
    }
    puts("Directory iteration tests passed");
}
