#include <iostream>
#include <thread>
class background_task{
public:
    void operator() ()const{
        // do something
        std::cout << "do something" << std::endl;
    }
};

int main(){
    background_task f;
    std::thread t(f); // 声明一个线程，传递其要调用的函数
    t.join();             // 声明等待其完成才返回，若不等待则可能效果不正常
    return 0;
}