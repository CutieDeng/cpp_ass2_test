#include <unordered_set> 
#include <exception> 
#include <iostream> 

#define ENCAP_POINTER

template <typename T> 
class encap_ptr; 

template <typename T> 
class encap_ptr {
    private: 
        T *value;
    public: 
        static std::unordered_set<void*> set; 

        explicit (false) encap_ptr(T *value): value(value) {} 
        explicit (false) encap_ptr(): encap_ptr(nullptr) {} 

        inline T &operator *() const; 
        inline T *operator ->() const; 

        inline explicit (false) operator T *(); 
        inline operator T *const() const; 

        inline encap_ptr<encap_ptr<T>> operator &(); 
        inline encap_ptr<T *const> operator &() const; 

        // encap_ptr<T> &operator =(encap_ptr<T> o); 
        // encap_ptr<T> &operator =(T *o); 

        // operator bool() const; 
}; 

template <typename T> 
class encap_ptr<encap_ptr<T>> {
    private: 
        encap_ptr<T> *value; 
    public: 
        static std::unordered_set<void*> set; 

        // explicit (false) encap_ptr(T **t): value((encap_ptr<T>*)t) {} 
        explicit (false) encap_ptr(encap_ptr<T> *t) : value(t) {} 
        explicit (false) encap_ptr(): encap_ptr(nullptr) {} 

        inline encap_ptr<T> &operator *() const; 
        // encap_ptr<T> *operator ->() const; 

        inline explicit (false) operator encap_ptr<T> *(); 
        inline operator encap_ptr<T> *const() const; 

        inline encap_ptr<T *> operator &(); 
        inline encap_ptr<T *const> operator &() const; 

        inline encap_ptr<T> &operator =(encap_ptr<T> o); 
        inline encap_ptr<T> &operator =(T *o); 

}; 

template <typename T> 
inline std::unordered_set<void *> encap_ptr<T>::set; 
        
template <typename T> 
encap_ptr<encap_ptr<T>>::operator encap_ptr<T> *() {
    return value; 
} 

template <typename T> 
encap_ptr<T> &encap_ptr<encap_ptr<T>>::operator *() const {
    if (!value)
        throw std::runtime_error("Segmentaion Fault!"); 
    return *value; 
} 

template <typename T> 
T &encap_ptr<T>::operator *() const {
    return *value; 
}; 

// template <typename T> 

template <typename T> 
encap_ptr<T>::operator T *() {
    return value; 
}

// template <typename T> 
// encap_ptr<T>::operator T *&() {
//     if (!value)
//         throw std::runtime_error("Segmentation fault"); 
//     return value; 
// }
// 
// template <typename T> 
// encap_ptr<T*>::operator encap_ptr<T> &() {
//     return *value; 
// }

template <typename T> 
encap_ptr<T>::operator T *const() const {
    return value; 
}

template <typename T> 
encap_ptr<encap_ptr<T>> encap_ptr<T>::operator &() {
    return this; 
}

template <typename T> 
encap_ptr<T *const> encap_ptr<T>::operator &() const {
    return &value; 
}

template <typename T> 
T *encap_ptr<T>::operator ->() const {
    if (!value)
        throw std::runtime_error("Segmentation Fault"); 
    return value; 
}

// template <typename T> 
// encap_ptr<T>::operator bool() const {
//     return value != nullptr; 
// }
// 
// template <typename T>
// encap_ptr<T>::

// template <typename T> 
// encap_ptr<T> &encap_ptr<T>::operator=(encap_ptr<T> v) {
//     this->value = v.value; 
//     return *this;
// }

// template <typename T> 
// encap_ptr<T> &encap_ptr<T>::operator=(T *v) {
//     this->value = v; 
//     return *this;
// }