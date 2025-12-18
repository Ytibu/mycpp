#include <unistd.h>
#include <iostream>
#include <string>
#include <thread>
#include <fstream>

using std::cout;
using std::endl;
using std::string;

/**
 * 每个类使用文件指针管理文件，生存周期结束时，会自动调用析构函数，释放文件指针。
 * 确保了不用手动释放资源的安全问题
 */

class SafeFile {
public:
    SafeFile(FILE *fp)  // 构造函数：托管资源
    : _fp(fp) 
    {
        cout << "SafeFile::SafeFile()" << endl;
    }
    ~SafeFile() {   //析构函数：释放资源
        if(_fp){
            fclose(_fp);
            cout << "fclose()" << endl;
        }
        cout << "SafeFile::~SafeFile()" << endl;
    }

    void write(const string & msg) {
        fwrite(msg.c_str(), 1,msg.size(), _fp);
    }
private:
    FILE *_fp;

};


int main() {

    SafeFile sf(fopen("test.txt", "a+"));
    SafeFile sf2(fopen("test.txt", "a+"));
    sf.write("hello world");
    sf2.write("hello world\n");

    return 0;
}