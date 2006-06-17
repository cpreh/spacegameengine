#ifndef SGE_FUNCTIONAL_HPP_INCLUDED
#define SGE_FUNCTIONAL_HPP_INCLUDED

#include <functional>

namespace sge
{

template<typename NewArg1, typename NewArg2, typename Fun> 
	class binary_dereference_binder : public std::binary_function<NewArg1,NewArg2,typename Fun::result_type> { 
public: 
	binary_dereference_binder(const Fun& f) 
		: f(f) {} 
	typename Fun::result_type operator()(NewArg1 arg1, NewArg2 arg2) const { return f(*arg1,*arg2); } 
private: 
	Fun f; 
}; 
 
template<typename NewArg1, typename Fun> 
	class unary_dereference_binder : public std::unary_function<NewArg1,typename Fun::result_type> { 
public: 
	unary_dereference_binder(const Fun& f) 
		: f(f) {} 
	typename Fun::result_type operator()(NewArg1 arg) const { return t(*arg); } 
private: 
	Fun f; 
}; 
 
template<typename NewArg1, typename NewArg2, typename Fun> 
	binary_dereference_binder<NewArg1,NewArg2,Fun> dereference_binder(const Fun& f) 
{ 
	return binary_dereference_binder<NewArg1,NewArg2,Fun>(f); 
} 
 
template<typename NewArg1, typename Fun> 
	unary_dereference_binder<NewArg1,Fun> dereference_binder(const Fun& f) 
{ 
	 return unary_dereference_binder<NewArg1,Fun>(f); 
} 

}

#endif
