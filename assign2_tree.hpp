#pragma once

#include <cstdint>
#include <string> 
#include <unordered_set> 

struct tree_node; 

inline thread_local std::unordered_set<void *> records; 
inline thread_local std::unordered_set<void *> bst_record; 

struct tree_node {
    tree_node *father;
    tree_node *l_child, *r_child;

    uint32_t node_count;  ///< the number of occurrences of a certain data (repetation count)
    uint32_t tree_count;  ///< the size of the subtree (including the root)

    uint64_t data;  ///< only save 8-bytes width memory for the data of any representation

    inline void *operator new (size_t s) {
        auto p {malloc(s)}; 
        records.insert(p); 
        return p; 
    }

    inline void *operator new[] (size_t v) noexcept(false) {
        throw std::string {"本次测试禁止使用 new[] 创建 tree_node 对象数组。"}; 
    }

    inline void operator delete (void *p) noexcept(false) {
        if (!records.count(p)) 
            throw std::string{"试图释放非法的内存段。"}; 
        records.erase(p); 
        free(p); 
    }

    inline void operator delete[] (void *p) noexcept (false) {
        throw std::string {"不应使用 delete[] 操作。"}; 
    }
};

struct BST {
    tree_node *root;

    /**
     * (pointer to a function) compare two data, represented by uint64_t, mentioned in @link{tree_node#data}
     *
     * @attention receiveing two uint64_t doesn't promise you can straightly compare the numeric value of them, but you should specify a rule to compare them
     * @returns (0)       if two data fields equal
     * @returns (int > 0) if the first data field is greater than the second one
     * @returns (int < 0) if the first data field is smaller than the second one
     */
    int (*comp)(uint64_t, uint64_t);

    inline void *operator new (size_t s) {
        auto p {malloc(s)}; 
        bst_record.insert(p); 
        return p; 
    }

    inline void *operator new[] (size_t v) noexcept(false) {
        throw std::string {"本次测试禁止使用 new[] 创建 bst 对象数组。"}; 
    }

    inline void operator delete (void *p) noexcept(false) {
        if (!bst_record.count(p)) 
            throw std::string{"试图释放非法的内存段。"}; 
        bst_record.erase(p); 
        free(p); 
    }

    inline void operator delete[] (void *p) noexcept (false) {
        throw std::string {"不应使用 delete[] 操作。"}; 
    }
};