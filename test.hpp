#pragma once 

#include <optional> 
#include <string> 
#include <sstream> 
#include <exception> 
#include <initializer_list>
#include <vector>
#include <functional> 
#include <utility> 

// Use std::optional..., just called r_type and name test to achieve your tests! 

namespace {
    typedef std::optional<std::string> r_type; 

    // cutie 的命名空间内函数，请不必阅读此处代码。
    // 该命名空间内的函数不建议测试者、开发者进行阅读。
    namespace cutie {
        template <typename ...Args>
        void inner_format(std::stringstream &a, std::string_view s, int, Args const &...args); 

        template <typename T> 
        void to_string(std::ostream &, T const &); 

        template <> 
        void inner_format(std::stringstream &a, std::string_view s, int offset) {
            while (s[offset]) {
                a << s[offset++]; 
            }
        }

        template <typename T, typename ...Args>
        void inner_format(std::stringstream &a, std::string_view s, int offset, T const &arg, Args const &...args) {
            bool flag = false; 
            bool ignore = false; 
            while (s[offset]) {
                switch (s[offset]) {
                    case '{': {
                        if (ignore) 
                            throw std::runtime_error("Invalid '}{' matching. "); 
                        if (flag) 
                            a << '{'; 
                        flag = !flag; 
                        break; 
                    }
                    case '}': {
                        if (flag) {
                            cutie::to_string(a, arg);
                            inner_format(a, s, offset + 1, args...); 
                            return ; 
                        } else {
                            if (ignore)
                                a << '}'; 
                            ignore = !ignore; 
                        }
                    }
                    default: {
                        a << s[offset];
                        flag = false; 
                        ignore = false; 
                    }
                }
                ++offset;
            }
        }

        template <typename T>
        void to_string(std::ostream &o, T const &a) {
            o << a; 
            return ; 
        }

        template <> 
        void to_string(std::ostream &o, tree_node const &t) {
            o << "[tree_node value = " << t.data << ", n_count = " << t.node_count << 
                ", t_count = " << t.tree_count << ". Relation(left: "; 
            if (!t.l_child)  
                o << "un"; o << "exists, right: "; 
            if (!t.r_child)
                o << "un"; o << "exists, father: "; 
            if (!t.father)
                o << "un"; o << "exists.]"; 
            return ; 
        }
    }

    // 格式化函数，支持快速格式化内容。
    // 调用方法大致如下：format("Hello World"); 得到一个 Hello World 字符串。
    // 等价地调用还有： format ("{} {}", "Hello", "World"); 
    // 欢迎调戏。
    template <typename ...Args> 
    std::string format(std::string_view a, Args const & ...b)  {
        std::stringstream s; 
        cutie::inner_format(s, a, 0, b...); 
        return s.str(); 
    }

    // 该方法用于格式化 exception 信息，你可以使用该方法使一个 assign2_exception::exception 转化成一个
    // 人类可读的字符串。 
    // 当 exception 没有异常信息时，该方法会返回一个空字符串。
    std::string transfer_exception(assign2_exception::exception e) {
        std::stringstream i; 
        bool flag (false); 
        if (e & NULL_POINTER_EXCEPTION) {
            if (flag) i << " & "; 
            i << "NULL POINTER EXCEPTION"; 
            flag = true; 
        }
        if (e & DUPLICATED_LEFT_CHILD_EXCEPTION) {
            if (flag) i << " & "; 
            i << "DUPLICATED LEFT CHILD EXCEPTION"; 
            flag = true; 
        }
        if (e & DUPLICATED_RIGHT_CHILD_EXCEPTION) {
            if (flag) i << " & "; 
            i << "DUPLICATED RIGHT CHILD EXCEPTION"; 
            flag = true; 
        }
        if (e & DUPLICATED_FATHER_EXCEPTION) {
            if (flag) i << " & "; 
            i << "DUPLICATED FATHER EXCEPTION"; 
            flag = true; 
        }
        if (e & INVALID_CHILD_DIRECTION_EXCEPTION) {
            if (flag) i << " & "; 
            i << "INVALID CHILD DIRECTION EXCEPTION"; 
            flag = true; 
        }
        if (e & ROOTS_FATHER_EXCEPTION) {
            if (flag) i << " & "; 
            i << "ROOTS FATHER EXCEPTION"; 
            flag = true; 
        }
        if (e & NULL_COMP_FUNCTION_EXCEPTION) {
            if (flag) i << " & "; 
            i << "NULL COMP FUNCTION EXCEPTION"; 
            flag = true; 
        }
        if (e & SPLAY_NODE_NOT_IN_TREE_EXCEPTION) {
            if (flag) i << " & "; 
            i << "SPLAY NODE NOT IN TREE EXCEPTION"; 
            flag = true; 
        }
        return i.str(); 
    }

    uint32_t get_node_size(tree_node const &t) {
        uint32_t ans {0}; 
        if (t.l_child)
            ans += t.l_child -> tree_count; 
        if (t.r_child)
            ans += t.r_child -> tree_count; 
        ans += t.node_count; 
        return ans; 
    }

