template <> 
r_type test<__COUNTER__>() {
    // 从该测试开始，进入 Part V 测试内容。 
    std::cout << "正在进入 Part V 测试。" << std::endl; 

    // 先调用空指针操作吧！
    std::cout << "调用 splay nullptr nullptr 方法。" << std::endl; 

    return check_exception(splay(nullptr, nullptr), NULL_POINTER_EXCEPTION); 
}

template <> 
r_type test<__COUNTER__>() {
    // 本测试负责测试未完全初始化的 bst splay. 

    std::cout << "未完全初始化一个 bst, 并对其调用 splay nullptr. " << std::endl; 
    BST bst {}; 

    return check_exception(splay(&bst, nullptr), NULL_COMP_FUNCTION_EXCEPTION | NULL_POINTER_EXCEPTION);
}

template <> 
r_type test<__COUNTER__>() {
    // 本测试方法负责测试已经初始化好的 bst, 并依旧使用 nullptr 调用它。

    std::cout << "初始化一个 bst, 并调用 splay, 并传递一个空指针描述待旋转的 tree node. " << std::endl; 
    BST bst{.comp = compare_std}; 

    return check_exception(splay(&bst, nullptr), NULL_POINTER_EXCEPTION); 
}

template <> 
r_type test<__COUNTER__>() {
    // 本方法测试 splay 调用一棵没有节点的 bst. 

    std::cout << "初始化一个 bst, 并初始化一个节点 node, 调用 splay bst node. " << std::endl; 
    BST bst {.comp = compare_std}; 
    tree_node t{}; 

    return check_exception(splay(&bst, &t), SPLAY_NODE_NOT_IN_TREE_EXCEPTION); 
}

template <> 
r_type test<__COUNTER__>() {
    // 本方法构建两个 bst, 并试调用一个 bst 去 splay 另一个 bst 的节点。

    std::cout << "初始化两个 bst, 并向其中传入若干相同数据。" << std::endl; 

    BST bst {.comp = compare_std}, bst2 {.comp = compare_std}; 

    std::initializer_list<uint64_t> l = {65, 7, 21, 99, 520, 685, 424, 1772, 909, 696, 276, 8981}; 
    insert_data(bst, l); 
    insert_data(bst2, l); 

    std::cout << "查询一棵树上的结果，对另一棵树调用 splay. " << std::endl; 
    tree_node *p {}; 
    find_in_BST(&bst2, 909, &p); 

    if (auto e = check_exception(splay(&bst, p), SPLAY_NODE_NOT_IN_TREE_EXCEPTION); e) {
        return e; 
    } else {
        destruct_tree(bst); 
        destruct_tree(bst2); 
        return {}; 
    }
}

template <> 
r_type test<__COUNTER__>() {
    // 构建一棵 bst, 对其进行基本的 splay 且约束其最后的高度。

    std::cout << "初始化一个个位识别的 bst, 并向其中插入少量递减数据。" << std::endl; 
    BST bst {.comp = compare_ones}; 
    insert_data(bst, {6, 4, 5});

    std::cout << "执行 splay 操作。" << std::endl; 
    if (auto o = rotate_to_top(bst, 5); o)
        return o; 

    // 此时当前的 bst 以 5 为根，其应当高度小于 2. 
    if (auto c = check_bst(bst); c) 
        return c; 
    
    if (auto h = upper_limit_height(bst, 2); h)
        return h; 
    
    destruct_tree(bst); 
    return {}; 
}

template <> 
r_type test<__COUNTER__>() {
    // 构建一棵 bst, 并对其进行双旋操作。

    std::cout << "初始化一个 bst, 插入数据 15, 12, 7, 5, 2, 4。" << std::endl; 
    BST bst {.comp = compare_std}; 
    insert_data(bst, {15, 12, 7, 5, 2, 4}); 

    std::cout << "执行 splay 操作，将 2 转至 root 点。" << std::endl; 
    if (auto c = rotate_to_top(bst, 2); c) 
        return c; 

    if (auto c = check_bst(bst); c) 
        return c; 

    // 此时当前的 bst 高度不应超过 4. 
    if (auto h = upper_limit_height(bst, 4); h)
        return h; 
    
    destruct_tree(bst); 
    return {}; 
}

template <> 
r_type test<__COUNTER__>() {

    // 构建一棵 bst, 并对其进行 splay 操作。

    std::cout << "初始化一个反向 bst, 并向其中插入重复数据。" << std::endl; 
    BST bst {.comp = compare_reverse}; 

    std::cout << "数据：16, 22, 23, 47, 27, 22, 16, 47, 36, 36, 32, 31. " << std::endl; 
    insert_data(bst, {16, 22, 23, 47, 27, 22, 16, 47, 36, 36, 32, 31}); 

    std::cout << "执行 splay 操作，搜索值为 31 的点。" << std::endl; 
    if (auto c = rotate_to_top(bst, 31); c) 
        return c; 
    if (auto c = check_bst(bst); c)
        return c; 
    if (auto c = upper_limit_height(bst, 4)) 
        return c;
    destruct_tree(bst); 
    return {}; 
}