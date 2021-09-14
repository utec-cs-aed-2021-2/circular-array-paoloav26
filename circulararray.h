#include <iostream>
using namespace std;

template <class T>
class CircularArray
{
private:
    T *array;
    int capacity;
    int back, front;
    
public:
    CircularArray();
    CircularArray(int _capacity);
    virtual ~CircularArray();
    void push_front(T data);
    void push_back(T data);
    void insert(T data, int pos);
    T pop_front();
    T pop_back();
    bool is_full();
    bool is_empty();
    int size();
    void clear();
    T &operator[](int);
    void sort();
    bool is_sorted();
    void reverse();
    string to_string(string sep=" ");

private:
    int next(int);
    int prev(int);
};

template <class T>
void CircularArray<T>::insert(T data, int pos){
    if(size()==capacity){
        T *temp_array =  new T [capacity + 3];
        int index=front;
        for(int i=0;i<capacity;i++){
            temp_array[i]=array[index];
            index=next(index);
        }
        back = size()-1;
        front = 0;
        capacity+=3;

        array=temp_array;
    }

    T *temp2_array =  new T [capacity];
    int index2=front;
    for(int i=0;i<pos;i++){
        temp2_array[i]=array[(front+i) % capacity];
        
    }
    for(int i=pos;i<capacity;i++){
        temp2_array[i+1]=array[(front+i) % capacity];
        
    }
    
    back=next(back);
    array=temp2_array;
    array[(front+pos) % capacity] = data;
}

template <class T>
void CircularArray<T>::push_back(T data){

    if(front == -1 && back == -1){
        front=0;
        back=0;
        array[back]=data;
    }

    else if(is_full()){
        T *temp_array =  new T [capacity + 3];
        int index=front;
        for(int i=0;i<capacity;i++){
            temp_array[i]=array[index];
            index=next(index);
        }
        back = size()-1;
        front = 0;
        capacity+=3;

        array=temp_array;

        back=next(back);
        array[back]=data;
    }

    else{
        back=next(back);
        array[back]=data;
    }

    return;
}

template <class T>
void CircularArray<T>::push_front(T data){

    if(front == -1 && back == -1){
        front=0;
        back=0;
        array[back]=data;
    }
    
    else if(is_full()){
        T *temp_array =  new T [capacity + 3];
        int index=front;
        for(int i=0;i<capacity;i++){
            temp_array[i]=array[index];
            index=next(index);
        }
        back = size()-1;
        front = 0;
        capacity+=3;

        array=temp_array;

        front=prev(front);
        array[front]=data;
    }

    else{
        front=prev(front);
        array[front]=data;
    }

    return;
}

template <class T>
T CircularArray<T>::pop_front(){

    if(size()==0){
        return 0;
    }

    T temp=array[front];

    if(size() == 1){
        front = back = -1;
    }

    else{
        front=next(front);
    }
    
    return temp;
}

template <class T>
T CircularArray<T>::pop_back(){

    if(size()==0){
        return 0;
    }

    T temp=array[back];

    if(size() == 1){
        front = back = -1;
    }

    else{
        back=prev(back);
    }

    return temp;
}

template <class T>
bool CircularArray<T>::is_empty(){
    if( front == -1 && back==-1){
        return true;
    }
    return false;
}

template <class T>
bool CircularArray<T>::is_full(){
    return (back+1) % capacity == front;
}

template <class T>
bool CircularArray<T>::is_sorted(){
    int j=front;
    for(int i=0;i<size();i++){
        if(array[j]>next(array[j])){
            return false;
        }
        j=next(j);
    }
    return true;
}

template <class T>
void CircularArray<T>::sort(){

    for (int i = 0; i < size()-1; i++){
        for (int j = 0; j < size()-i-1; j++){
            if(array[(front+j) % capacity]>array[(front+j+1) % capacity]){
                T temp=array[(front+j) % capacity];
                array[(front+j) % capacity] = array[(front+j+1) % capacity];
                array[(front+j+1) % capacity] = temp;
            }
        }
    }   
}

template <class T>
void CircularArray<T>::reverse(){
    T *temp_array=new T[capacity];
    int f = front;
    int b = back;
    do{
        temp_array[b]=array[f];
        b=prev(b);
        f=next(f);
    }while(f != front);

    array=temp_array;
    return;
}

template <class T>
int CircularArray<T>::size(){

    if(front == -1 && back == -1){
        return 0;
    }

    return front > back ? (capacity - front + back + 1) : (back - front + 1);
}

template <class T>
T &CircularArray<T>::operator[](int index){
    return array[(front+index) % capacity];
}

/* los que vinieron */

template <class T>
CircularArray<T>::CircularArray()
{
    CircularArray(0);
}

template <class T>
CircularArray<T>::CircularArray(int _capacity)
{
    this->array = new T[_capacity];
    this->capacity = _capacity;
    this->front = this->back = -1;
}

template <class T>
CircularArray<T>::~CircularArray()
{
    delete[] array;
}

template <class T>
int CircularArray<T>::prev(int index)
{
    return (index == 0) ? capacity - 1 : index - 1;
}

template <class T>
int CircularArray<T>::next(int index)
{
    return (index + 1) % capacity;
}

template <class T>
string CircularArray<T>::to_string(string sep)
{
    string result = "";
    int j=front;
    for (int i = 0; i < size(); i++){
        result += std::to_string(array[j]) + sep;
        j = next(j);
    }
    return result;    
}
