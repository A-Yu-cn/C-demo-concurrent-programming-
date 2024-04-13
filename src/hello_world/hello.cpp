#include <iostream>
#include <thread>
void hello(){
    std::cout << "Hello Concurrent World!" << std::endl;
}
int main(){
    std::thread t(hello); // 声明一个线程，传递其要调用的函数
    t.join();             // 声明等待其完成才返回，若不等待则可能效果不正常
    return 0;
}