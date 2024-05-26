#pragma once

#include "_CORE.h"

#include <memory>
#include <unordered_map>
#include <mutex>
#include <string>
#include <iostream>
#include <typeinfo>

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

inline std::string demangleTypeName(const char *name)
{
    // Platform-specific demangling logic can be added here if needed
    // For simplicity, we return the mangled name as-is
    return std::string(name);
}

template <typename T>
class TrackedSCOPE
{
  public:
    template <typename... Args>
    static std::unique_ptr<T> create(Args &&...args)
    {
        std::cout << "Creating scope for " << typeid(T).name() << std::endl;
        std::cout << "Demangled name: " << demangleTypeName(typeid(T).name()) << std::endl;
        auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
        ReferenceTracker::getInstance().addReference("SCOPE", demangleTypeName(typeid(T).name()));
        return ptr;
    }

    ~TrackedSCOPE()
    {
        std::cout << "Destroying scope for " << typeid(T).name() << std::endl;
        ReferenceTracker::getInstance().removeReference("SCOPE", demangleTypeName(typeid(T).name()));
        delete ptr_;
    }

    T *operator->() { return ptr_.get(); }
    const T *operator->() const { return ptr_.get(); }
    T &operator*() { return *ptr_; }
    const T &operator*() const { return *ptr_; }

  private:
    TrackedSCOPE() = default;
    TrackedSCOPE(const TrackedSCOPE &) = delete;
    // template <typename... Args>
    // TrackedSCOPE(Args &&...args) : ptr_(std::make_unique<T>(std::forward<Args>(args)...))
    // {
    //     std::cout << "Creating scope for " << typeid(T).name() << std::endl;
    //     std::cout << "Demangled name: " << demangleTypeName(typeid(T).name()) << std::endl;
    //     ReferenceTracker::getInstance().addReference("SCOPE", demangleTypeName(typeid(T).name()));
    // }

    std::unique_ptr<T> ptr_;
};

template <typename T>
class TrackedREF
{
  public:
    template <typename... Args>
    static std::shared_ptr<T> create(Args &&...args)
    {
        std::cout << "Creating reference to " << typeid(T).name() << std::endl;
        std::cout << "Demangled name: " << demangleTypeName(typeid(T).name()) << std::endl;
        auto ptr = std::make_shared<T>(std::forward<Args>(args)...);
        ReferenceTracker::getInstance().addReference("REF", demangleTypeName(typeid(T).name()));
        return ptr;
    }

    ~TrackedREF()
    {
        std::cout << "Destroying reference to " << typeid(T).name() << std::endl;
        ReferenceTracker::getInstance().removeReference("REF", demangleTypeName(typeid(T).name()));
        delete ptr_;
    }

    T *operator->() { return ptr_.get(); }
    const T *operator->() const { return ptr_.get(); }
    T &operator*() { return *ptr_; }
    const T &operator*() const { return *ptr_; }

  private:
    TrackedREF() = default;
    TrackedREF(const TrackedREF &) = delete;
    // template <typename... Args>
    // TrackedREF(Args &&...args): ptr_(std::make_shared<T>(std::forward<Args>(args)...))
    // {
    //     std::cout << "Creating reference to " << typeid(T).name() << std::endl;
    //     std::cout << "Demangled name: " << demangleTypeName(typeid(T).name()) << std::endl;
    //     ReferenceTracker::getInstance().addReference("REF", demangleTypeName(typeid(T).name()));
    // }

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

    // TrackedSCOPE<T> trackedScope(std::forward<Args>(args)...);
    // return trackedScope.get();

    return TrackedSCOPE<T>::create(std::forward<Args>(args)...);
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

    // TrackedREF<T> trackedRef(std::forward<Args>(args)...);
    // return trackedRef.get();

    return TrackedREF<T>::create(std::forward<Args>(args)...);
}
}