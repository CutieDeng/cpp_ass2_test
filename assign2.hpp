#pragma once

#include "assign2_exception.hpp"
#include "assign2_tree.hpp"

#define CHILD_DIRECTION_LEFT 0
#define CHILD_DIRECTION_RIGHT 1

#define ADD_NODE_LEFT(father, child) \
    add_node(father, child, CHILD_DIRECTION_LEFT)

#define ADD_NODE_RIGHT(father, child) \
    add_node(father, child, CHILD_DIRECTION_RIGHT)


/**
 * add node @p child to @p father 's corresponding child according to the @p child_direction
 * 
 * if @p child_direction equals @link{CHILD_DIRECTION_LEFT}, add @p child to @p father 's left child
 * if @p child_direction equals @link{CHILD_DIRECTION_RIGHT}, add @p child to @p father 's right child
 * 
 * @todo task 1, 20 pts
 * 
 * @exception assign2_exception::NULL_POINTER_EXCEPTION
 * @exception assign2_exception::DUPLICATED_LEFT_CHILD_EXCEPTION
 * @exception assign2_exception::DUPLICATED_RIGHT_CHILD_EXCEPTION
 * @exception assign2_exception::DUPLICATED_FATHER_EXCEPTION
 * @exception assign2_exception::INVALID_CHILD_DIRECTION_EXCEPTION
 */
assign2_exception::exception add_node(tree_node *father, tree_node *child, int child_direction);

/**
 * judge whether the node @p node is the left or right child of its father, and store the result to @p child_direction
 * 
 * @todo task 2, 15 pts
 * 
 * @exception assign2_exception::NULL_POINTER_EXCEPTION
 * @exception assign2_exception::ROOTS_FATHER_EXCEPTION
 */
assign2_exception::exception judge_child_direction(tree_node *node, int *child_direction);

/**
 * insert specific @p data into @p bst, according to the @link{BST#comp(uint64_t, uint64_t)} function
 * 
 * @todo task 3, 20 pts
 * 
 * @exception assign2_exception::NULL_POINTER_EXCEPTION
 * @exception assign2_exception::NULL_COMP_FUNCTION_EXCEPTION
 */
assign2_exception::exception insert_into_BST(BST *bst, uint64_t data, tree_node **inserted_node);

/**
 * find specific data in the BST, and storing the target tree node into ans
 * 
 * @todo task 4, 20 pts
 * 
 * @exception assign2_exception::NULL_POINTER_EXCEPTION
 * @exception assign2_exception::NULL_COMP_FUNCTION_EXCEPTION
 */
assign2_exception::exception find_in_BST(BST *bst, uint64_t data, tree_node **target_node);

/**
 * splay tree node @p node to the root of binary search tree if @p node is in @p bst
 * 
 * @attention all the exceptions should be handled in Part One
 * 
 * @todo task 5, 30 pts
 * 
 * @exception assign2_exception::NULL_POINTER_EXCEPTION
 * @exception assign2_exception::NULL_COMP_FUNCTION_EXCEPTION
 * @exception assign2_exception::SPLAY_NODE_NOT_IN_TREE_EXCEPTION
 */
assign2_exception::exception splay(BST *bst, tree_node *node);
