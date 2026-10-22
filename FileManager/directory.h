#ifndef FILEMANAGER_DIRECTORY_H
#define FILEMANAGER_DIRECTORY_H

#ifdef _WIN32
#include "dirent.h"
#else
#include <dirent.h>
#endif
#include <algorithm>
#include <cerrno>
#include <memory>
#include <string>
#include <vector>

struct DirectoryEntry {
    std::string name;
    int type;
    bool operator<(const DirectoryEntry& other) const {
        return name < other.name;
    }
};

// Sorted streams are snapshots; ordinary streams retain filesystem order.
class DirectoryStream {
    DIR* stream;
    bool sorted;
    std::vector<DirectoryEntry> entries;
    size_t position;

    DirectoryStream(DIR* stream, bool sorted)
        : stream(stream), sorted(sorted), position(0) {}
    DirectoryStream(const DirectoryStream&) = delete;
    DirectoryStream& operator=(const DirectoryStream&) = delete;

public:
    ~DirectoryStream() { if (stream) closedir(stream); }

    static DirectoryStream* open(const char* path, bool sorted) {
        if (!path || !*path) return nullptr;
        std::unique_ptr<DirectoryStream> result(new DirectoryStream(nullptr, sorted));
        result->stream = opendir(path);
        if (!result->stream) return nullptr;
        if (sorted) {
            for (;;) {
                errno = 0;
                dirent* entry = readdir(result->stream);
                if (!entry) {
                    if (errno) return nullptr;
                    break;
                }
                result->entries.push_back({entry->d_name, entry->d_type});
            }
            std::sort(result->entries.begin(), result->entries.end());
            closedir(result->stream);
            result->stream = nullptr;
        }
        return result.release();
    }

    bool next(DirectoryEntry& entry) {
        if (sorted) {
            if (position == entries.size()) return false;
            entry = entries[position++];
        } else {
            dirent* item = readdir(stream);
            if (!item) return false;
            entry = {item->d_name, item->d_type};
        }
        return true;
    }
};
#endif
