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
    std::cout << "框架特殊约束：禁用 new tree_node[] 初始化测试." << std::endl; 
    tree_node *p = new tree_node[3]; 
    delete[] p; 
    return {}; 
}

template <> 
r_type test<__COUNTER__> () {
    // new 方法的使用建议。

    std::cout << "本测试方法为环境测试，即测试本机环境下的一些代码的运行结果和情况。" << std::endl; 

    tree_node *p = new tree_node; 

    std::cout << "执行代码 tree_node *p = new tree_node; " << std::endl; 
    std::cout << "试输出 tree_node 的信息初始化情形：" << 
        "p.father = " << p -> father << ", p.l_child = " << p -> l_child 
        << ", p.r_child = " << p -> r_child << ". " << std::endl; 

    tree_node *p2 = new tree_node(); 
    delete p; 
    p = p2; 
    std::cout << "执行代码 tree_node *p = new tree_node(); " << std::endl; 
    std::cout << "试输出 tree_node 的信息初始化情形：" << 
        "p.father = " << p -> father << ", p.l_child = " << p -> l_child 
        << ", p.r_child = " << p -> r_child << ". " << std::endl; 

    tree_node *p3 = new tree_node{}; 
    p = p3; 
    std::cout << "执行代码 tree_node *p = new tree_node{}; " << std::endl; 
    std::cout << "试输出 tree_node 的信息初始化情形：" << 
        "p.father = " << p -> father << ", p.l_child = " << p -> l_child 
        << ", p.r_child = " << p -> r_child << ". " << std::endl; 
    
    std::cout << "请根据你的结果考虑好你的初始化方式及实际代码中的对象构造方式。" << std::endl; 

    delete p2; 
    delete p3; 

    return {}; 
}

template <> 
r_type test<__COUNTER__> () {
    // 从本次测试开始，开始正式进行 part 1 测试。
    std::cout << "Part 1 部分测试正式开始。" << std::endl; 

    tree_node *f = new tree_node{}; 
    tree_node *s = new tree_node{}; 

    std::cout << "构建两个 tree_node f, s; " << std::endl; 
    
    if (f -> l_child || f -> r_child || f -> father) 
        return "节点 f 初始化错误。"; 
    
    if (s -> l_child || s -> r_child || s -> father) 
        return "节点 s 初始化错误。"; 

    std::cout << "进行 ADD_NODE_LEFT(f, s)" << std::endl; 

    auto p = ADD_NODE_LEFT(f, s); 
    if (p) 
        return ({std::stringstream s; s << "将点连至叶子节点的左儿子位置但回报了错误代码：" << p << ". "; s.str(); }); 

    if (f -> l_child != s || s -> father != f) 
        return "连接两个节点，且调用函数成功返回——但并没有实际连接两点。"; 
    if (f -> father) 
        return "父节点的父亲被设为非空指针。"; 
    if (f -> r_child) 
        return "父节点存在非预期的右儿子节点。"; 
    if (s -> l_child || s -> r_child) 
        return "子节点不是叶子节点。"; 

    delete f; 
    delete s; 

    return {}; 
}

template <> 
r_type test<__COUNTER__>() {
    tree_node *f = new tree_node{}; 
    tree_node *s = new tree_node{}; 

    std::cout << "构建两个 tree_node f, s; " << std::endl; 
    
    if (f -> l_child || f -> r_child || f -> father) 
        return "节点 f 初始化错误。"; 
    
    if (s -> l_child || s -> r_child || s -> father) 
        return "节点 s 初始化错误。"; 

    std::cout << "进行 ADD_NODE_RIGHT(f, s)" << std::endl; 

    auto p = ADD_NODE_RIGHT(f, s); 
    if (p) 
        return ({std::stringstream s; s << "将点连至叶子节点的右儿子位置但回报了错误代码：" << p << ". "; s.str(); }); 

    if (f -> r_child != s || s -> father != f) 
        return "连接两个节点，且调用函数成功返回——但并没有实际连接两点。"; 
    if (f -> father) 
        return "父节点的父亲被设为非空指针。"; 
    if (f -> l_child) 
        return "父节点存在非预期的左儿子节点。"; 
    if (s -> l_child || s -> r_child) 
        return "子节点不是叶子节点。"; 

    delete f; 
    delete s; 

    return {}; 
}

template <> 
r_type test<__COUNTER__>() {
    typedef tree_node *ptr; 

    ptr p = new tree_node{}; 
    ptr rightson = new tree_node{}; 
    ptr rightson2 = new tree_node{}; 

    std::cout << "DUPLICATED RIGHT CHILD EXCEPTION 测试" <<std::endl; 
    std::cout << "构造三个空节点 p, rightson, rightson2. " << std::endl; 

    auto r = ADD_NODE_RIGHT(p, rightson); 
    auto r2 = ADD_NODE_RIGHT(p, rightson2); 

    std::cout << "调用 ADD_NODE_RIGHT(p, rightson), 再次调用 ADD_NODE_RIGHT(p, rightson2). " 
        << std::endl; 
    
    delete p; 
    delete rightson; 
    delete rightson2; 

    if (!r && (r2 & DUPLICATED_RIGHT_CHILD_EXCEPTION)) {
        return {}; 
    } else {
        if (r) 
            return "运行 ADD_NODE_RIGHT(p, rightson) 过程遭遇错误。"; 
        if (!(r2 & DUPLICATED_RIGHT_CHILD_EXCEPTION)) 
            return "运行 ADD_NODE_RIGHT(p, rightson2) 时没有意识到 duplicate 的错误发生。"; 
        return "未知的错误"; 
    }
}

namespace {
    constexpr int test_number {__COUNTER__}; 
}