#include <iostream>
#include <thread>

void f(int i,std::string const& s){

}
// 传值操作
void oops(int some_param){
    char buffer[1024];
    sprintf(buffer,"%i",some_param);
    //std::thread t(f,3,buffer);  //注意这里可能导致buffer转换成string类型对象过程中函数退出导致局部数组销毁导致错误
    std::thread t(f,3,std::string(buffer));  // 显式构造string对象，可以解决问题。
    t.detach();
}

using widget_id = int;
struct widget_data {
    int data;
    double data_;
    widget_data() = default;
    widget_data(int d1,double d2):data(d1),data_(d2){};
};
using widget_data = struct widget_data;

void update_data_for_widget(widget_id w,widget_data &data){
    data.data = 1;
}
void display_status(widget_data data){
    std::cout << "data:" << data.data<<std::endl;
}

// 针对需要进行引用传递的操作
void oops_again(widget_id w){
    widget_data data{};
    // std::thread t(update_data_for_widget,w,data); // 注意这里已经会先复制一次，后边传入的引用已经不是此处的对象
    std::thread t(update_data_for_widget,w,std::ref(data));
    display_status(data);
    t.join();
    display_status(data);
}


//针对需要传递对象归属权的操作
using big_object = widget_data; //只是为了编译通过
void process_big_object(std::unique_ptr<big_object> obj){};
void oops_big_data(big_object obj){
    std::unique_ptr<big_object> p(new big_object);
    auto p2 = std::make_unique<big_object>();// 也可以这样，C++14之后可以
    std::thread t(process_big_object,std::move(p));
    t.join();
}


int main(){
    oops_again(1);
    return 0;
}