class scoped_ptr {
 
private:
  Object* myPointer;
 
public:
 
  scoped_ptr(Object* ptr);
  ~scoped_ptr();
 
public:
 
  Object* ptr();
  Object& operator *() const;
  Object* operator->() const;
  bool isNull() const;
 
private:
  scoped_ptr(const scoped_ptr& p);
  const scoped_ptr& operator=(const scoped_ptr& p);  
}
scoped_ptr::scoped_ptr(Object* ptr) {
   myPointer = ptr;
}
 
scoped_ptr::~scoped_ptr() {
  if (myPointer != 0) {
    delete myPointer;
  }
}
 
Object& scoped_ptr::operator *() const {
  return *myPointer;
}
 
Object& scoped_ptr::operator ->() const {
  return myPointer;
}
 
bool scoped_ptr::isNull() const {
  return myPointer == 0;
}
