#pragma once

#include <cstdint>

struct tree_node {
    tree_node *father;
    tree_node *l_child, *r_child;

    uint32_t node_count;  ///< the number of occurrences of a certain data (repetation count)
    uint32_t tree_count;  ///< the size of the subtree (including the root)

    uint64_t data;  ///< only save 8-bytes width memory for the data of any representation
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
};
