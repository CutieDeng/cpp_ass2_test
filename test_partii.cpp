template <>
r_type test<__COUNTER__>() {
    // 从此开始进行 Part II 测试内容。
    std::cout << "Part II 测试开始。" << std::endl; 

    // 本次测试测试 judge_child_direction 在其没有父节点时的情形。

    std::cout << "构建一个 tree_node 并询问它的 child direction. " << std::endl; 
    int direct; 
    tree_node r{}; 
    return check_exception(judge_child_direction(&r, &direct), ROOTS_FATHER_EXCEPTION); 
}

template <> 
r_type test<__COUNTER__>() {
    // 本次测试测试 nullptr tree_node 的 child direction. 
    std::cout << "询问 nullptr 的 child direction. " << std::endl; 
    int direct; 
    
    return check_exception(judge_child_direction(nullptr, &direct), NULL_POINTER_EXCEPTION); 
} 

template <> 
r_type test<__COUNTER__>() {
    // 进行 Null pointer exception 测试～. 
    // 测试 judge_child_direction(nullptr, nullptr) 的情形. 
    std::cout << "询问 nullptr 的 child direction, 并且不设置对应的答复内存空间。" << std::endl; 

    return check_exception(judge_child_direction(nullptr, nullptr), NULL_POINTER_EXCEPTION); 
}

template <> 
r_type test<__COUNTER__>() {
    // 本次测试测试 judge_child_direction 在节点没有为根且答案空间为空时的异常情形

    std::cout << "构造节点 node 且询问 judge_child_direction(node, nullptr) 时的回答。" << std::endl; 
    tree_node f{}; 

    return check_exception(judge_child_direction(&f, nullptr), NULL_POINTER_EXCEPTION | ROOTS_FATHER_EXCEPTION); 
}

template <> 
r_type test<__COUNTER__>() {
    // 测试普通子节点 judge_child_direction 运行 judge_child_direction 且发现其没有答案内存空间时的异常类型

    std::cout << "构造节点 node 为一个左子节点，并调用 judge_child_direction(node, nullptr). " << std::endl; 
    tree_node f{}, n{}; 
    ADD_NODE_RIGHT(&f, &n);    

    return check_exception(judge_child_direction(&n, nullptr), NULL_POINTER_EXCEPTION); 
}

template <> 
r_type test<__COUNTER__>() {
    // 测试一般情形，即该点为一个左节点。

    std::cout << "构造一棵二层二插树。" << std::endl; 

    tree_node f{}, l{}, r{}; 
    build_with_nodes(f, l, r); 

    int ans{-1}; 
    std::cout << "询问左节点的 child direction. " << std::endl; 

    if (auto e = judge_child_direction(&l, &ans); !e) {
        std::cout << "获得结果，正在比较该返回值。" << std::endl; 
        return check_int(ans, CHILD_DIRECTION_LEFT); 
    } else {
        return check_exception(e, 0);
    }
}

template <> 
r_type test<__COUNTER__>() {
    // 测试一般情形，即该点为一个右节点。

    std::cout << "构造一棵二层二叉树。" << std::endl; 

    tree_node f{}, l{}, r{}; 
    build_with_nodes(f, l, r); 

    int ans{-1}; 
    std::cout << "询问右节点的 child direction. " << std::endl; 

    if (auto e = judge_child_direction(&r, &ans); !e) {
        std::cout << "获得结果，正在比较该返回值。" << std::endl; 
        return check_int(ans, CHILD_DIRECTION_RIGHT); 
    } else {
        return check_exception(e, 0);
    }
}

template <> 
r_type test<__COUNTER__>() {
    // 测试更复杂的情形，构建一棵三层二叉树。

    std::cout << "构造一棵三层二叉树。" << std::endl; 

    tree_node f{}, l{}, r{}, ll{}, lr{}, rl{}, rr{}; 
    build_with_nodes(f, l, r); 
    build_with_nodes(l, ll, lr); 
    build_with_nodes(r, rl, rr); 

    int ans {-1}; 
    std::cout << "询问根的左节点的 child direction. " << std::endl; 

    if (auto e = judge_child_direction(&l, &ans); !e) {
        std::cout << "获得结果，正在比较该返回值。" << std::endl; 
        return check_int(ans, CHILD_DIRECTION_LEFT); 
    } else 
        return check_exception(e, 0); 
}

template <> 
r_type test<__COUNTER__>() {
    // 测试更复杂的情形，构建一棵三层二叉树。

    std::cout << "构造一棵三层二叉树。" << std::endl; 

    tree_node f{}, l{}, r{}, ll{}, lr{}, rl{}, rr{}; 
    build_with_nodes(f, l, r); 
    build_with_nodes(l, ll, lr); 
    build_with_nodes(r, rl, rr); 

    int ans {-1}; 
    std::cout << "询问左节点的右子节点的 child direction. " << std::endl; 

    if (auto e = judge_child_direction(&lr, &ans); !e) {
        std::cout << "获得结果，正在比较该返回值。" << std::endl; 
        return check_int(ans, CHILD_DIRECTION_RIGHT); 
    } else 
        return check_exception(e, 0); 
}