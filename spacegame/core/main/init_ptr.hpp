#ifndef SGE_INIT_PTR_HPP_INCLUDED
#define SGE_INIT_PTR_HPP_INCLUDED

namespace sge
{
	template<typename T> class init_ptr {
	public:
		init_ptr(T* t = 0) : t(0) {}
		init_ptr& operator=(const init_ptr& p) { t = p.t; return *this; }
		init_ptr& operator=(T* _t) { t = _t; return *this; }
		operator T*() const { return t; }
	private:
		T* t;
	};
}

#endif
