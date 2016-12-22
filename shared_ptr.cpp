template<class T>
class shared_ptr
{
    T* ptr_;
    size_t* count_; 
public:
    shared_ptr();
    shared_ptr(T* p);
    shared_ptr(const shared_ptr &p);
    ~shared_ptr();
    shared_ptr& operator=(shared_ptr &p);
};

template<class T>
shared_ptr<T>::shared_ptr(): ptr_(nullptr), count_(nullptr) 
{}

template<class T>
shared_ptr<T>::shared_ptr(T* p): ptr_(p), count_(new size_t(1))
{}

template<class T>
shared_ptr<T>::shared_ptr(const shared_ptr<T> &p): ptr_(p.ptr_), count_(p.count_)
{
    if (ptr_!=nullptr)
        ++(*count_);
};
 
shared_ptr::~shared_ptr()
{
    if(count_==1)//<------------------ ??
    {
        delete ptr_;
        delete count_;
    }
    else 
        ptr_ = nullptr;
        (*count_)--;
};
 
shared_ptr& shared_ptr::operator=(shared_ptr &p)
{
    std::swap(ptr, p.ptr);
	std::swap(count, p.count);
}
