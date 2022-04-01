#pragma once

#include <cstdint>

namespace assign2_exception {

/**
 * mock the design of Exception in Java, or std::exception in C++
 *
 * In this assignment, exception is not handled by throw.
 * When you throw a exception, most of time you just throw the most-previous exception.
 * In our assignment, however, you are required to handle all exception occuring.
 * 
 * i.e., in your function, `EXCEPTION1` and `EXCEPTION2` may both occur,
 * then you should contain the information for both of them in your return value.
 * 
 * @attention record exception into @p exception: exception |= NULL_POINTER_EXCEPTION
 * @attention judge whether @p exception records specific exception: if (exception & NULL_POINTER_EXCEPTION)
 */


#define NULL_POINTER_EXCEPTION                (0x1 << 0)  ///< possible accessing to member of null pointer occurs
#define DUPLICATED_LEFT_CHILD_EXCEPTION       (0x1 << 1)  ///< the user wants to add a new child node to a father's left child, while the father has already had a left child
#define DUPLICATED_RIGHT_CHILD_EXCEPTION      (0x1 << 2)  ///< the user wants to add a new child node to a father's right child, while the father has already had a right child
#define DUPLICATED_FATHER_EXCEPTION           (0x1 << 3)  ///< the user wants to add a child node to a new father, while the child node has already had a father node
#define INVALID_CHILD_DIRECTION_EXCEPTION     (0x1 << 4)  ///< the user uses an invalid value for **child_direction** field
#define ROOTS_FATHER_EXCEPTION                (0x1 << 5)  ///< the user wants to access the father node of a root node
#define NULL_COMP_FUNCTION_EXCEPTION          (0x1 << 6)  ///< the user wants to insert/find/splay a nodes in BST, while there is no `comp` function defined for the BST
#define SPLAY_NODE_NOT_IN_TREE_EXCEPTION      (0x1 << 7)  ///< the user wants to splay a node to the root of a BST, while this node does not exist in this BST

typedef uint32_t exception;  ///< use exception as the return type, don't use the raw type uint32_t

}  // namespace assign2_exception
