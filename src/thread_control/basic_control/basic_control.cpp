#include <iostream>
#include <thread>
class background_task{
public:
    void operator() ()const{
        // do something
        std::cout << "do something" << std::endl;
    }
};

class thread_guard{
    std::thread& t;
public:
    explicit thread_guard(std::thread& t_): t(t_){}
    ~thread_guard(){
        if(t.joinable()){// 如果析构时候仍然没有被join或detach，则等待其结束
            t.join();
        }
    }
    thread_guard(thread_guard const&)=delete;               // 注意不可以复制构造
    thread_guard& operator=(thread_guard const&)=delete;    // 也不可赋值给其进行操作
};



int main(){
    background_task f;
    std::thread t(f); // 声明一个线程，传递其要调用的函数
    t.join();             // 声明等待其完成才返回，若不等待则可能效果不正常
    int i = 0;
    std::thread my_thread([&i]{   // C++11 新语法， lambda表达式实现
        //do something
        std::cout << "do something lambda:" << i++ << std::endl;  // 这里线程调用了主线程中的内容
    });
    // my_thread.detach(); // 如果分离不等待新线程结束，对i的访问非法可能访问悬空引用
    my_thread.join();

    std::thread t_auto(background_task{});
    thread_guard g(t_auto);
    // 做其他事，不需要显式控制t_auto，交由了thread_guard对象管理。
    return 0;
}