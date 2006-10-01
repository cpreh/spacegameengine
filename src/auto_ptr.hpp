#ifndef SGE_AUTO_PTR_HPP_INCLUDED
#define SGE_AUTO_PTR_HPP_INCLUDED

#include <boost/utility.hpp>
#include "./smart_ptr_policies.hpp"

namespace sge
{

template<typename T, template <typename> class Deleter = heap_deleter> class auto_ptr : boost::noncopyable, Deleter<T> {
public:
	typedef T& reference;
	typedef T* pointer;
	explicit auto_ptr(pointer p = 0) : p(p) {}
	~auto_ptr() { _destroy(); }
	auto_ptr& operator=(pointer np) { _destroy(); p = np; return *this; }
	pointer operator->() const { return p; }
	reference operator*() const { return *p; }
	pointer get() const { return p; }
	void reset(pointer np = 0) { _destroy(); p = np; }
	bool operator!() const { return p; }
	operator bool() const { return p; }
private:
	auto_ptr(const auto_ptr&);
	void _destroy() { delete_(p); }
	pointer p;
};

template<typename T> bool operator==(const auto_ptr<T>& l, const auto_ptr<T>& r) { return l.get() == r.get(); }
template<typename T> bool operator!=(const auto_ptr<T>& l, const auto_ptr<T>& r) { return !(l==r); }

}

#endif
