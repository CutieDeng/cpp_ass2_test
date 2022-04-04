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
        return "执行 ADD_NODE_LEFT(p, s) 过程中遭遇错误。"; 
    } else if (a2 & NULL_POINTER_EXCEPTION) {
        if (a2 & ~(NULL_POINTER_EXCEPTION | DUPLICATED_FATHER_EXCEPTION)) 
            return ({std::stringstream s; s << "执行 ADD_NODE_LEFT(nullptr, s) 返回了更多的错误信息。其返回的错误码为：" << a2 << ". "; s.str(); });  
        return {}; 
    } else 
        return "执行 ADD_NODE_LEFT(nullptr, s) 过程没有返回 NULL POINTER EXCEPTION. "; 
}

template <> 
r_type test<__COUNTER__>() {
    // 该测试来自曾令玺同学。 

    std::cout << "NULL POINTER EXCEPTION 测试" << std::endl; 

    std::cout << "执行 ADD_NODE_LEFT(nullptr, nullptr). " << std::endl; 

    auto e = ADD_NODE_LEFT(nullptr, nullptr); 
    if (e & NULL_POINTER_EXCEPTION) {
        // 检测出了空指针异常 
        if (e == NULL_POINTER_EXCEPTION)    
            // 正确的错误码. 
            return {}; 
        else 
            // 还检测出了额外的错误内容。
            return "检测出了额外的错误内容。"; 
    } else {
        return "没能检测出其对应的 NULL POINTER EXCEPTION. "; 
    }
}

template <> 
r_type test<__COUNTER__>() {
    std::cout << "进行 ROOTS FATHER EXCEPTION 测试" << std::endl; 

    std::cout << "构建节点 p 并调用 judge_child_direction(p) " << std::endl; 
    tree_node *p = new tree_node(); 
    int direction; 
    auto e = judge_child_direction(p, &direction); 

    // if (e == ROOTS_FATHER_EXCEPTION) 
    //     // 正确判断当前的异常情形
    //     return {}; 
    // else  
    //     return "没能正确返回异常类型，希望返回的异常类型为 ROOTS_FATHER_EXCEPTION. "; 

    delete p; 
    
    // 实验性方法：比对答案是否正确并进行输出..
    return check_exception(e, ROOTS_FATHER_EXCEPTION); 
}

template <> 
r_type test<__COUNTER__>() {
    std::cout << "进行 Insert to BST 测试" << std::endl; 

    std::cout << "构建 BST, 并试向其中插入值为 1, 2, 3, 4, 5 节点。" << std::endl; 
    BST bst{.comp = compare_std};
    auto g = insert_data(bst, {1, 2, 3, 4, 5}); 

    std::cout << "正在比对 bst 的 size(大小) 值。" << std::endl; 
    auto s = size_of_tree(bst); 
    for (auto ga: g) 
        delete ga; 
    
    return check_int(s, 5); 
}

template <> 
r_type test<__COUNTER__>() {
    std::cout << "进行 Duplicated Insert to BST 测试" << std::endl; 

    std::cout << "构建 BST, 并试向其中插入值为 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 13, 8, 5, 3, 2 各节点。" << std::endl; 

    BST bst{.comp = compare_std}; 
    insert_data(bst, {1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 13, 8, 5, 3, 2}); 

    std::cout << "正在比对 bst 的 size 值，并递归删除该 BST. " << std::endl; 
    auto s = size_of_tree(bst); 
    destruct_tree(bst); 

    return check_int(s, 17); 
}

template <> 
r_type test<__COUNTER__>() {
    std::cout << "进行 Insert to BST 时的 Null Pointer Exception 测试" << std::endl;

    std::cout << "构建 BST 且不初始化, 并向其中依次插入 21 节点. " << std::endl; 

    BST bst {}; 
    tree_node *store {}; 
    if (auto e = insert_into_BST(&bst, 21, &store); e != NULL_POINTER_EXCEPTION) {
        std::cout << "insert into BST 返回了错误的异常信息。" << std::endl; 
        return check_exception(e, NULL_POINTER_EXCEPTION); 
    }

    return {}; 
}

namespace {
    constexpr int test_number {__COUNTER__}; 
}