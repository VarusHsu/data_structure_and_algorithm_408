# ifndef CONTIGUOUS_H_
# define CONTIGUOUS_H_
# define INITIAL_CAPACITY (0)
# define THRESHOLD (256)

template<typename T>

class Contiguous{
    private: 
    T* header; // 线性表头指针
    int size; // 线性表容量
    int capacity;  // 线性表容量
    void grow();
    public:
    Contiguous();
    ~Contiguous();
    bool is_empty();
    T* pop_back();
    void push_back(T);
    void clear();
    int length();
    T* index_at(int);
    void insert_at(int, T);
    T* delete_at(int);
    void print(); // for test;
};
# endif