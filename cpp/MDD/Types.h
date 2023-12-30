#include <optional>

#include <proxyInclude/eigen>

using RealType = double;
using ArrayType = Eigen::ArrayXd;

//! optional reference to an object
template<class T>
struct OptRef: public std::optional<std::reference_wrapper<T>>{
	OptRef():std::optional<std::reference_wrapper<T>>(){}
	OptRef(T& v):std::optional<std::reference_wrapper<T>>(v){}
	T* operator ->(){return &this->value().get();}
	const T* operator ->()const{return &this->value().get();}
};

//! reference to an object, can be used in containers
template<class T>
struct Ref: OptRef<T>{
	Ref()=delete;
	Ref(T& v):OptRef<T>(v){}
};
