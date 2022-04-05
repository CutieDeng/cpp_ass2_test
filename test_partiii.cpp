template <> 
r_type test<__COUNTER__>() {
    // 这是第三部分测试的第一条测试代码。
    std::cout << "进入 Part III 测试。" << std::endl; 

    // 执行最简单的 insert to bst 测试。
    std::cout << "向 nullptr(bst) 中插入 data. " << std::endl; 

    return check_exception(insert_into_BST(nullptr, 47, nullptr), NULL_POINTER_EXCEPTION); 
}

template <> 
r_type test<__COUNTER__>() {
    std::cout << "向未初始化的 bst 中插入数据但没有给出答案空间。" << std::endl; 

    BST b{}; 

    return check_exception(insert_into_BST(&b, 23, nullptr), NULL_POINTER_EXCEPTION | NULL_COMP_FUNCTION_EXCEPTION); 
}

template <> 
r_type test<__COUNTER__>() {
    std::cout << "向未初始化的 bst 中插入数据。" << std::endl; 

    BST b{}; 
    tree_node *p {}; 

    return check_exception(insert_into_BST(&b, 21, &p), NULL_COMP_FUNCTION_EXCEPTION); 
}

template <> 
r_type test<__COUNTER__>() {
    std::cout << "向标准的空 bst 中插入一条数据。" << std::endl; 

    BST b{.comp = compare_std}; 
    tree_node *p {}; 

    if (auto e = check_exception(insert_into_BST(&b, 66, &p), 0); e) {
        return e; 
    } else {
        delete p; 
        return {}; 
    }
}

template <> 
r_type test<__COUNTER__>() {
    std::cout << "向标准的空 bst 中插入两条相同数据。" << std::endl; 

    BST b{.comp = compare_std}; 
    tree_node *p {}; 

    insert_into_BST(&b, 42, &p); 
    insert_into_BST(&b, 42, &p); 

    std::cout << "正在检查该 bst 树的大小信息。" << std::endl; 
    if (auto c = check_int(size_of_tree(b), 2); c) {
        return c; 
    } else {
        delete p; 
        return {}; 
    }
}

template <> 
r_type test<__COUNTER__>() {
    // 该测试开始测试树的大小有无错误。
    std::cout << "向标准的 bst 中插入不同数据。" << std::endl; 

    BST b{.comp = compare_std}; 

    auto rooms = insert_data(b, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}); 

    std::cout << "正在检查该 bst 树的大小信息。" << std::endl; 
    if (auto c = check_int(size_of_tree(b), 10); c) {
        return c; 
    } else {
        for (auto d: rooms) delete d; 
        return {}; 
    }
}

template <> 
r_type test<__COUNTER__>() {
    std::cout << "向逆序的 bst 插入一些数据。" << std::endl; 

    BST b{.comp =compare_reverse}; 

    auto rooms = insert_data(b, {1, 1, 2, 1, 6, 2, 4, 6, 5, 4, 3, 3, 7, 5}); 

    std::cout << "正在检查该 bst 的大小信息。" << std::endl; 
    if (auto c = check_int(size_of_tree(b), 14); c) {
        return c; 
    } else {
        for (auto i {0}; i < rooms.size(); i += 2)
            delete rooms[i]; 
        return {}; 
    }
}

template <> 
r_type test<__COUNTER__>() {
    std::cout << "向全等 bst 中插入一些数据。" << std::endl; 

    BST b{.comp = compare_equality}; 

    auto rooms = insert_data(b, {21, 77, 65, 410, 372, 666, 520}); 

    std::cout << "正在检查该 bst 的大小信息。" << std::endl; 
    if (auto c = check_int(size_of_tree(b), 7); c) {
        return c; 
    } else {
        delete rooms[0]; 
        return {}; 
    }
}

template <> 
r_type test<__COUNTER__>() {
    // 该测试负责测试该树结构是否满足结构性的要求。
    std::cout << "向个位 bst 中插入若干数据。" << std::endl; 

    BST b{.comp = compare_ones}; 

    insert_data(b, {75, 84, 93, 102, 111, 120, 136, 147, 158, 169, 180}); 

    std::cout << "遍历树结构并进行检查。" << std::endl; 
    if (auto e = check_bst(b); e) {
        return e; 
    } else {
        destruct_tree(b); 
        return {}; 
    }
}

template <> 
r_type test<__COUNTER__>() {
    std::cout << "向虚数 bst 中插入若干数据。" << std::endl; 

    BST b{.comp = compare_complex}; 

    insert_data(b, {create_complex(1, 0), create_complex(3, 5), create_complex(4, 1), create_complex(8, 7)}); 

    std::cout << "遍历树结构并进行检查。" << std::endl; 

    if (auto e = check_bst(b); e) {
        return e; 
    } else {
        destruct_tree(b); 
        return {}; 
    }
}

template <> 
r_type test<__COUNTER__>() {
    std::cout << "向 bst 中插入若干不同数据，后只插入重复数据。" << std::endl; 

    BST b {.comp = compare_std}; 

    insert_data(b, {71, 82, 955, 256, 346, 8237, 384, 758, 1245, 432}); 
    insert_data(b, {71, 71, 256, 8237, 758, 432}); 

    std::cout << "遍历树结构进行检查。" << std::endl; 

    if (auto e = check_bst(b); e) {
        return e; 
    } else {
        destruct_tree(b); 
        return {}; 
    }
}