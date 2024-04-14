#include <iostream>
#include <thread>
#include <vector>
#include "data.h"
void some_function(){};
void some_other_function(int i){};

std::thread f(){                            // 从函数内部返回thread对象
    return std::thread(some_function);
}
void g(std::thread t){};
void g_caller(){                            // 向函数传递归属权
    std::thread t1(some_function);
    g(std::move(t1));
}

// basic_control中的thread_guard类可能存在其对象生存周期超过thread对象的问题，导致异常情况发生
class scoped_thread{                //此类通过移动归属权，将thread完全由对象控制，保证释放顺序正常
    std::thread t;
public:
    explicit scoped_thread(std::thread t_): t(std::move(t_)){
        if(!t.joinable())
            throw std::logic_error("No thread");
    }
    ~scoped_thread(){
        t.join();   // 传入时保证可join，释放前保证join，不会出现问题
    }
    scoped_thread(scoped_thread const&)=delete;
    scoped_thread& operator=(scoped_thread const&)=delete; // 保证不可赋值不可复制

};



int main(){
    std::thread t1(some_function);
    std::thread t2 = std::move(t1);         // 线程归属权转交
    t1 = std::thread(some_other_function,2);  // 启动新线程，归属权移交给t1，因为本身就是临时变量因此可以隐式移动
    std::thread t3;
    t3 = std::move(t2);                     // t3关联原本的线程
    t1.join();
    t3.join();
    // t1 = std::move(t3);                  // 不可如此操作，会导致已关联线程的t1重复赋值，导致terminate()被调用
    int local_state = 1;
    scoped_thread t{std::thread(func(local_state))};
    
    // 由于支持移动语义，容器同样可以写出如此的方法
    std::vector<std::thread> threads;
    for(int i=0;i<20;i++){
        threads.emplace_back(some_other_function,i);
    }
    std::thread::id detach_id = threads[10].get_id();   // 获取id以判别不同的线程句柄
    for(auto & entry:threads){
        if(entry.get_id() != detach_id) //可以进行判别是否为目标线程，且可以比较大小，不过无具体含义
            entry.join();
        else
            entry.detach();
    }
    return 0;
}