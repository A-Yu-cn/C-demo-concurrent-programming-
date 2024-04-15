#ifndef threadsafe_stack_h
#define threadsafe_stack_h

#include <exception>
#include <memory>
#include <mutex>
#include <stack>

struct empty_stack: std::exception{
    const char* what() const {throw("");}
};

template<typename T>
class threadsafe_stack{
private:
    std::stack<T> data;
    mutable std::mutex m;    
public:
    threadsafe_stack(){};
    threadsafe_stack(const threadsafe_stack&);
    threadsafe_stack& operator=(const threadsafe_stack&)=delete;
    void push(T new_value);
    std::shared_ptr<T> pop();
    void pop(T& value);
    bool empty() const;
};

#include "threadsafe_stack.cpp" // 这样也可以实现避免使用模板类链接报错的问题
#endif threadsafe_stack_h