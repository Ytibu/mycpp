#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>

using std::ofstream;
using std::ifstream;
using std::istringstream;
using std::cout;
using std::map;
using std::string;
using std::cerr;


class DictionaryMap{
public:
    void read(const std::string &fileName); //逐行读取文件内容，并对文件内容进行分析操作
    void store(const std::string &fileName);//将读取的内容直接存储到文件中
private:
    std::string dealWord(const std::string &word);  //逐个处理单词
private:
    map<string, int> _dict;
};


void DictionaryMap::read(const std::string &fileName){
    ifstream ifs(fileName);
    if(!ifs){
        cerr << "open file error" << "\n";
        return;
    }

    string line;
    while(getline(ifs, line)){
        string word;

        istringstream iss(line);
        while(iss >> word){
            string newWord = dealWord(word);
            if(newWord != string()){
                ++_dict[newWord];
            }
        }
    }
    ifs.close();
}


std::string DictionaryMap::dealWord(const std::string &word){
    
    for(size_t i = 0; i != word.size(); ++i){
        if(!isalpha(word[i])){
            return string();
        }
    }
    return word;
}


void DictionaryMap::store(const std::string &fileName){
    ofstream ofs(fileName);
    if(!ofs){
        cerr << "Error opening file " << fileName << "\n";
        return;
    }

    for(auto &word : _dict){
        ofs << word.first << " " << word.second << "\n";
    }

    ofs.close();
}


int main(){
    DictionaryMap dict;
    cout << "Reading words.txt...\n";

    time_t start = time(NULL);
    dict.read("The_Holy_Bible.txt");
    time_t end = time(NULL);
    cout << "Reading took " << end - start << " seconds.\n";

    dict.store("dictMap.dat");
}
