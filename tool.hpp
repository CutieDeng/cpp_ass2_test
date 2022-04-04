#include <optional> 
#include <string> 
#include <sstream> 
#include <exception> 
#include <initializer_list>
#include <vector>
#include <functional> 
#include <utility> 

namespace {

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
        if (!flag)  
            i << "NONE"; 
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
            // std::cout << "正在检查节点 node_count 信息。" << std::endl; 
            // std::cout << format("遍历至节点 {}.", t) << std::endl; 
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
                if (c(t.data, t.r_child->data) > 0) {
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

    // 使用如下三个 tree_node 构建一个小二叉树。
    r_type build_with_nodes(tree_node &f, tree_node &l, tree_node &r) {
        auto e1 = ADD_NODE_LEFT(&f, &l); 
        if (e1) 
            return format("调用 ADD NODE LEFT 返回了意外的异常：{}. ", transfer_exception(e1)); 
        
        e1 = ADD_NODE_RIGHT(&f, &r); 
        if (e1) 
            return format("调用 ADD NODE RIGHT 返回了意处的异常：{}. ", transfer_exception(e1)); 
        return {}; 
    }

    // 全等比较器
    int compare_equality(uint64_t, uint64_t ) {
        return 0; 
    }

    // 模十比较器 
    int compare_ones(uint64_t a, uint64_t b) {
        return compare_std(a % 10, b % 10); 
    }

    uint64_t map(uint64_t a) {
        uint64_t r = a & 0xffffffff; 
        uint64_t v = a >> 32; 
        return r * r + v * v; 
    }

    int compare_complex(uint64_t a, uint64_t b) {   
        return compare_std(map(a), map(b)); 
    }

    uint64_t create_complex(uint32_t real, uint32_t imaginary) {
        return (static_cast<uint64_t>(imaginary) << 32) | real; 
    }

    namespace cutie {
        uint32_t height_of_node(tree_node const &node) {
            uint32_t height = 0; 
            if (node.l_child)
                height = height_of_node(*node.l_child); 
            if (node.r_child)
                height = std::max(height, height_of_node(*node.r_child)); 
            return height + 1; 
        }
    }

    uint32_t height_of_bst(BST const &bst) {
        if (!bst.root)
            return 0; 
        return cutie::height_of_node(*bst.root); 
    }

    r_type upper_limit_height(BST const &bst, uint32_t limits) {
        auto actual = height_of_bst(bst); 
        if (actual > limits) {
            return format("超过限制的树高，bst 实际高度：{}, 限制高度：{}. ", actual, limits); 
        } else 
            return {}; 
    }

    r_type rotate_to_top(BST &bst, uint64_t data) {
        tree_node *node {}; 
        if (auto e = find_in_BST(&bst, data, &node); e) {
            return format("在 bst 中搜索 {} 遭遇异常：{}. ", data, transfer_exception(e)); 
        }
        if (auto e = splay(&bst, node); e)
            return format("在 bst 中旋转 node 至根节点遭遇异常：{}. ", transfer_exception(e)); 
        if (!bst.comp) 
            throw std::runtime_error("bst 无比较器异常。"); 
        else if (!bst.root)
            return "bst 根结点失踪。"; 
        else if (bst.comp(data, bst.root->data)) 
            return format("旋转完成后根结点非预期。根节点数据：{}, 期望的值为：{}. , ", bst.root->data, data); 
        return {}; 
    }
}