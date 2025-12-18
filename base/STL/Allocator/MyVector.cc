#include <memory>
#include <iostream>

using std::cout;
using std::endl;
using std::allocator;

template<typename T>
class Vector
{
public:
    Vector();
    ~Vector();

    void push_back(T value);
    void pop_back();

    int size() const;
    int capacity() const;

private:
    void reallocate();

private:
    static std::allocator<T> _alloc;
    T* _start;
    T* _finish;
    T* _end_of_storage;
};

template<typename T>
std::allocator<T> Vector<T>::_alloc;

template<typename T>
Vector<T>::Vector()
:_start(nullptr)
,_finish(nullptr)
,_end_of_storage(nullptr)
{

}

template<typename T>
Vector<T>::~Vector()
{
    if(_start){
        while (_start != _finish)
        {
            _alloc.destroy(--_finish);
        }
        
        _alloc.deallocate(_start, capacity());
    }
}

/**
 * 首先判断是否已经满元素，进行空间开辟，否则直接移动_finish
 */
template<typename T>
void Vector<T>::push_back(T value)
{
    if(size() == capacity()){
        reallocate();
    }
    if(size() < capacity()){
        _alloc.construct(_finish++, value);
    }
    
}

template<typename T>
void Vector<T>::pop_back()
{
    if(size() > 0){
        _alloc.destroy(--_finish);
    }
    
}

template<typename T>
int Vector<T>::size() const
{
    return _finish - _start;
}

template<typename T>
int Vector<T>::capacity() const
{
    return _end_of_storage - _start;
}

template<typename T>
void Vector<T>::reallocate()
{
    int oldCapacity = capacity();
    int newCapacity = oldCapacity > 0 ? 2 * oldCapacity : 1;
    T* temp = _alloc.allocate(newCapacity);
    
    if(_start){
        std::uninitialized_copy(_start, _finish, temp);
        while(_start != _finish){
            _alloc.destroy(--_finish);
        }
        _alloc.deallocate(_start, oldCapacity);
    }

    _start = temp;
    _finish = temp + oldCapacity;
    _end_of_storage = temp + newCapacity;
}



void disPlay(const Vector<int> &vec){
    std::cout << "size(): " << vec.size() << "\n";
    std::cout << "capacity(): " << vec.capacity() << "\n";
    std::cout << "\n";
}

int main(){
    Vector<int> vec;

    vec.push_back(1);
    disPlay(vec);

    vec.push_back(2);
    disPlay(vec);

    vec.push_back(3);
    disPlay(vec);

    vec.push_back(4);
    disPlay(vec);

    vec.push_back(5);
    disPlay(vec);

    vec.push_back(6);
    disPlay(vec);

    vec.pop_back();
    disPlay(vec);

}