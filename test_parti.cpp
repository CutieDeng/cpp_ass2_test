template <> 
r_type test<__COUNTER__> () {
    // 从本次测试开始，开始正式进行 part 1 测试。
    std::cout << "开始 PART 1 测试。" << std::endl; 
    
    // 本次测试只检查 ADD NODE LEFT 的返回值是否正确。希望得到的返回值为 0. 
    std::cout << "构造两个 tree_node 并执行 ADD NODE LEFT 方法。" << std::endl; 

    tree_node f{}, r{}; 
    auto p = ADD_NODE_LEFT(&f, &r); 

    if (p) 
        return format("方法 ADD NODE LEFT 返回了异常信息：{}. ", transfer_exception(p)); 
    //    return ({std::stringstream s; s << "将点连至叶子节点的左儿子位置但回报了错误代码：" << p << ". "; s.str(); }); 

    return {}; 
}

template <> 
r_type test<__COUNTER__>() {
    // 测试 ADD NODE RIGHT 方法能否正常运行。 

    std::cout << "构造两个 tree_node 并执行 ADD NODE RIGHT 方法。" << std::endl; 
    tree_node f{}, r{}; 
    
    if (auto p = ADD_NODE_RIGHT(&f, &r); p)
        return format("方法 ADD NODE RIGHT 返回了异常信息：{}. ", transfer_exception(p)); 

    return {}; 
}

template <> 
r_type test<__COUNTER__>() {
    // 同时测试 ADD NODE LEFT, ADD NODE RIGHT 方法的正常运行。

    std::cout << "构造三个 tree_node 并将其构建成一个小二叉树。" << std::endl; 
    tree_node f{}, l{}, r{}; 
    
    return build_with_nodes(f, l, r); 
}

template <> 
r_type test<__COUNTER__>() {
    // 测试空指针异常，当你试图为一个点添加空左节点时，其应当返回 NULL POINTER EXCEPTION. 

    std::cout << "构建一个 tree_node 并添加左节点 nullptr. " << std::endl; 
    tree_node f{}; 

    return check_exception(ADD_NODE_LEFT(&f, nullptr), NULL_POINTER_EXCEPTION);
}

template <> 
r_type test<__COUNTER__>() {
    // 测试为一个点添加空右节点时返回 NULL POINTER EXCEPTION. 

    std::cout << "构建一个 tree_node 并添加右节点 nullptr. " << std::endl; 
    tree_node f{}; 

    return check_exception(ADD_NODE_RIGHT(&f, nullptr), NULL_POINTER_EXCEPTION); 
}

template <> 
r_type test<__COUNTER__>() {
    // 将一个节点添加为 nullptr 的左儿子时返回 NULL POINTER EXCEPTION. 
    
    std::cout << "构建一个 tree_node, 并调用 ADD NODE LEFT(nullptr, node) 方法。" << std::endl; 
    tree_node f{}; 

    return check_exception(ADD_NODE_LEFT(nullptr, &f), NULL_POINTER_EXCEPTION); 
}

template <> 
r_type test<__COUNTER__>() {
    // 将一个节点添加为 nullptr 的右儿子时应返回 NULL POINTER EXCEPTION. 

    std::cout << "构建一个 tree_node, 并调用 ADD NODE RIGHT(nullptr, node) 方法。" << std::endl; 
    tree_node f{}; 

    return check_exception(ADD_NODE_RIGHT(nullptr, &f), NULL_POINTER_EXCEPTION); 
}

template <> 
r_type test<__COUNTER__>() {
    // Duplicated Father EXCEPTION 测试
    
    std::cout << "构建一个 tree_node 并为其增加父节点后调用 ADD NODE LEFT(nullptr, node) 方法。" << std::endl; 

    tree_node node{}, f{}; 
    ADD_NODE_LEFT(&f, &node); 

    return check_exception(ADD_NODE_LEFT(nullptr, &node), NULL_POINTER_EXCEPTION | DUPLICATED_FATHER_EXCEPTION); 
}