    // check_exception 用于判断两个异常类型是否完全相同。
    // 如果完全相同，其将会返回一个空对象，表示没有错误信息输出。
    // 如果存在不同，其将会返回一个具体描述为什么不同，两个异常实例不同点在哪的信息以便于被测进行 DEBUG. 
    r_type check_exception(assign2_exception::exception actual, assign2_exception::exception expect) {
        if (actual == expect)
            return {}; 
        std::stringstream i; 
        i << "希望返回的异常类型为：" << transfer_exception(expect) 
            << "; 而实际返回的类型为：" << transfer_exception(actual) << ". "; 
        return i.str();  
    }

    r_type check_int(int actual, int expect) {
        if (actual == expect)
            return {}; 
        std::stringstream i; 
        i << "期待的整型值为: " << expect << ", 而程序运行中实际得到的值为: " << actual << "."; 
        return i.str(); 
    }

    // inert_data 聚合了插入 BST 的操作。
    // 你可以使用该方法快速将一组数据一次性插入到一个 BST 中。
    // 它的返回值是一个变长数组，用以依顺序记录每次使用 insert_into_BST 的返回值。
    // 本方法不期望在调用 insert_into_BST 的过程中得到一个异常回复。
    std::vector<tree_node *> insert_data(BST &bst, std::initializer_list<uint64_t> const &v){
        tree_node *p (nullptr); 
        std::vector<tree_node *> r;
        r.reserve(v.size());  
        for (auto va: v) {
            if (insert_into_BST(&bst, va, &p)) {
                throw std::runtime_error("正确插入节点至 bst 中，却遭遇执行异常。"); 
            }
            r.push_back(p); 
        }
        return std::move(r); 
    }

    namespace cutie {
        void destruct_tree_node(tree_node *p) {
            if (!p)
                return ; 
            destruct_tree_node(p -> l_child); 
            destruct_tree_node(p -> r_child); 
            delete p; 
        }
    }

    // 该方法用于递归地删除一棵树。
    // 调用该方法可以将一树 BST 上的所有节点都删除，并释放其所有节点的内存。
    // insert 了太多节点不知道怎么释放？就用它吧！
    void destruct_tree(BST &bst) {
        cutie::destruct_tree_node(bst.root); 
        bst.root = nullptr;        
    }

    // 求取一棵树的数据数？
    // 直接无脑 bst.root.tree_count? 
    // 不如用用 size of tree 吧，有较避免 null pointer exception~. 
    uint32_t size_of_tree(BST &bst) {
        if (bst.root)
            return bst.root -> tree_count; 
        else 
            return 0; 
    }

    namespace cutie {
        r_type check_node(tree_node const &t, int (c)(uint64_t, uint64_t )) {
            if (t.node_count <= 0)
                return format("检查发现某节点的 node_count 属性非法，节点信息：{}. ", t); 
            if (auto i = get_node_size(t); i != t.tree_count) {
                std::cout << "检查该点的 node_count 信息发现错误：" << std::endl; 
                std::cout << format("错误节点为 {}.", t) << std::endl; 
                return check_int(t.tree_count, i); 
            } 
            if (t.l_child) {
                if (t.l_child -> father != &t) {
                    if (t.l_child -> father) {
                        return format("节点 {} 的 father 信息错误。\n\t应当出现的 father 节点为 {} \n\t而实际出现的 father 节点为 {}. ",
                            *t.l_child, t, *t.l_child->father); 
                    } else {
                        return format("节点 {} 缺失 father 节点信息。", *t.l_child); 
                    }
                }
                if (c(t.data, t.l_child->data) <= 0) {
                    return format("非法的节点分布，节点 {} 有错误的左节点。", t); 
                }
                if (auto e = check_node(*t.l_child, c); e)
                    return e; 
            }
            if (t.r_child) {
                if (t.r_child -> father != &t) {
                    if (t.r_child -> father) {
                        return format("节点 {} 的 father 信息错误。\n\t应当出现的 father 节点为 {} \n\t而实际出现的 father 节点为 {}. ",
                            *t.r_child, t, *t.r_child->father); 
                    } else {
                        return format("节点 {} 缺失 father 节点信息。", *t.r_child); 
                    }
                }
                if (c(t.data, t.l_child->data) <= 0) {
                    return format("非法的节点分布，节点 {} 有错误的右节点。", t); 
                }
                if (auto e = check_node(*t.r_child, c); e)
                    return e; 
            }
            return {}; 
        }
    }

    // 使用该方法来检查你的 BST 的正确性：
    // 1. tree_count 结果的正确性
    // 2. 是否满足 comp 函数计算结果的正确性
    // 3. 各节点信息是否具有一致性 
    // 检查成功则返回空对象，失败会返回一个包含错误信息的字符串。
    r_type check_bst(BST const &bst) {
        if (bst.root) {
            if (bst.root->father)   
                return "当前 bst.root 存在 father 节点。"; 
            return cutie::check_node(*bst.root, bst.comp); 
        } else 
            return {}; 
    }

    // 标准的比较器函数
    int compare_std(uint64_t a, uint64_t b) {
        if (a < b)
            return -1; 
        else if (a > b)
            return 1; 
        else return 0; 
    }

    // 对标准比较器取个反吧。
    int compare_reverse(uint64_t a, uint64_t b) {
        return -compare_std(a, b); 
    }
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