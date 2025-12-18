#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using std::cout;
using std::string;
using std::vector;
using std::cerr;

// 记录（单词-频数）
struct Record{
    Record(const string &word, int frequency)
    : _word(word), _frequency(frequency) {}

    string _word;
    int _frequency;
};

bool operator<(const Record &lhs, const Record &rhs){
    return lhs._word < rhs._word;
}

class DictionaryVector{
public:
    /* 存储字典 */
    void store(const std::string &fileName){
        std::ofstream ofs(fileName);
        if(!ofs){
            cerr << "Error: can not open file " << fileName << "\n";
        }

        /* 按字典序写入文件*/
        for(size_t idx = 0; idx < _dict.size(); ++idx){
            ofs << _dict[idx]._word << " " << _dict[idx]._frequency << "\n";
        }
        ofs.close();
    }


    /*文件读取，并存储在vector中*/
    void read(const std::string &fileName){
        std::ifstream ifs(fileName);
        if(!ifs){
            std::cerr << "File not found" << "\n";
            return;
        }

        string line;
        while(getline(ifs, line)){
            string word;

            std::istringstream iss(line);
            while(iss >> word){
                //获取每行内容，处理出单词，将单词放入字典容器中
                string newWord = dealWord(word);
                insert(newWord);
            }
        }

        /*将存储后的字典容器进行排序，按照字典容器的元素Record的word字段进行排序*/
        std::sort(_dict.begin(), _dict.end());

        ifs.close();
    }

    /* 处理单词 */
    string dealWord(const string &word){
        for(int i = 0; i < word.size(); i++){
            // if(word[i] >= 'A' && word[i] <= 'Z'){
                
            // }
            if(!isalpha(word[i])){  // 判断是否是字母
                return string();    // 返回空串
            }
        }
        return word;
    }

    /* 插入单词 */
    void insert(const string &word){
        if(word == string()){   //排除空串
            return;
        }
        size_t idx = 0;

        /*遍历字典，如果单词和字典中的单词相同，则将字典中的对应单词频率加1*/
        for(idx = 0; idx < _dict.size(); ++idx){
            if(word == _dict[idx]._word){
                ++_dict[idx]._frequency;
                break;
            }
        }

        /*如果没有找到(遍历的idx等于字典大小)，则将单词加入字典*/
        if(idx == _dict.size()){
            _dict.push_back(Record(word,1));
        }
    }
private:
    vector<Record> _dict;
};

int main(){

    DictionaryVector dict;

    cout << "Reading..." << "\n";
    time_t start = time(NULL);
    dict.read("The_Holy_Bible.txt");
    time_t end = time(NULL);
    cout << "Reading time: " << end - start << " seconds" << "\n";

    dict.store("dictVec.dat");


}