#include <stack>

template<typename T>
class linkedList {
private:
    struct node {
        T value;
        node* next;
        node* prev;
    };

    node* head, * tail;
    int elements;
    
    struct task {
        /*
        -2 for pop back
        -1 for pop front
        1 for push back
        2 for push front

        # value is irrelevant in push operations
        */

        int type;
        T value;
    };

    std::stack < task > tasksStack;

public:
    linkedList();
    void push_back(T value);
    void push_front(T value);
    void display();
    void displayDetail();
    void pop_back();
    void pop_front();
    void undo();
    int size();
    T back();
    T front();
};
