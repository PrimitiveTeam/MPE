#pragma once

#include "_CORE.h"

#include <memory>
#include <unordered_map>
#include <mutex>
#include <string>

/**
 * @file _PTRS.h
 * @brief This file contains the smart pointer aliases for the MPE engine.
 * @date 2024-05-05
 */

/**
 * @brief The Mere Primitive Engine (MPE) namespace.
 * @date 2024-05-05
 * @author Sebastian Termen
 */
namespace MPE
{
class MPE_API ReferenceTracker
{
  public:
    static ReferenceTracker &getInstance()
    {
        static ReferenceTracker instance;
        return instance;
    }

    void addReference(const std::string &type, const std::string &tag);

    void removeReference(const std::string &type, const std::string &tag);

    void displayReferences() const;

  private:
    ReferenceTracker() = default;

    mutable std::mutex mutex_;
    std::unordered_map<std::string, int> references_;
    std::unordered_map<std::string, int> totalReferences_;
};

template <typename T>
class TrackedSCOPE
{
  public:
    template <typename... Args>
    TrackedSCOPE(Args &&...args) : ptr_(std::make_unique<T>(std::forward<Args>(args)...))
    {
        ReferenceTracker::getInstance().addReference("SCOPE", typeid(T).name());
    }

    ~TrackedSCOPE() { ReferenceTracker::getInstance().removeReference("SCOPE", typeid(T).name()); }

    T *operator->() { return ptr_.get(); }
    const T *operator->() const { return ptr_.get(); }
    T &operator*() { return *ptr_; }
    const T &operator*() const { return *ptr_; }

  private:
    std::unique_ptr<T> ptr_;
};

template <typename T>
class TrackedREF
{
  public:
    template <typename... Args>
    TrackedREF(Args &&...args) : ptr_(std::make_shared<T>(std::forward<Args>(args)...))
    {
        ReferenceTracker::getInstance().addReference("REF", typeid(T).name());
    }

    ~TrackedREF() { ReferenceTracker::getInstance().removeReference("REF", typeid(T).name()); }

    T *operator->() { return ptr_.get(); }
    const T *operator->() const { return ptr_.get(); }
    T &operator*() { return *ptr_; }
    const T &operator*() const { return *ptr_; }

  private:
    std::shared_ptr<T> ptr_;
};

/**
 * @brief Alias template for std::unique_ptr to manage the lifecycle of
 * individual objects.
 * @details SCOPE automatically deletes the object it points to when the SCOPE
 * variable goes out of scope.
 * @date 2024-05-05
 * @author Sebastian Termen
 */
template <typename T>
using SCOPE = std::unique_ptr<T>;

/**
 * @brief Factory function to create a SCOPE smart pointer instance.
 * @details This function simplifies the creation of unique_ptr instances with
 * automatic type deduction and argument forwarding.
 * @date 2024-05-05
 * @author Sebastian Termen
 */
template <typename T, typename... Args>
constexpr SCOPE<T> NEWSCOPE(Args &&...args)
{
    /**
     * @brief std::make_unique is used to construct an object and wrap it in a
     * std::unique_ptr (SCOPE).
     * @details It provides exception safety by ensuring that memory allocation
     * and object construction are atomic operations.
     * @see https://en.cppreference.com/w/cpp/memory/unique_ptr/make_unique
     */
    // return std::make_unique<T>(std::forward<Args>(args)...);
    return TrackedSCOPE<T>(std::forward<Args>(args)...);
}

/**
 * @brief Alias template for std::shared_ptr to manage shared ownership of
 * objects.
 * @details REF allows multiple pointers to the same object, with the object
 * being destroyed once the last REF is destroyed or reset.
 * @date 2024-05-05
 * @author Sebastian Termen
 */
template <typename T>
using REF = std::shared_ptr<T>;

/**
 * @brief Factory function to create a REF smart pointer instance.
 * @details This function simplifies the creation of shared_ptr instances with
 * automatic type deduction and argument forwarding.
 * @date 2024-05-05
 * @author Sebastian Termen
 */
template <typename T, typename... Args>
constexpr REF<T> NEWREF(Args &&...args)
{
    /**
     * @brief std::make_shared is used to construct an object and wrap it in a
     * std::shared_ptr (REF).
     * @details It is more efficient than using std::shared_ptr directly as it
     * allocates memory for the object and the control block in a single memory
     * block.
     * @see https://en.cppreference.com/w/cpp/memory/shared_ptr/make_shared
     */
    // return std::make_shared<T>(std::forward<Args>(args)...);
    return TrackedREF<T>(std::forward<Args>(args)...);
}
}