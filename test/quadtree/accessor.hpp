#ifndef ACCESSOR_HPP_INCLUDED
#define ACCESSOR_HPP_INCLUDED

template<typename T>
class accessor
{
	T a_;
	public:
		accessor() {}
		accessor(const T &_a) : a_(_a) {}
		void operator()(const T &_a) { a_ = _a; }
		T operator()() const { return a_; }
};


#endif
