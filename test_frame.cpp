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
    // 进行异常抛出测试。
    std::cout << "正在进行异常抛出测试。" << std::endl; 

    throw std::runtime_error("我是被抛出的运行时异常"); 

    std::cout << "异常抛出完成。" << std::endl; 

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
    // 高危测试！
    std::cout << "内存访问错误测试（Segmentation Fault）！" << std::endl; 
    std::cout << "如果本段代码导致程式中断，请注释掉该测试方法！" << std::endl; 

    std::cout << "执行代码 char *p = nullptr; *p = 0; " << std::endl; 
    char *p = nullptr; 
    *p = 0;

    std::cout << "执行代码成功。" << std::endl; 
    return {}; 
}