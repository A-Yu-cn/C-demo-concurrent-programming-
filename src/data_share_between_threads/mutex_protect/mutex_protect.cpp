#include <iostream>
#include <list>
#include <mutex>
#include <algorithm>
#include <stack>
#include "threadsafe_stack.h"
std::list<int> some_list;
std::mutex some_mutex;

void add_to_list(int new_value){
    std::lock_guard<std::mutex> guard(some_mutex);      // 使用RAII的方法获取锁并上锁，在构造时同时代表了lock被调用，在析构时候表示unlock被调用，即解锁
    some_list.push_back(new_value);
}

bool list_contains(int value_to_find){
    std::lock_guard<std::mutex> guard(some_mutex);
    return std::find(some_list.begin(),some_list.end(),value_to_find)!= some_list.end();
}

// 问题：若返回指针或者引用指向被保护的共享数据，则仍然会打破保护导致条件竞争问题，如下：
class some_data{
    int a;
    std::string b;
public:
    void do_something(){};
};
class data_wrapper{
    some_data data;
    std::mutex m;
public:
    template<typename Function>
    void process_data(Function func){
        std::lock_guard<std::mutex> l(m);
        func(data);                         // 传递受保护共享数据，可能有问题存在
    }
};

some_data * unprotected;

void malicious_function(some_data & protected_data){
    unprotected = &protected_data;
}
data_wrapper a;
void foo(){
    a.process_data(malicious_function);     // 传递了恶意函数操作
    unprotected->do_something();            // 无保护的方式访问了应该受保护的共享数据
}

// std::stack存在的固有竞争问题： 整体的访问操作并不是互斥的，可能会被其他线程插入操作
std::stack<int> s;
void f(){
    if(!s.empty()){                         // 内部为安全操作，但是此处后续不一定
        const int value = s.top();          // 可能在非空判断到读取top数据中间有其他线程pop数据
        s.pop();                            // 可能存在多个线程同时读取一个top数据，然后却pop出去未处理过的数据
        // 对value传递做操作
    }
}
// 解决方案1: 传入引用
// stack.pop(result);  // 并不好，因为要先有一个返回类型的实例才行，而且如果对象不可被赋值也是不行的。

// 解决方案2： 提供不抛出异常的拷贝、移动构造函数

// 解决方案3： 返回指针，指向弹出元素
// auto res = stack.pop();  // 使用智能指针包装的指针返回更好，可以避免对内存的控制的思虑

// 例子，线程安全的栈
threadsafe_stack<int> ts;






int main(){
    if(ts.empty())
        std::cout<<"it's empty"<<std::endl;
    ts.push(1);
    if(ts.empty())
        std::cout<<"it's empty"<<std::endl;
    else
        std::cout<<"it's  not empty:"<<*ts.pop()<<std::endl;
    return 0;
}