template<T>
class shared_ptr
{
    T* pObj;
    static int count; //счетчик указателей на pObj
public:
    shared_ptr(T* myObj);
    shared_ptr(const shared_ptr &myObj);
    ~shared_ptr();
    shared_ptr& operator=(shared_ptr &myObj);
};

int shared_ptr::count=0;
 
shared_ptr::shared_ptr(T* myObj)
{
    pObj=myObj; 
};
shared_ptr::shared_ptr(const shared_ptr &myObj)
{
    shared_ptr p1 = new T();
    p1.pObj = myObj.pObj;
    count++;
};
 
shared_ptr::~shared_ptr()
{
    if(count==1)//если имеется только один указатель на объект, то чистим память
    {
        delete pObj;
        count = 0;
        printf("Another crash\n");
    }
    else 
        pObj = NULL;
        count--;
};
 
shared_ptr& shared_ptr::operator=(shared_ptr &myObj)
{
    count++;
    return myObj;
}
