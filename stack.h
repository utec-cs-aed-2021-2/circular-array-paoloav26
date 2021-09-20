#include "circulararray.h"

template <typename T>
class StackArray : public CircularArray<T> { 
    public:
    template<typename T>
    void push(T data){
        push_front(data);
    }

    template<typename T>
    T pop(T data){
        return pop_front();
    }
};