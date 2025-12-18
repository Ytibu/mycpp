#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>

using std::cout;
using std::istringstream;
using std::ifstream;
using std::unordered_map;
using std::string;
using std::cerr;

class WordsTrans{
public:
    /** 
     * 读取：先读取每行的第一个字符串，然后将剩下的部分整行读取
     * 建立：直接将第一个字符串作为KEY, 剩下的内容视作VALUE。
     * 直接存储
     */
    void buildMap(const string& filename){
        ifstream ifs(filename);
        if(!ifs){
            cerr << " open file error: " << filename << std::endl;
        }
        string line;
        string word;
        while (ifs >> word, getline(ifs, line))
        {
            map_[word] = line.substr(1);
        }
        

        ifs.close();
    }

    /**
     * 行读取文件，语句的输出也是按照行划分
     * 查找每行的所有字符串是否是字典的内容，根据返回的迭代器判断是否找到
     * 没找到直接输出，找到了输出it->second
     */
    void Trans(const string& filename){
        ifstream ifs(filename);
        if(!ifs){
            cerr << "open file error: " << filename << std::endl;
        }
        string line;
        while(getline(ifs, line)){
            istringstream iss(line);
            string words;
            while (iss >> words)
            {
                auto it = map_.find(words);
                if(it == map_.end()){
                    cout << words << " ";
                }else{
                    cout << it->second << " ";
                }
            }cout << "\n";
            
        }


        ifs.close();

    }

private:
    unordered_map<string, string> map_; //生成string: 多个string
};


int main(){

    WordsTrans trans;
    trans.buildMap("map.txt");
    trans.Trans("file.txt");

}