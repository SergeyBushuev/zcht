template <typename T>
class Node
{
    friend class Tree<T>;
public:
    Node(const T &);
    T get_data();
protected:
    Node* left; /* указатель на левого ребенка */
    Node* right; /* указатель на правого ребенка */
    Node* parent; /* указатель на родителя */
    T data;/* ключ */
};

template <typename T>
Node <T>::Node(const T &a)
{
    data=a;
    left=right=0;
}
template <typename T>
T Node <T>::get_data()
{
    return data;
};


template <typename T>
class Tree
{
public:
    Tree();                                                 /* конструктор */
    int insert_node(const T &);                             /* вставляет узел */
    Node<T>* delete_node(TreeNode<T> *);                    /* удаляет узел */
    Node<T>* find_node(TreeNode<T>*,const T &);
    Node<T> *get_root();                                    /* возвращает указатель на корень дерева */
private:
    Node<T> *root;                                          /* собственно, сам корень */
};

template<class T>
int Tree<T>::insert_node(const T &x)
{
    Node<T>* n=new Node<T>(x);  /* создаем новый узел, его мы будем вставлять */
    Node<T>* ptr;
    Node<T>* ptr1;
    
    n->parent=n->left=n->right=0;                   /* он - лист */
    ptr=root;
    while(ptr!=0)                                   /* идем от корня и ищем подходящее место для нашего нового элемента, оно должно быть свободно */
    {
        ptr1=ptr;                                   /* будущий родитель нового узла */
        if(x < ptr->get_data() )                    /* по определению нашего дерева - слева значение ключа меньше родителя, */
            ptr=ptr->left;
        else
            ptr=ptr->right;                         /* справа - больше */
    }
    n->parent=ptr1;
    if(ptr1==0)                                     /* дерево было пусто? */
        root=n;
    else
    {
        if(x < ptr1->get_data() )
            ptr1->left=n;
        else
            ptr1->right=n;
    }
    return 0;
}
