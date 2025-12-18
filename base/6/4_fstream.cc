#include <iostream>
#include <fstream>
using std::cout;
using std::ifstream;
using std::ofstream;

void test_file_ifstream()
{
    ifstream ifs;
    ifs.open("3_explicit.cc");

    if(!ifs.good()){
        cout << "file open failed" << "\n";
        return;
    }

    /*兼容c的方式：行读取*/
    char buf[1024] = {0};
    while (ifs.getline(buf, sizeof(buf)))
    {
        cout << buf << std::endl;
    }

    /*利用string 类：行读取*/
    std::string line;
    while (std::getline(ifs, line))
    {
        cout << line << std::endl;
    }

    
}

void test_file_ofstream()
{
}

int main()
{
    test_file_ifstream();
    test_file_ofstream();
    return 0;
}