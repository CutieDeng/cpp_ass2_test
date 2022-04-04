#include <iostream> 
#include <optional>
#include <functional> 

#ifndef __WIN64__
#include "assign2.hpp"
#else 
#include "assign2.cpp"
#endif

#include <thread>
#include <chrono> 
#include <atomic>
#include <future>

std::function<void ()> run_next; 

template <int x> 
std::optional<std::string> test(); 

#include "test.hpp" 

extern std::unordered_set<void *> records; 
extern std::unordered_set<void *> bst_record; 

template <int x> 
void run(); 

void invoke(); 

void clear_record(); 

template <> 
void run<test_number>() {
    run_next = nullptr;
    std::cout << "本次测试到此结束。" << std::endl 
        << "====================" << std::endl << std::endl; 
}

template <int v> 
void run() {
    std::cout << "正在进行第 " << v << " 组测试：" << std::endl; 
    run_next = run<v+1>; 
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
    
    clear_record(); 
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
    
    clear_record(); 
    invoke(); 
    exit(0); 
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

    run_next = run<0>; 

    invoke(); 
}

void clear_record() {
    for (auto p : records) 
        free(p); 
    records.clear(); 

    for (auto p : bst_record) 
        free(p); 
    bst_record.clear(); 
}

void invoke() {
    while (run_next) {
        using namespace std::literals::chrono_literals; 

        // std::thread t ([=] {run_next(); }); 
        std::promise<void> p; 
        std::thread ([&] { run_next(); p.set_value(); }).detach(); 

        auto f = p.get_future(); 

        if (f.wait_for(7s) == std::future_status::timeout) {
            clear_record(); 
        }
    }
}