#include "circulararray.h"

template <typename T>
class QueueArray : public CircularArray<T> { 
    public:
    template<typename T>
    void enqueue(T dato){
        push_back(dato);
    }

    template<typename T>
    T dequeue(){
        return pop_front();
    }
};