
#include "threadsafe_stack.h"
template<typename T>
threadsafe_stack<T>::threadsafe_stack(const threadsafe_stack& other){
    std::lock_guard<std::mutex> lock(other.m);
    data = other.data;
}
template<typename T>
void threadsafe_stack<T>::push(T new_value){
    std::lock_guard<std::mutex> lock(m);
    data.push(std::move(new_value));
}

template<typename T>
std::shared_ptr<T> threadsafe_stack<T>::pop(){
    std::lock_guard<std::mutex> lock(m);
    if(data.empty()) throw empty_stack();
    std::shared_ptr<T> const res(std::make_shared<T>(data.top()));
    data.pop();
    return res;
}

template<typename T>
void threadsafe_stack<T>::pop(T& value){
    std::lock_guard<std::mutex> lock(m);
    if(data.empty()) throw empty_stack();
    value = data.top();
    data.pop();
}
template<typename T>
bool threadsafe_stack<T>::empty() const{
    std::lock_guard<std::mutex> lock(m);
    return data.empty();
}


//template class threadsafe_stack<int>;   // 注意这里必须要显式实例化出int类型的模板，不然链接报错，而且实例化一次避免多个地方引用多次实例化可能加速编译