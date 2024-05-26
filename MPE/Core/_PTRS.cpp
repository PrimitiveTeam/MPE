#include "_PTRS.h"
#include "MPEPCH.h"

#include "MPE/Log/GlobalLog.h"

namespace MPE
{
void ReferenceTracker::addReference(const std::string &type, const std::string &tag)
{
    std::lock_guard<std::mutex> lock(mutex_);
    references_[type + "::" + tag]++;
    totalReferences_[type]++;
}

void ReferenceTracker::removeReference(const std::string &type, const std::string &tag)
{
    std::lock_guard<std::mutex> lock(mutex_);
    references_[type + "::" + tag]--;
    totalReferences_[type]--;
    if (references_[type + "::" + tag] == 0)
    {
        references_.erase(type + "::" + tag);
    }
    if (totalReferences_[type] == 0)
    {
        totalReferences_.erase(type);
    }
}

void ReferenceTracker::displayReferences() const
{
    std::lock_guard<std::mutex> lock(mutex_);

    std::cout << "Current References:" << std::endl;
    for (const auto &ref : references_)
    {
        if (ref.first.find("SCOPE") != std::string::npos)
        {
            std::cout << "SCOPE - " << ref.first << ": " << ref.second << std::endl;
        }
        else if (ref.first.find("REF") != std::string::npos)
        {
            std::cout << "REF - " << ref.first << ": " << ref.second << std::endl;
        }
        else
        {
            std::cout << ref.first << ": " << ref.second << std::endl;
        }
    }

    std::cout << "Total References by Type:" << std::endl;
    int totalScopeReferences = 0;
    int totalRefReferences = 0;
    for (const auto &totalRef : totalReferences_)
    {
        if (totalRef.first.find("SCOPE") != std::string::npos)
        {
            totalScopeReferences += totalRef.second;
        }
        else if (totalRef.first.find("REF") != std::string::npos)
        {
            totalRefReferences += totalRef.second;
        }
        else
        {
            std::cout << totalRef.first << ": " << totalRef.second << std::endl;
        }
    }

    std::cout << "SCOPE: " << totalScopeReferences << std::endl;
    std::cout << "REF: " << totalRefReferences << std::endl;
}
}