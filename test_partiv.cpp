template <> 
r_type test<__COUNTER__>() {
    // 下面开始第四部分的测试内容。
    std::cout << "下面进入 Part IV 测试。" << std::endl; 

    // 先测试对空树的查询吧. 
    std::cout << "构建一棵空 bst, 并执行 find in bst. " << std::endl; 
    BST bst{}; 
    tree_node *ans; 

    return check_exception(find_in_BST(&bst, 0, &ans), NULL_COMP_FUNCTION_EXCEPTION); 
}

template <> 
r_type test<__COUNTER__>() {
    // 再测试直接对 nullptr bst 进行查询。

    std::cout << "执行 find in bst (nullptr). " << std::endl; 
    tree_node *ans; 
    
    return check_exception(find_in_BST(nullptr, 674, &ans), NULL_POINTER_EXCEPTION); 
}

template <> 
r_type test<__COUNTER__>() {
    // 再测试答案指针为 nullptr 时的情形。

    std::cout << "构造一棵 bst, 但在查询时没有提供答案回传地址。" << std::endl; 
    BST bst{}; 

    return check_exception(find_in_BST(&bst, 404, nullptr), NULL_POINTER_EXCEPTION | NULL_COMP_FUNCTION_EXCEPTION); 
}

template <> 
r_type test<__COUNTER__>() {
    // 正式进入正常的测试内容。

    std::cout << "构造一棵标准的 bst, 并插入若干数据。" << std::endl; 

    BST bst{.comp = compare_std}; 
    tree_node *ans{}; 

    insert_data(bst, {2, 6, 5, 8, 11, 21, 44, 75}); 

    std::cout << "搜索不存在于 bst 中的数据。" << std::endl; 
    // 搜索不存在的节点 
    find_in_BST(&bst, 1, &ans); 

    destruct_tree(bst); 
    if (ans) return format("搜索结果不为空：{}", *ans); 
    else return {}; 
}

template <> 
r_type test<__COUNTER__>() {
    // 插入标准的数据并进行查询. 
    std::cout << "构建一棵 bst, 并向其中插入数据。" << std::endl; 

    BST bst {.comp = compare_std}; 
    tree_node *ans {}; 

    insert_data (bst, {61, 77, 211, 343, 659, 871, 902, 1000, 2103}); 

    std::cout << "搜索存在于 bst 中的数据。" << std::endl; 

    find_in_BST(&bst, 902, &ans); 

    if (!ans) {
        return "查询结果为空。";
    } else if (ans->data != 902) {
        return format("查询的结点与预期不符，实际值：{}, 预期值：{}. ", ans->data, 902); 
    } else {
        destruct_tree(bst); 
        return {}; 
    }
}

template <> 
r_type test<__COUNTER__>() {
    // 插入重复的数据以进行询问. 

    std::cout << "构建一棵个位 bst, 并向其中插入数据。 " << std::endl; 

    BST bst {.comp = compare_ones}; 
    tree_node *ans {}; 

    insert_data (bst, {5, 3, 8, 4, 6, 2, 9, 7, 1, 0}); 
    insert_data (bst, {33, 46, 55, 88, 921, 516, 727, 457, 595, 121, 75}); 

    std::cout << "询问其中的部分元素个数。" << std::endl; 

    find_in_BST(&bst, 5, &ans); 

    if (!ans) {
        return "查询结果为空。"; 
    } else if (bst.comp(ans->data, 5)) {
        return format("查询结果与预期不符，实际结果：{}, 预期结果：{}. ", ans->data, 5); 
    } else {
        auto s = ans -> node_count; 
        destruct_tree(bst); 
        std::cout << "正在比对该元素在 bst 中的个数。" << std::endl; 
        return check_int(s, 4); 
    }
}

template <> 
r_type test<__COUNTER__>() {
    // 插入若干元素并统计个数 

    std::cout << "构建一个全等 bst, 并向其中插入数据。" << std::endl; 

    BST bst {.comp = compare_equality}; 
    tree_node *ans {}; 

    insert_data(bst, {1, 7, 5, 10, 21, 55, 7, 33, 21, 6, 81, 1}); 

    std::cout << "进行元素个数的询问. " << std::endl; 
    find_in_BST(&bst, 999, &ans); 

    if (!ans) {
        return "查询结果为空。"; 
    } else if (bst.comp(ans->data, 999)) {
        return format("查询结果与预期不符，实际结果：{}, 预期结果：{}. ", ans->data, 999); 
    } else {
        auto s = ans -> node_count; 
        destruct_tree(bst); 
        std::cout << "正在比对该元素在 bst 中的个数。" << std::endl; 
        return check_int(s, 12); 
    }
}

template <> 
r_type test<__COUNTER__>() {
    // Thanks for the attribution of classmate Zhang Ce. 

    std::cout << "构建一棵空 bst, 有comp方法, 并执行 find in bst. " << std::endl; 
    BST bst{.comp = compare_std}; 
    tree_node t{}; 
    tree_node *ans {&t}; 

    if (auto e = find_in_BST(&bst, 1, &ans); e) {
        return check_exception(e, 0); 
    }

    destruct_tree(bst); 
    if (ans) return format("搜索结果不为空：{}", *ans); 
    else return {}; 
}