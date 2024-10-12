/* xinji2301 whn 3230104148 10.12 */
#include <initializer_list>
#include <iostream>

template <typename T>
class SingleLinkedList
{
private:
    class Node
    {
    private:
        T data;
        Node *next = nullptr;
        Node(T _val) { data = _val; }

        friend class SingleLinkedList<T>;
    };
    Node* head = nullptr;
    int size = 0;
    Node* currentPos = nullptr;


    void _emptyList();
    void _copy(const SingleLinkedList<T> &_l);
public:
    T getCurrentVal() const; // 返回当前位置的值
    void setCurrentVal(const T &_val); // 设置当前位置的值
    bool isEmpty() const; // 判断链表是否为空

    int getSize() const;
    void emptyList();
    SingleLinkedList() {};
    ~SingleLinkedList();
    SingleLinkedList(std::initializer_list<T> _l);
    void printList() const;
    SingleLinkedList(const SingleLinkedList<T> &_l);
    SingleLinkedList<T>& operator=(const SingleLinkedList<T> &_l);
    bool find(const T &_val);
    void insert(T _val); // 在当前位置后插入一个元素
    void remove(); // 删除当前位置后面的元素
};

// 以 下 是 我 写 的 作 业 的 主 要 实 现 内 容 ，其 他 基 本 没 动 过

// 1. T getCurrentVal() const 实现
template <typename T>
T SingleLinkedList<T>::getCurrentVal() const
{
    if (currentPos == nullptr)
    {
        // 你说的若当前位置为空，则报错"Empty current position! Can't get value!"并停止退出；
        std::cerr << "Empty current position! Can't get value!" << std::endl;
        exit(EXIT_FAILURE); // 真的退了
    }
    return currentPos->data; // 返回当前位置的值
}

// 2. void setCurrentVal(const T &_val) 实现
template <typename T>
void SingleLinkedList<T>::setCurrentVal(const T &_val)
{
    if (currentPos == nullptr)
    {
        // 若当前位置为空，则报错"Empty current position! Can't setvalue!"并停止退出；
        std::cerr << "Empty current position! Can't set value!" << std::endl;
        exit(EXIT_FAILURE);
    }
    currentPos->data = _val; // set当前的值
}

// 3. bool isEmpty() const 实现 注意这里名称的改动，课上代码多了个l?
template <typename T>
bool SingleLinkedList<T>::isEmpty() const
{
    return true ? head == nullptr : false ;
}

// 4. void insert(T _val) 实现
template <typename T>
void SingleLinkedList<T>::insert(T _val)
{
    Node* newNode = new Node(_val);

    if (isEmpty()) // 空链表的情况,若为空链表则插入一个元素
    {
        head = newNode;
        currentPos = head;
    }
    else if (currentPos != nullptr) // 非空链表，插入到 currentPos 后面
    {
        newNode->next = currentPos->next;
        currentPos->next = newNode;
    }
    else
    {
        std::cerr << "shituzaikongptrcharu" << std::endl;
        delete newNode; // 防止内存泄漏
        exit(EXIT_FAILURE); // 前面的报错都退出了，所以我猜这个要退出
    }

    ++size;
}

// 5. void remove() 实现
template <typename T>
void SingleLinkedList<T>::remove()
{
    if (isEmpty()) // 空链表
    {
        std::cerr << "ruodangqianweizhiweikongzebujinxingcaozuo" << std::endl;
        return;
    }

    if (currentPos == nullptr) // currentPos 不应为空
    {
        std::cerr << "zhegeptrshiinvalid" << std::endl;
        exit(EXIT_FAILURE); // 前面的报错都退出了，所以我猜这个也要退出
    }

    if (currentPos == head) // 如果 currentPos 是 head，处理删除头节点的情况
    {
        Node* nodeToDelete = head;  // head->A->B  head->B n2delte->A
        head = head->next;
        delete nodeToDelete;
        --size;

        if (size == 0) // 删除后链表为空
        {
            head = nullptr;
            currentPos = nullptr;
        }
        else
        {
            currentPos = head; // 将 currentPos 移动到新的 head
        }
        return;
    }

    // 普通情况下删除 currentPos 之后的节点
    if (currentPos->next == nullptr) // 如果 currentPos 是最后一个节点
    {
        std::cerr << "zhegeshizuihouyige,bucaozuo" << std::endl;
        return;
    }

    // 删除 currentPos 后面的节点
    Node* nodeToDelete = currentPos->next;
    currentPos->next = nodeToDelete->next;
    delete nodeToDelete;
    --size;
    return;
}


template<typename T>
bool SingleLinkedList<T>::find(const T &_val)
{
    Node* p = head;  // 从头开始遍历链表
    while (p != nullptr)
    {
        if (p->data == _val)  // 如果找到目标值
        {
            currentPos = p;  // 将 currentPos 移动到找到的节点
            return true;  // 返回 true
        }
        p = p->next;
    }
    return false;  // 没找到目标值，返回 false
}

template<typename T>
int SingleLinkedList<T>::getSize() const
{
    return size;
}

template <typename T>
SingleLinkedList<T>::SingleLinkedList(std::initializer_list<T> _l)
{
    for (auto i = _l.begin(); i != _l.end(); ++i)
    {
        Node* newNode = new Node(*i);
        if (head == nullptr)
        {
            head = newNode;
            currentPos = head;
        }
        else
        {
            currentPos->next = newNode;
            currentPos = newNode;
        }
        ++size;
    }
}

template <typename T>
void SingleLinkedList<T>::_emptyList()
{
    Node* p = head;
    while (p != nullptr)
    {
        Node* t = p;
        p = p->next; 
        delete t;
    }
}

template <typename T>
void SingleLinkedList<T>::printList() const
{
    Node* p = head;
    while (p != nullptr)
    {
        std::cout << p->data << "\t";
        p = p->next;
    }
    std::cout << std::endl;    
}

template <typename T>
SingleLinkedList<T>::~SingleLinkedList()
{
    _emptyList();
}

template<typename T>
SingleLinkedList<T>::SingleLinkedList(const SingleLinkedList<T> &_l)
{
    _copy(_l);
}

template<typename T>
void SingleLinkedList<T>::emptyList()
{
    _emptyList();
    head = nullptr;
    currentPos = nullptr;
    size = 0;
}

template<typename T>
SingleLinkedList<T>& SingleLinkedList<T>::operator=(const SingleLinkedList<T> &_l)
{
    if (this == &_l)
        return *this;
    emptyList();
    _copy(_l);
    return *this;
}

template <typename T>
void SingleLinkedList<T>::_copy(const SingleLinkedList<T> &_l)
{
    Node *p = _l.head;
    while (p != nullptr)
    {
        Node* newNode = new Node(p->data);
        if (head == nullptr)
        {
            head = newNode;
            currentPos = head;
        }
        else
        {
            currentPos->next = newNode;
            currentPos = newNode;
        }
        ++size;
        p = p->next;
    }
}