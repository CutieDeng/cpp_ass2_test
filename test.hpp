#pragma once 

namespace {
    typedef std::optional<std::string> r_type; 

    // 格式化函数，支持快速格式化内容。
    // 调用方法大致如下：format("Hello World"); 得到一个 Hello World 字符串。
    // 等价地调用还有： format ("{} {}", "Hello", "World"); 
    // 欢迎调戏。
    template <typename ...Args> 
    std::string format(std::string_view , Args const & ...); 

    // 该方法用于格式化 exception 信息，你可以使用该方法使一个 assign2_exception::exception 转化成一个
    // 人类可读的字符串。 
    // 当 exception 没有异常信息时，该方法会返回一个空字符串。
    std::string transfer_exception(assign2_exception::exception ); 

    // check_exception 用于判断两个异常类型是否完全相同。
    // 如果完全相同，其将会返回一个空对象，表示没有错误信息输出。
    // 如果存在不同，其将会返回一个具体描述为什么不同，两个异常实例不同点在哪的信息以便于被测进行 DEBUG. 
    r_type check_exception(assign2_exception::exception actual, assign2_exception::exception expect); 

    r_type check_int(int actual, int expect); 

    // inert_data 聚合了插入 BST 的操作。
    // 你可以使用该方法快速将一组数据一次性插入到一个 BST 中。
    // 它的返回值是一个变长数组，用以依顺序记录每次使用 insert_into_BST 的返回值。
    // 本方法不期望在调用 insert_into_BST 的过程中得到一个异常回复。
    std::vector<tree_node *> insert_data(BST &, std::initializer_list<uint64_t> const &); 

    // 该方法用于递归地删除一棵树。
    // 调用该方法可以将一树 BST 上的所有节点都删除，并释放其所有节点的内存。
    // insert 了太多节点不知道怎么释放？就用它吧！
    void destruct_tree(BST &); 

    // 求取一棵树的数据数？
    // 直接无脑 bst.root.tree_count? 
    // 不如用用 size of tree 吧，有较避免 null pointer exception~. 
    uint32_t size_of_tree(BST &); 

    // 使用该方法来检查你的 BST 的正确性：
    // 1. tree_count 结果的正确性
    // 2. 是否满足 comp 函数计算结果的正确性
    // 3. 各节点信息是否具有一致性 
    // 检查成功则返回空对象，失败会返回一个包含错误信息的字符串。
    r_type check_bst(BST const &); 
    
    // 标准的比较器函数
    int compare_std(uint64_t, uint64_t ); 

    // 对标准比较器取个反吧。
    int compare_reverse(uint64_t, uint64_t ); 

    // 使用如下三个 tree_node 构建一个小二叉树。
    r_type build_with_nodes(tree_node &father, tree_node &l_child, tree_node &r_child); 
    
    // 全等比较器。
    int compare_equality(uint64_t, uint64_t ); 
    
    // 模十比较器. 
    int compare_ones(uint64_t a, uint64_t b); 

    // 复数比较器
    int compare_complex(uint64_t, uint64_t ); 

    // 创建虚数，以 uint64_t 格式表示。
    uint64_t create_complex(uint32_t real, uint32_t imaginary); 

    // 约束该 bst 的高度至多为 limits. 
    // 有根树的高度为 1.  
    r_type upper_limit_height(BST const &, uint32_t ); 

    // 快速将指定数据的点旋转至 bst 的根节点位置。
    r_type rotate_to_top(BST &, uint64_t ); 
}

#include "tool.hpp"

// 下面则包含了测试包。

// 框架自测试包 
// #include "test_frame.cpp" 

// 曾同学提供的测试包
#include "test_zlx.cpp" 

// 标准 part i 部分测试包
#include "test_parti.cpp" 

// 标准 part ii 部分测试包
#include "test_partii.cpp"

// 标准 part iii 部分测试包
#include "test_partiii.cpp"

// 标准 part iv 部分测试包
#include "test_partiv.cpp"

// 标准 part iv 部分测试包
#include "test_partv.cpp"

// deprecated 测试包
// #include "test_else.cpp"

namespace {
    constexpr int test_number {__COUNTER__}; 
}