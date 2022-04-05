#include <csetjmp>

jmp_buf jump_buf; 

#include <iostream> 
#include <optional>
#include <functional> 

#ifndef __WIN64__
#include "assign2.hpp"
#else 
#include "assign2.cpp"
#endif

std::function<void ()> run_next; 

template <int x> 
std::optional<std::string> test(); 

#include "test.hpp" 

extern thread_local std::unordered_set<void *> records; 

template <int x> 
void run(); 

template <> 
void run<test_number>() {
    std::cout << "本次测试到此结束。" << std::endl 
        << "====================" << std::endl << std::endl; 
}

template <int v> 
void run() {
    std::cout << "正在进行第 " << v << " 组测试：" << std::endl; 
    if (!setjmp(jump_buf)) {
        try {
            auto r (test<v>()); 
            if (!r && records.empty() && bst_record.empty()) 
                std::cout << "测试通过！" << std::endl;     
            else if (r)
                std::cout << "测试失败，错误原因：" << *r << std::endl; 
            else 
                std::cout << "测试失败，错误原因：内存泄漏。" << std::endl; 
        } catch (std::string const &cause) {
            std::cout << "测试异常，原因：" << cause << std::endl; 
        } catch (std::exception const &e) {
            std::cout << "测试内抛出异常，原因：" << e.what() << std::endl; 
        }
        std::cout << "====================" << std::endl << std::endl; 
    }
    for (auto p: records)
        free(p); 
    records.clear(); 
    for (auto p: bst_record)
        free(p); 
    bst_record.clear(); 

    run<v+1>(); 
}

#include <cstdlib>
#include <cstdio>  
#include <csignal>
#include <cstring>

#ifndef __WIN64__
void segfault_sigaction(int signal, siginfo_t *si, void *arg) {
#else 
void segfault_sigaction(int s) {
#endif
    std::cout << "测试异常：Segmentation Fault! " << std::endl 
        << "====================" << std::endl << std::endl; 
    longjmp(jump_buf, 0); 
}

void register_seg_fault() {

#ifndef __WIN64__
    struct sigaction sa;
        
    memset(&sa, 0, sizeof(struct sigaction));
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = segfault_sigaction;
    sa.sa_flags   = SA_SIGINFO;

    sigaction(SIGSEGV, &sa, NULL);
#else 
    signal(SIGSEGV, segfault_sigaction); 
#endif

}

int main() {
    register_seg_fault(); 
    run<0>(); 
}
