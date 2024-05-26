#include "_PTRS.h"
#include "MPEPCH.h"

namespace MPE
{
void ReferenceTracker::addReference(const std::string &type, const std::string &tag)
{
    std::lock_guard<std::mutex> lock(mutex_);
    references_[tag]++;
    totalReferences_[type]++;
}

void ReferenceTracker::removeReference(const std::string &type, const std::string &tag)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (--references_[tag] == 0)
    {
        references_.erase(tag);
    }
    totalReferences_[type]--;
}

void ReferenceTracker::displayReferences() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    std::cout << "Reference counts by tag:\n";
    for (const auto &entry : references_)
    {
        std::cout << entry.first << ": " << entry.second << "\n";
    }

    std::cout << "Total reference counts by type:\n";
    for (const auto &entry : totalReferences_)
    {
        std::cout << entry.first << ": " << entry.second << "\n";
    }
}
}