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
    std::cout << "本次测试为框架正确性测试。" << std::endl; 
    std::cout << "其应当回答：通过测试。 " << std::endl; 
    return {}; 
}

template <> 
r_type test<__COUNTER__> () {
    // 错误测试！
    std::cout << "本次测试为框架错误检测测试。" << std::endl; 
    std::cout << "其应当返回测试失败并回报相应的错误信息。" << std::endl; 
    return "测试该框架能否正确输出错误信息。"; 
}

template <> 
r_type test<__COUNTER__> () {
    // 内存泄漏测试，测试框架能否检测内存泄漏！
    std::cout << "框架 tree_node 模型对象内存控制检测测试。" << std::endl; 
    std::cout << "其应检测出内存泄漏情形。" << std::endl; 

    std::cout << "使用 new tree_node(); 构造一个 tree_node 节点，并忘记释放它。" << std::endl; 
    new tree_node(); 

    return {}; 
}

template <> 
r_type test<__COUNTER__> () {
    // 内存重复释放的安全检测！
    std::cout << "框架 tree_node 模型对象内存控制检测测试。" << std::endl; 
    std::cout << "其应检测出危险的内存控制操作。" << std::endl; 

    std::cout << "tree_node *p = new tree_node(); 构造一个 tree_node 节点。" << std::endl; 
    tree_node *p = new tree_node(); 
    std::cout << "两次执行 delete p; " << std::endl; 
    delete p; 
    delete p; 
    return {}; 
}

template <> 
r_type test<__COUNTER__> () {
    // 使用禁止的方法构造 tree_node 对象。
    std::cout << "框架特殊约束：禁用 new tree_node[] 初始化测试." << std::endl; 
    
    std::cout << "执行代码 tree_node *p = new tree_node[3]; " << std::endl; 
    tree_node *p = new tree_node[3]; 

    std::cout << "执行代码 delete[] p"; 
    delete[] p; 

    return {}; 
}

template <> 
r_type test<__COUNTER__> () {
    std::cout << "异常抛出测试，测试能否通过抛出 std::string 异常来退出执行该方法。" << std::endl; 
    std::cout << "请不要使用 throw \"a sentence\" 的方法抛出异常！其不会被本框架捕获和处理！" << std::endl; 

    throw std::string {"我是一个 std::string 异常。"}; 

    std::cout << "此 statement 在异常抛出后面。" << std::endl; 
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
    
    std::cout << "回收所有新开辟的堆内存。" << std::endl; 
    delete p; 
    delete rightson; 
    delete rightson2; 

    if (!r && (r2 == DUPLICATED_RIGHT_CHILD_EXCEPTION)) {
        return {}; 
    } else {
        if (r) 
            return "运行 ADD_NODE_RIGHT(p, rightson) 过程遭遇错误。"; 
        if (!(r2 & DUPLICATED_RIGHT_CHILD_EXCEPTION)) 
            return "运行 ADD_NODE_RIGHT(p, rightson2) 时没有意识到 duplicate 的错误发生。"; 
        if (r2 & ~DUPLICATED_RIGHT_CHILD_EXCEPTION)
            return "运行 ADD_NODE_RIGHT(p, rightson2) 时汇报了额处的错误。"; 
        return "未知的错误"; 
    }
}

template <> 
r_type test<__COUNTER__>() {
    typedef tree_node *ptr; 

    ptr p = new tree_node{}; 
    ptr leftson = new tree_node{}; 
    ptr leftson2 = new tree_node{}; 

    std::cout << "DUPLICATED LEFT CHILD EXCEPTION 测试" <<std::endl; 
    std::cout << "构造三个空节点 p, leftson, leftson2. " << std::endl; 

    auto r = ADD_NODE_LEFT(p, leftson); 
    auto r2 = ADD_NODE_LEFT(p, leftson2); 

    std::cout << "调用 ADD_NODE_LEFT(p, leftson), 再次调用 ADD_NODE_LEFT(p, leftson2). " 
        << std::endl; 
    
    std::cout << "回收所有新开辟的堆内存。" << std::endl; 
    delete p; 
    delete leftson; 
    delete leftson2; 

    if (!r && (r2 == DUPLICATED_LEFT_CHILD_EXCEPTION)) {
        return {}; 
    } else {
        if (r) 
            return "运行 ADD_NODE_LEFT(p, leftson) 过程遭遇错误。"; 
        if (!(r2 & DUPLICATED_LEFT_CHILD_EXCEPTION)) 
            return "运行 ADD_NODE_LEFT(p, leftson2) 时没有意识到 duplicate 的错误发生。"; 
        if (r2 & ~DUPLICATED_LEFT_CHILD_EXCEPTION)
            return "运行 ADD_NODE_LEFT(p, leftson2) 时汇报了额处的错误。"; 
        return "未知的错误"; 
    }
}

template <> 
r_type test<__COUNTER__>() {

    std::cout << "DUPLICATED FATHER EXCEPTION 测试" << std::endl; 
    
    std::cout << "初始化三个节点 p, f, f2. " << std::endl; 
    tree_node *p = new tree_node{}; 
    tree_node *f = new tree_node{}; 
    tree_node *f2 = new tree_node{}; 

    std::cout << "执行 ADD_NODE_LEFT(f, p), 再执行 ADD_NODE_RIGHT(f2, p)" << std::endl; 
    auto a1 = ADD_NODE_LEFT(f, p); 
    auto a2 = ADD_NODE_RIGHT(f2, p); 

    delete f; 
    delete f2; 
    delete p; 

    if (a1) {
        return "执行 ADD_NODE_LEFT(f, p) 过程中被拒绝。"; 
    } else if (!a2) {
        return "错误执行成功了 ADD_NODE_RIGHT(f2, p). "; 
    } else if (a2 & DUPLICATED_FATHER_EXCEPTION) {
        if (a2 != DUPLICATED_FATHER_EXCEPTION)
            return "ADD_NODE_RIGHT(f2, p) 方法汇报了更多异常。"; 
        else 
            return {}; 
    } else 
        return "ADD_NODE_RIGHT(f2, p) 方法汇报了其它异常。"; 
}

template <> 
r_type test<__COUNTER__>() {
    std::cout << "NULL POINTER EXCEPTION 测试" << std::endl; 

    std::cout << "构造了两个节点 p, s. " << std::endl; 
    tree_node *p = new tree_node{}; 
    tree_node *s = new tree_node{}; 

    std::cout << "执行 ADD_NODE_LEFT(p, s), 再执行 ADD_NODE_LEFT(nullptr, s). " << std::endl; 

    auto a1 = ADD_NODE_LEFT(p, s); 

    // 该操作将 nullptr 转化为一个左值，以避免一些同学使用了更苛性的语法检查编译手段导致无法通过 compile. 
    tree_node *s2 = nullptr; 
    auto a2 = ADD_NODE_LEFT(s2, s); 

    delete p; 
    delete s; 

    if (a1) {
        throw "执行 ADD_NODE_LEFT(p, s) 过程中遭遇错误。"; 
    } else if (a2 & NULL_POINTER_EXCEPTION) {
        if (a2 & ~(NULL_POINTER_EXCEPTION | DUPLICATED_FATHER_EXCEPTION)) 
            return ({std::stringstream s; s << "执行 ADD_NODE_LEFT(nullptr, s) 返回了更多的错误信息。其返回的错误码为：" << a2 << ". "; s.str(); });  
        return {}; 
    } else 
        return "执行 ADD_NODE_LEFT(nullptr, s) 过程没有返回 NULL POINTER EXCEPTION. "; 
}

namespace {
    constexpr int test_number {__COUNTER__}; 
}