#include <iostream>
#include <istream>
using std::cout;
using std::endl;
using std::cin;
using std::istream;


void checkStreamStatus(istream & is){
    cout << "is.good(): " << is.good() << endl; // good状态：输入流正常
    cout << "is.bad(): " << is.bad() << endl;   // bad状态：输入流错误，无法继续使用
    cout << "is.fail(): " << is.fail() << endl; 
    // fail状态：输入流错误，可以通过调用clear()方法恢复
    cout << "is.eof(): " << is.eof() << endl;   
    // eof状态：输入流结束,输入流已经到达文件末尾或输入结束
    cout << endl;
}

int main(){

    int num = 0;

    cout << "检查输入流的状态前" << endl;
    checkStreamStatus(cin);

    cin >> num;

    cout << "检查输入流状态后" << endl;
    checkStreamStatus(cin);

    if(!cin.good()){
        cin.clear();
        cin.ignore();
        //cin.ignore(1000, '\n');   //忽略1000个字符，直到遇到换行符
        //cin.ignore(1000);    //忽略1000个字符
        checkStreamStatus(cin);
    }


}