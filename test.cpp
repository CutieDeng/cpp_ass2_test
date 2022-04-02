#include <iostream> 
#include <optional>
#include <functional> 
#include "assign2.hpp"

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
    run_next = run<v+1>; 
    try {
        auto r (test<v>()); 
        if (!r && records.empty()) 
            std::cout << "测试通过！" << std::endl;     
        else if (r)
            std::cout << "测试失败，错误原因：" << *r << std::endl; 
        else 
            std::cout << "测试失败，错误原因：内存泄漏。" << std::endl; 
    } catch (std::string cause) {
        std::cout << "测试异常，原因：" << cause << std::endl; 
    }
    std::cout << "====================" << std::endl << std::endl; 
    
    for (auto p: records)
        free(p); 
    records.clear(); 

    run<v+1>(); 
}

#include <cstdlib>
#include <cstdio>  
#include <csignal>
#include <cstring>

void segfault_sigaction(int signal, siginfo_t *si, void *arg) {
    std::cout << "测试异常：Segmentation Fault! " << std::endl 
        << "====================" << std::endl << std::endl; 
    
    for (auto p: records) 
        free(p); 
    records.clear(); 

    run_next(); 
    exit(0); 
}

void register_seg_fault() {
   struct sigaction sa;
        
    memset(&sa, 0, sizeof(struct sigaction));
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = segfault_sigaction;
    sa.sa_flags   = SA_SIGINFO;

    sigaction(SIGSEGV, &sa, NULL);
}

int main() {
    register_seg_fault(); 

    run<0>(); 
}