template <> 
r_type test<__COUNTER__>() {
    // Null Father Exception 测试. 

    std::cout << "构建一个 tree_node 并调用 ADD NODE LEFT(nullptr, node) 为其设置父节点。" << std::endl; 

    tree_node node{}; 

    return check_exception(ADD_NODE_LEFT(nullptr, &node), NULL_POINTER_EXCEPTION); 
}

template <> 
r_type test<__COUNTER__>() {
    // Null pointer and Child Direct Error Exception .

    std::cout << "直接调用 add_node(nullptr, nullptr, 2). " << std::endl; 

    return check_exception(add_node(nullptr, nullptr, 2), NULL_POINTER_EXCEPTION | INVALID_CHILD_DIRECTION_EXCEPTION); 
}

template <> 
r_type test<__COUNTER__>() {
    // Normal Node with Direct Error Exception. 
    // 这可能是一个不合理的测试点 emm. 

    std::cout << "构建 tree_node 并执行 add_node(node, node, 2). " << std::endl; 
    tree_node t{}; 

    return check_exception(add_node(&t, &t, 2), INVALID_CHILD_DIRECTION_EXCEPTION); 
}

template <> 
r_type test<__COUNTER__>() {
    // Duplicate father exception and direction invalid exception. 

    std::cout << "构建 tree_node 并为其添加一个父节点，并执行 add_node(other_node, node, 53). " << std::endl;   
    tree_node t{}, f{}, o{}; 
    ADD_NODE_LEFT(&f, &t); 

    return check_exception(add_node(&o, &t, 53), DUPLICATED_FATHER_EXCEPTION | INVALID_CHILD_DIRECTION_EXCEPTION); 
}

template <> 
r_type test<__COUNTER__>() {
    // Duplicate father exception and duplicate left node exception. 

    std::cout << "构建 tree_node parent and l_child, 建立关系后再次执行 ADD_NODE_LEFT(parent, l_child). " << std::endl; 
    tree_node f{}, l{};
    ADD_NODE_LEFT(&f, &l);
    
    return check_exception(ADD_NODE_LEFT(&f, &l), DUPLICATED_LEFT_CHILD_EXCEPTION | DUPLICATED_FATHER_EXCEPTION); 
}

template <> 
r_type test<__COUNTER__>() {
    // Duplicate father exception and duplicate right node exception. 

    std::cout << "构建 tree_node parent and r_child, 建立关系后再次执行 ADD_NODE_RIGHT(parent, r_child). " << std::endl; 
    tree_node f{}, r{}; 
    ADD_NODE_RIGHT(&f, &r); 

    return check_exception(ADD_NODE_RIGHT(&f, &r), DUPLICATED_RIGHT_CHILD_EXCEPTION | DUPLICATED_FATHER_EXCEPTION); 
}

template <> 
r_type test<__COUNTER__>() {
    // 简单构建一棵三层二叉树. 

    std::cout << "构建一棵三层的二叉树。" << std::endl; 

    tree_node t{}, l{}, r{}, ll{}, lr{}, rl{}, rr{}; 

    if (auto o = build_with_nodes(t, l, r); o)
        return o; 
    
    if (auto o = build_with_nodes(l, ll, lr); o)
        return o; 

    if (auto o = build_with_nodes(r, rl, rr); o)
        return o; 
    
    return {}; 
}

template <> 
r_type test<__COUNTER__>() {
    // 判断是否成功将点相连。

    std::cout << "构建一棵普通二层二叉树，并测试点的相连情形。" << std::endl; 

    tree_node t{}, l{}, r{}; 

    build_with_nodes(t, l, r);

    if (t.l_child != &l || l.father != &t) 
        return "根节点与左子节点没有正确相连。"; 

    if (t.r_child != &r || r.father != &t) 
        return "根节点与右子节点没有正确相连。";  

    return {}; 
}