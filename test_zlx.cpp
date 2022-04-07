namespace zlx {

    int comp(uint64_t a, uint64_t b);
    void inorder(BST * const bst, std::string *);
    void preorder(BST * const bst, std::string *);
    void delete_tree(tree_node * );
    bool judge_bst(BST *bst, int &tree_count);
    tree_node * create_tree_node_test(uint64_t data); 
    BST * create_bst_test(tree_node *node, int (*comp)(uint64_t, uint64_t));
    tree_node * find_root(tree_node * node);
    void delete_from_root(tree_node * node);

    int main(){
       /*
        This is the test for function add_node. 
    */
    // Part 1 - case 1
    int count = 0;
    {
        assign2_exception::exception e = 0;
        e|=add_node(nullptr, nullptr, CHILD_DIRECTION_LEFT);
        try {
            if (e!=1) throw e;
            count++;
        }
        catch(assign2_exception::exception){
            std::cout<<"\033[41;11m Error in part 1, case1!  \033[0m\n";
        }
    }
    // // Part 1 - case 2
    {
        tree_node * father = new tree_node;
        tree_node * child = new tree_node; 
        tree_node * father_left = new tree_node;
        tree_node * child_father = new tree_node;

        father->l_child = father_left;
        child->father = child_father;

        assign2_exception::exception e = 0;
        e|=add_node(father, child, CHILD_DIRECTION_LEFT);
        try {
            if (e!=10) throw e;
            count++;
        }
        catch(assign2_exception::exception){
            std::cout<<"\033[41;11m Error in part 1, case2!  \033[0m\n";
            
        }
        delete father;
        delete child;
        delete father_left;
        delete child_father;
    }
    // // Part 1 - case 3
    {
        tree_node * father = new tree_node;
        tree_node * child = new tree_node; 
        tree_node * father_right = new tree_node;

        father->r_child = father_right;
        child->father = nullptr;
        assign2_exception::exception e = 0;
        e|=add_node(father, child, CHILD_DIRECTION_RIGHT);
        try {
            if (e!=4) throw e;
            count++;
        }
        catch(assign2_exception::exception){
            std::cout<<"\033[41;11m Error in part 1, case3! \033[0m\n";
        }
        delete father;
        delete child;
        delete father_right;
    }

    // // Part 1 - case 4
    {
        tree_node * father = new tree_node;
        tree_node * child = new tree_node; 
        tree_node * father_right = new tree_node;

        father->r_child = father_right;
        child->father = NULL;
        assign2_exception::exception e = 0;
        e|=add_node(father, child, -1);
        try {
            if (e!=16) throw e;
            count++;
        }
        catch(assign2_exception::exception){
            std::cout<<"\033[41;11m Error in part 1, case4! \033[0m\n";
        }
        delete father;
        delete child;
        delete father_right;
    }

    // // Part 1 - case 5
    {
        tree_node * father = create_tree_node_test(2);
        tree_node * l_child = create_tree_node_test(1); 
        tree_node * r_child = create_tree_node_test(3);
        tree_node * test_tree_count = create_tree_node_test(4);
        assign2_exception::exception e = 0;
        e|=add_node(father, l_child, CHILD_DIRECTION_LEFT);
        e|=add_node(father, r_child, CHILD_DIRECTION_RIGHT);
        e|=add_node(r_child, test_tree_count, CHILD_DIRECTION_RIGHT);
        BST *bst = new BST;
        int root_tree_count = 0;
        bst->root = r_child;
        bst->comp = comp;
        try {
            if (father->l_child->data!=1 || father->r_child->data!=3) throw e;
            if (!judge_bst(bst, root_tree_count) || root_tree_count != bst->root->tree_count) throw e;
            count++;
            
        }
        catch(assign2_exception::exception){
            std::cout<<"\033[41;11m Error in part 1, case5! \033[0m\n";
        }
        delete father;
        delete l_child;
        delete r_child;
        delete bst;
        delete test_tree_count;
    }

    // // Part 1 - case 6
    {
        tree_node * father = create_tree_node_test(2);
        tree_node * l_child = create_tree_node_test(1); 
        tree_node * r_child = create_tree_node_test(3);
        tree_node * test_tree_count = create_tree_node_test(4);
        assign2_exception::exception e = 0;
        e|=add_node(father, l_child, CHILD_DIRECTION_LEFT);
        e|=add_node(father, r_child, CHILD_DIRECTION_RIGHT);
        try {
            if (father->l_child->data!=1 || father->r_child->data!=3) throw e;
            count++;
            
        }
        catch(assign2_exception::exception){
            std::cout<<"\033[41;11m Error in part 1, case6! \033[0m\n";
        }
        delete father;
        delete l_child;
        delete r_child;
        delete test_tree_count;
    }

    /*
        This is the test for function judge_child_direction. 
    */
    // // Part 2 - case 1
   {
        tree_node * node;
        node = nullptr;
        int *child_direction = new int;

        assign2_exception::exception e = 0;
        e|=judge_child_direction(node, child_direction);
        try {
            if (e!=1) throw e;
            count++;
        }
        catch(assign2_exception::exception){
            std::cout<<"\033[41;11m Error in part 2, case1! \033[0m\n";
        }
        delete child_direction;
    }

    // Part 2 - case 2
   {
        tree_node * node = new tree_node;
        tree_node * father = new tree_node;
        node->father = NULL;
        int *child_direction = new int;

        assign2_exception::exception e = 0;
        e|=judge_child_direction(node, child_direction);
        try {
            if (e!=32) throw e;
            count++;
        }
        catch(assign2_exception::exception){
            std::cout<<"\033[41;11m Error in part 2, case2! \033[0m\n";
        }
        delete node;
        delete father;
        delete child_direction;
    }

    // Part 2 - case 3
    {
        tree_node * father = create_tree_node_test(2);
        tree_node * l_child = create_tree_node_test(1); 
        tree_node * r_child = create_tree_node_test(3);

        int *child_direction = new int;
        assign2_exception::exception e = 0;

        e|=add_node(father, l_child, CHILD_DIRECTION_LEFT);
        e|=add_node(father, r_child, CHILD_DIRECTION_RIGHT);
        try {
            e|=judge_child_direction(l_child,  child_direction);
            if (*child_direction != CHILD_DIRECTION_LEFT) throw e;
            e|=judge_child_direction(r_child,  child_direction);
            if (*child_direction != CHILD_DIRECTION_RIGHT) throw e;
            count++;
            
        }
        catch(assign2_exception::exception){
            std::cout<<"\033[41;11m Error in part 2, case3! \033[0m";
        }
        delete father;
        delete l_child;
        delete r_child;
        delete child_direction;
    }

    /*
        This is the test cases for part 3.
    */

    // Part 3 - case 1
    {
        assign2_exception::exception e = 0;
        try {
                BST *bst = new BST;
                tree_node *node = new tree_node;
                node->data=50;
                node->l_child=NULL;
                node->r_child=NULL;
                node->father=NULL;
                node->node_count=1;
                node->tree_count=1;
                bst->root = node;
                bst->comp = comp;
                tree_node *targetnode;
                insert_into_BST(bst,55,&targetnode);
                insert_into_BST(bst,32,&targetnode);
                insert_into_BST(bst,90,&targetnode);
                insert_into_BST(bst,61,&targetnode);
                insert_into_BST(bst,29,&targetnode);
                insert_into_BST(bst,36,&targetnode);
                insert_into_BST(bst,100,&targetnode);

                std::string *s1 = new std::string, *s2 = new std::string;                
                preorder(bst, s1);               
                inorder(bst, s2);
                std::string ans1="501832132911361155149013611110011";
                std::string ans2="291132133611501855146111901310011";
                if (*s1!=ans1 || *s2!=ans2){
                    delete s1;
                    delete s2;
                    delete_tree(bst->root);
                    delete bst;
                    throw e;
                }
                count++;
                delete s1;
                delete s2;
                delete_tree(bst->root);
                delete bst;
        }
        catch(assign2_exception::exception){
            std::cout<<"\033[41;11m Error in part 3, case1! \033[0m\n";
        }
        
    }

    // Part 3 - case 2
    {
        assign2_exception::exception e = 0;
        try {
                BST *bst = new BST;
                tree_node *node = new tree_node;
                node->data=50;
                node->l_child=NULL;
                node->r_child=NULL;
                node->father=NULL;
                node->node_count=1;
                node->tree_count=1;
                bst->root = node;
                bst->comp = comp;
                tree_node *targetnode;
                insert_into_BST(bst,55,&targetnode);
                insert_into_BST(bst,55,&targetnode);
                insert_into_BST(bst,55,&targetnode);
                insert_into_BST(bst,32,&targetnode);
                insert_into_BST(bst,90,&targetnode);
                insert_into_BST(bst,61,&targetnode);
                insert_into_BST(bst,29,&targetnode);
                insert_into_BST(bst,36,&targetnode);
                insert_into_BST(bst,100,&targetnode);
                insert_into_BST(bst,36,&targetnode);
                insert_into_BST(bst,36,&targetnode);
                insert_into_BST(bst,100,&targetnode);
                insert_into_BST(bst,100,&targetnode);

                // BST *new_bst = new BST;
                // new_bst->root = targetnode;
                // new_bst->comp = comp;
                // insert_into_BST(new_bst, )
                std::string *s1 = new std::string, *s2 = new std::string;
                preorder(bst, s1);
                inorder(bst, s2);
                std::string ans1="5011432152911363355389015611110033";
                std::string ans2="2911321536335011455386111901510033";
                if (*s1!=ans1 || *s2!=ans2){
                    delete s1;
                    delete s2;
                    delete_tree(bst->root);
                    delete bst;
                    
                    throw e;
                }
                count++;
                delete s1;
                delete s2;
                delete_tree(bst->root);
                delete bst;
        }
        catch(assign2_exception::exception){
            std::cout<<"\033[41;11m Error in part 3, case2! \033[0m\n";
        }
    }

    // Part 3 - case 3
    {
        assign2_exception::exception e = 0;
        try {
                BST *bst = new BST;
                bst->comp = comp;
                bst->root = nullptr;
                tree_node *targetnode;
                for (int i = 10000; i >= 1; i--){
                    insert_into_BST(bst, i, &targetnode);
                }

                // BST *new_bst = new BST;
                // new_bst->root = targetnode;
                // new_bst->comp = comp;
                // insert_into_BST(new_bst, )
                int tree_c=0;
                if (!judge_bst(bst,tree_c)){

                    delete_tree(bst->root);
                    delete bst;
                    
                    throw e;
                }
                count++;
                delete_tree(bst->root);
                delete bst;
        }
        catch(assign2_exception::exception){
            std::cout<<"\033[41;11m Error in part 3, case3! \033[0m\n";
        }
    }
    // Part 3 - case 4
    {
        assign2_exception::exception e = 0; 
        tree_node *(*node) = new tree_node*;
        try{
            e|=insert_into_BST(nullptr, 1, node);
            if (e!=1) throw e;
            count++;
        }
        catch(assign2_exception::exception){
            std::cout<<"\033[41;11m Error in part 3, case4! \033[0m\n";
        }
        delete node;
    }

    // Part 3 - case 5
    {
        assign2_exception::exception e = 0; 
        tree_node *(*node) = new tree_node*;
        BST *bst = new BST;
        bst->root = nullptr;
        bst->comp = nullptr;
        try{
            e|=insert_into_BST(bst, 1, node);
            if (e!=64) throw e;
            count++;
        }
        catch(assign2_exception::exception){
            std::cout<<"\033[41;11m Error in part 3, case5! \033[0m\n";
        }
        delete node;
        delete_tree(bst->root);
        delete bst;
    }
    /*
        This is the test case for part 4.
    */
   // Part 4 - case 1
    {
        assign2_exception::exception e = 0;
        try {
                BST *bst = new BST;
                tree_node *node = new tree_node;
                node->data=50;
                node->l_child=NULL;
                node->r_child=NULL;
                node->father=NULL;
                node->node_count=1;
                node->tree_count=1;
                bst->root = node;
                bst->comp = comp;
                tree_node *targetnode;
                //std::cout<<"wrong\n";
                insert_into_BST(bst,55,&targetnode);
                insert_into_BST(bst,32,&targetnode);
                insert_into_BST(bst,90,&targetnode);
                insert_into_BST(bst,61,&targetnode);
                insert_into_BST(bst,29,&targetnode);
                insert_into_BST(bst,36,&targetnode);
                insert_into_BST(bst,100,&targetnode);
                tree_node **target_node = new tree_node*;
                find_in_BST(bst, 1, target_node);
                if (*target_node != NULL) e = 1, throw e; // judgement step 1.
                count++;
                find_in_BST(bst, 50, target_node);
                if (*target_node==NULL || (*target_node)->data !=50) delete_tree(bst->root), delete bst, e = 2, throw e; // judgement step 2.
                count++;
                find_in_BST(bst, 55, target_node);
                if (*target_node==NULL || (*target_node)->data !=55) delete_tree(bst->root), delete bst, e = 3, throw e; // judgement step 3.
                count++;
                find_in_BST(bst, 90, target_node);
                if (*target_node==NULL || (*target_node)->data !=90) delete_tree(bst->root), delete bst, e = 4, throw e; // judgement step 4.
                count++;
                find_in_BST(bst, 61, target_node);
                if (*target_node==NULL || (*target_node)->data !=61) delete_tree(bst->root), delete bst, e = 5, throw e; // judgement step 5.
                count++;
                find_in_BST(bst, 29, target_node);
                if (*target_node==NULL || (*target_node)->data !=29) delete_tree(bst->root), delete bst, e = 6, throw e; // judgement step 6.
                count++;
                find_in_BST(bst, 36, target_node);
                if (*target_node==NULL || (*target_node)->data !=36) delete_tree(bst->root), delete bst, e = 7, throw e; // judgement step 7.
                count++;
                find_in_BST(bst, 32, target_node);
                if (*target_node==NULL || (*target_node)->data !=32) delete_tree(bst->root), delete bst, e = 8, throw e; // judgement step 8.
                count++;
                delete_tree(bst->root);
                delete bst; 
        }
        catch(assign2_exception::exception){
            std::cout<<"\033[41;11m Error in part 4, case1! Happen in judgement step "<<e<<". \033[0m\n";
        }
        
    }

    // Part 4 - case 2
    {
        assign2_exception::exception e = 0;
        try{
            e|=find_in_BST(nullptr, 1, nullptr);
            if (e!=1) throw e;
            count++;
        }
        catch (assign2_exception::exception){
            std::cout<<"\033[41;11m Error in part 4, case2! \033[0m\n";
        }
    }

    //Part 4 - case 3
    {
        assign2_exception::exception e = 0;
        BST *bst = create_bst_test(nullptr, nullptr);
        tree_node *(*target) = new tree_node*;
        try{
            e|=find_in_BST(bst, 1, target);
            if (e!=64) throw e;
            count++;
        }
        catch(assign2_exception::exception){
            std::cout<<"\033[41;11m Error in part 4, case3! \033[0m\n";
        }
        delete bst;
        delete target;
    }
    /*
        This is the test case for part 5. 
    */

    // Part 5 - case 1
    {
        assign2_exception::exception e = 0;
        try {
                BST *bst = new BST;
                tree_node *node = new tree_node;
                node->data=50;
                node->l_child=NULL;
                node->r_child=NULL;
                node->father=NULL;
                node->node_count=1;
                node->tree_count=1;
                bst->root = node;
                bst->comp = comp;
                tree_node *targetnode;
                tree_node *test_node_one;
                tree_node *test_node_two;
                tree_node *test_node_three;
                //std::cout<<"wrong\n";
                insert_into_BST(bst,55,&targetnode);
                insert_into_BST(bst,32,&targetnode);
                insert_into_BST(bst,90,&targetnode);
                insert_into_BST(bst,61,&targetnode);
                insert_into_BST(bst,61,&targetnode);
                insert_into_BST(bst,61,&targetnode);
                insert_into_BST(bst,61,&test_node_two);
                insert_into_BST(bst,29,&test_node_one);
                insert_into_BST(bst,36,&targetnode);
                insert_into_BST(bst,36,&test_node_three);
                insert_into_BST(bst,36,&targetnode);
                insert_into_BST(bst,100,&targetnode);
                insert_into_BST(bst,100,&targetnode);
                splay(bst, test_node_one);
                int tree_c = 0;
                if (!judge_bst(bst, tree_c) || bst->root != test_node_one) delete_tree(bst->root), delete bst, throw e=1;
                count++;
                std::cout<<"------------------\n";
                splay(bst, test_node_two);
                tree_c = 0;
                if (!judge_bst(bst, tree_c) || bst->root!=test_node_two) delete_tree(bst->root), delete bst, throw e=2;
                count++;
                splay(bst, test_node_three);
                tree_c = 0;
                if (!judge_bst(bst, tree_c) || bst->root!=test_node_three) delete_tree(bst->root), delete bst, throw e=3;
                count++;
                delete_tree(bst->root);
                delete bst; 
        }
        catch(assign2_exception::exception){
            std::cout<<"\033[41;11m Error in part 5, case1! Happen in judgement step "<<e<<". \033[0m\n";
        }
    }

    //Part 5 - case 2 //To test the zig and zag
    {
        assign2_exception::exception e = 0;
        try{
            tree_node * father = create_tree_node_test(2);
            tree_node * target_node;
            BST *bst = create_bst_test(father, comp);
            insert_into_BST(bst, 1, &target_node);
            splay(bst, bst->root->l_child);
            if (bst->root!=father->father || bst->root->r_child!=father) delete_tree(bst->root),delete bst, throw e; 
            count++;
            delete_tree(bst->root),delete bst;
        }
        catch(assign2_exception::exception){
            std::cout<<"\033[41;11m Error in part 5, case2!"<<". \033[0m\n";
        }
    }

    //Part 5 - case 3 //To test the zig and zag
    {
        assign2_exception::exception e = 0;
        try{
            tree_node * father = create_tree_node_test(2);
            tree_node * target_node;
            BST *bst = create_bst_test(father, comp);
            insert_into_BST(bst, 3, &target_node);
            splay(bst, bst->root->r_child);
            if (bst->root!=father->father || bst->root->l_child!=father) delete_tree(bst->root),delete bst,  throw e; 
            count++;
            delete_tree(bst->root);
            delete bst;
        }
        catch(assign2_exception::exception){
            std::cout<<"\033[41;11m Error in part 5, case3!"<<". \033[0m\n";
        }
    }

    //Part 5 - case 4
    {
        assign2_exception::exception e = 0;
        try
        {
            e|=splay(nullptr, nullptr);
            if (e!=1) throw e;
            count++; 
        }
        catch(assign2_exception::exception)
        {
            std::cout<<"\033[41;11m Error in part 5, case4!"<<". \033[0m\n";
        }
        
    }

    //Part 5 - case 5
    {
        assign2_exception::exception e = 0;
        BST *bst = create_bst_test(nullptr, nullptr);
        try
        {
            e|=splay(bst, nullptr);
            if (e!=65) throw e;
            count++; 
        }
        catch(assign2_exception::exception)
        {
            std::cout<<"\033[41;11m Error in part 5, case5!"<<". \033[0m\n";
        }
        delete bst;
        
    }
    //Part 5 - case 6
    {
        assign2_exception::exception e = 0;
        BST *bst = create_bst_test(nullptr, comp);
        tree_node *node = create_tree_node_test(4);
        try
        {
            e|=splay(bst, node);
            if (e!=128) throw e;
            count++; 
        }
        catch(assign2_exception::exception)
        {
            std::cout<<"\033[41;11m Error in part 5, case6!"<<". \033[0m\n";
        }
        delete bst;
        delete node; 
    }

    //Part 5 - case 7
    {
        assign2_exception::exception e = 0;
        BST *bst = create_bst_test(nullptr, comp);
        tree_node *node = create_tree_node_test(4);
        tree_node *(*target) = new tree_node*;
        try
        {
            insert_into_BST(bst, 2, target);
            insert_into_BST(bst, 4, target);

            e|=splay(bst, node);
            //std::cout<<e<<std::endl;
            if (e!=128) throw e;
            count++; 
        }
        catch(assign2_exception::exception)
        {
            std::cout<<"\033[41;11m Error in part 5, case7!"<<". \033[0m\n";
        }
        delete_tree(bst->root);
        delete bst;
        delete node; 
        delete target;
    }
    std::cout<<"The final result is "<<count<<"/33\n";
    std::cout<<"If you have patience, you can read my code and add some new test cases.\n";
    std::cout<<"Hope you a good score!\n";
    std::cout<<"If you find any bug or any wrong answer, please contact us.\n";
    return 0;
    }


    int comp(uint64_t a, uint64_t b){
        if (a == b) return 0;
        else if (a > b) return 1;
        else return -1; 
    };

    void inorder(BST * const bst, std::string *s){
        if (bst->root != NULL){
            if (bst->root->l_child != NULL) {
                BST *new_bst = new BST;
                new_bst->comp = bst->comp;
                new_bst->root = bst->root->l_child;
                inorder(new_bst, s);
                delete new_bst;
                new_bst = NULL;
            }
            //std::cout<<bst->root->data<<" "<<bst->root->node_count<<" "<<bst->root->tree_count<<"\n";
            s->append(std::to_string(bst->root->data));
            s->append(std::to_string(bst->root->node_count));
            s->append(std::to_string(bst->root->tree_count));
            if (bst->root->r_child != NULL) {
                BST *new_bst = new BST;
                new_bst->comp = bst->comp;
                new_bst->root = bst->root->r_child;
                inorder(new_bst, s);
                delete new_bst;
                new_bst = NULL;
            }
        }
        else return;
    };

    void preorder(BST * const bst, std::string *s){
        if (bst->root != nullptr){
            //std::cout<<bst->root->data<<" "<<bst->root->node_count<<" "<<bst->root->tree_count<<"\n";
            s->append(std::to_string(bst->root->data));
            s->append(std::to_string(bst->root->node_count));
            s->append(std::to_string(bst->root->tree_count));
            if (bst->root->l_child != NULL) {
                BST *new_bst = new BST;
                new_bst->comp = bst->comp;
                new_bst->root = bst->root->l_child;
                preorder(new_bst, s);
                delete new_bst;
                new_bst = NULL;
            }
            if (bst->root->r_child != nullptr) {
                BST *new_bst = new BST;
                new_bst->comp = bst->comp;
                new_bst->root = bst->root->r_child;
                preorder(new_bst, s);
                delete new_bst;
                new_bst = NULL;
            }
        }
        else return;
    };

    bool judge_bst(BST *bst, int &tree_c){
        if (bst->root != NULL){
            //std::cout<<bst->root->data<<" "<<bst->root->node_count<<" "<<bst->root->tree_count<<"\n";
            tree_c += bst->root->node_count;
            if (bst->root->l_child != NULL) {
                if (bst->comp(bst->root->data, bst->root->l_child->data) < 0) return false;
                BST *new_bst = new BST;
                new_bst->comp = bst->comp;
                new_bst->root = bst->root->l_child;
                judge_bst(new_bst, tree_c);
                delete new_bst;
                new_bst = NULL;
            }
            if (bst->root->r_child != NULL) {
                if (bst->comp(bst->root->data, bst->root->r_child->data) > 0) return false;
                BST *new_bst = new BST;
                new_bst->comp = bst->comp;  
                new_bst->root = bst->root->r_child;
                judge_bst(new_bst, tree_c);
                delete new_bst;
                new_bst = NULL;
            }
            if (bst->root->tree_count != tree_c) return false; 
        }
        else return true;
        return true;
    }

    tree_node * create_tree_node_test(uint64_t data){
        tree_node *node = new tree_node;
        node->data = data;
        node->node_count = 1;
        node->tree_count = 1;
        node->father = nullptr;
        node->l_child = nullptr;
        node->r_child = nullptr;
        return node;
    }

    BST * create_bst_test(tree_node *node, int (*comp)(uint64_t, uint64_t)){
        BST *bst = new BST;
        bst->comp = comp;
        bst->root = node;
        return bst;
    };

    tree_node * find_root(tree_node * node){
    while (node != nullptr){
        if (node->father != nullptr) node = node->father;
        else return node; 
    }
    return node;
    }

    void delete_from_root(tree_node * node){
        if (node != nullptr) {
            if (node->l_child != nullptr){
                delete_from_root(node->l_child);
            }
            if (node->r_child != nullptr){
                delete_from_root(node->r_child);
            }
            delete node;
        }
    }

void delete_tree(tree_node * node){
    node = find_root(node);
    delete_from_root(node);
};
    /*
        author: 
            灵犀
        co-author:
            方艺钧、邓值仁
    */
}

template <> 
r_type test<__COUNTER__>() {
    zlx::main(); 
    return {}; 
}