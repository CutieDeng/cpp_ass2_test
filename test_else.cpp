emplate <> 
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