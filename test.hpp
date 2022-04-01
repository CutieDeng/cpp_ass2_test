#pragma once 

#include <optional> 
#include <string> 
#include <sstream> 

// Use std::optional..., just called r_type and name test to achieve your tests! 

namespace {
    typedef std::optional<std::string> r_type; 
}

template <> 
r_type test<__COUNTER__>() {
    // 测试框架测试，测试框架是否能正常进行。
    std::cout << "框架正确性测试。" << std::endl; 
    return {}; 
}

template <> 
r_type test<__COUNTER__> () {
    // 错误测试！
    std::cout << "框架错误检测测试。" << std::endl; 
    return "测试该框架能否正确输出错误信息。"; 
}

template <> 
r_type test<__COUNTER__> () {
    // 内存泄漏测试，测试框架能否检测内存泄漏！
    std::cout << "框架 tree_node 模型对象内存控制检测测试。" << std::endl; 
    new tree_node(); 
    return {}; 
}

template <> 
r_type test<__COUNTER__> () {
    // 内存重复释放的安全检测！
    std::cout << "框架 tree_node 模型对象内存控制检测测试 2. " << std::endl; 
    tree_node *p = new tree_node(); 
    delete p; 
    delete p; 
    return {}; 
}

template <> 
r_type test<__COUNTER__> () {
    // 使用禁止的方法构造 tree_node 对象。
    std::cout << "框架特殊约束：禁用 new tree_node[] 初始化。" << std::endl; 
    tree_node *p = new tree_node[3]; 
    delete[] p; 
    return {}; 
}

template <> 
r_type test<__COUNTER__> () {
    // 从本次测试开始，开始正式进行 part 1 测试。
    std::cout << "Part 1 部分测试正式开始。" << std::endl; 

    tree_node *f = new tree_node{}; 
    tree_node *s = new tree_node{}; 

    std::cout << "构建两个 tree_node f, s; 并进行 ADD_NODE_LEFT(f, s)" << std::endl; 

    auto p = ADD_NODE_LEFT(f, s); 
    if (p) 
        return ({std::stringstream s; s << "将点连至叶子节点的左儿子位置但回报了错误代码：" << p << ". "; s.str(); }); 

    if (f -> l_child != s || s -> father != f) 
        return "连接两个节点，且调用函数成功返回——但并没有实际连接两点。"; 

    delete f; 
    delete s; 

    return {}; 
}

namespace {
    constexpr int test_number {__COUNTER__}; 
}