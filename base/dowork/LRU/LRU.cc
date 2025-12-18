#include <unordered_map>
#include <list>
#include <string>
#include <utility>
#include <iostream>

using std::list;
using std::unordered_map;
using std::string;
using std::pair;

template<typename K, typename V>
class LRU{
public:
    LRU(int capacity):_capacity(capacity){}
    void Put(K key, V value);   //上传：存在的更新内容，不存在的根据条件生成新的内容
    V Get(K key);   //存在则返回，不存在返回错误(离线加载)
    void Print();
private:
    int _capacity;
    list<pair<K,V>> _nodes;
    unordered_map<K, typename list<pair<K, V>>::iterator> _cache;
};

/**
 * 利用缓存的哈希特性：快速查找是否存在
 * 对于存在的node，利用缓存快速输出的迭代器，直接更新node的内容
 * 将最新使用的node置于头
 * 对于不存在的节点，直接利用删除nodes的最后一个，并更新最后一个node的内容
 * 将更新的node置于头
 */
template<typename K, typename V>
void LRU<K,V>::Put(K key, V value){
    auto it = _cache.find(key);
    if(it != _cache.end()){
        it->second->second = value;
        _nodes.splice(_nodes.begin(), _nodes, it->second); 
    }else{

        if((size_t)_capacity == _nodes.size() ){
            auto lastNode = _nodes.back();
            _cache.erase(_cache.find(lastNode.first));
            //获取最后一个节点的first，然后交给chache，cache快速查找并删除自己对应于node最后一个节点的内容
            _nodes.pop_back();
           
        }
        //满了需要删除最后一个，但是最终都是将这个新值添加到_cache和_nodes
        _nodes.push_front(pair<K,V>(key, value));
        _cache[key] = _nodes.begin();    
    }
}

/**
 * 查找内容
 * 利用_cache快速查找，
 * 查找到内容则将_nodes中的对应的节点置于头部
 * 未查找到直接返回报错
 */
template<typename K, typename V>
V LRU<K,V>::Get(K key){
    auto it = _cache.find(key);
    if(it != _cache.end()){
        _nodes.splice(_nodes.begin(), _nodes, it->second); //查找的内容置于头
        return it->second->second;
    }else{
        return -1;
    }
}

template<typename K, typename V>
void LRU<K,V>::Print(){
    for(auto &element: _nodes){
        std::cout << element.first << " " <<element.second << " ";
    }std::cout << "\n";
}


int main(){


    LRU<string, int> lru(5);

    lru.Put("丁",100);
    lru.Print();
    std::cout << "lru.Get(\"丁\"): " << lru.Get("丁") << "\n";

    lru.Put("李",99);
    lru.Print();
    std::cout << "lru.Get(\"丁\"): " << lru.Get("丁") << "\n";

    lru.Put("赵",98);
    lru.Print();
    std::cout << "lru.Get(\"丁\"): " << lru.Get("丁") << "\n";

    lru.Put("孙",88);
    lru.Print();
    std::cout << "lru.Get(\"丁\"): " << lru.Get("丁") << "\n";

    lru.Put("丁",88);
    lru.Print();
    std::cout << "lru.Get(\"丁\"): " << lru.Get("丁") << "\n";

    lru.Print();
}