#include <iostream>
#include <thread>

void f(int i,std::string const& s){

}

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
};
using widget_data = struct widget_data;

void update_data_for_widget(widget_id w,widget_data &data){
    data.data = 1;
}
void display_status(widget_data data){
    std::cout << "data:" << data.data<<std::endl;
}
void oops_again(widget_id w){
    widget_data data{};
    // std::thread t(update_data_for_widget,w,data); // 注意这里已经会先复制一次，后边传入的引用已经不是此处的对象
    std::thread t(update_data_for_widget,w,std::ref(data));
    display_status(data);
    t.join();
    display_status(data);
}

int main(){
    oops_again(1);
    return 0;
}