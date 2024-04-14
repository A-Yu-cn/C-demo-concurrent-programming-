#ifndef data_h
#define data_h
struct func
{
    int &i;
    func(int &i_):i(i_){};
    void operator()(){
        for(unsigned int j=0;j<1000;j++){
            std::cout << i <<std::endl;// 做一些操作
        }
    };
};
#endif data_h