#ifndef SGE_FIELD_HPP_INCLUDED
#define SGE_FIELD_HPP_INCLUDED

#include <cassert>
#include <algorithm>
#include <vector>
#include <iterator>
#include <memory>
#include <boost/iterator/iterator_adaptor.hpp>
#include "math/vector.hpp"
#include "math/dim.hpp"
#include "exception.hpp"
#include "format.hpp"

namespace sge
{

template<typename T,template<typename,typename>class ArrayType = std::vector,typename Alloc = std::allocator<T> >
class field
{
	public:
	typedef ArrayType<T,Alloc>                    array_type;

	// container requirements
	typedef T                                     value_type;
	typedef Alloc                                 allocator_type;
	typedef T&                                    reference;
	typedef const T&                              const_reference;
	typedef typename array_type::iterator         iterator;
	typedef typename array_type::const_iterator   const_iterator;
	typedef typename array_type::size_type        size_type;
	typedef typename array_type::difference_type  difference_type;
	typedef std::reverse_iterator<iterator>       reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	typedef math::basic_vector<size_type,2>      vector_type;
	typedef math::basic_dim<size_type,2>         dim_type;

	private:
	dim_type   dim_;
	array_type array;

	public:

	// standard-ctor
	field(const allocator_type& alloc = allocator_type()) : array(alloc) {}
	// copy-ctor
	field(const field &r) : dim_(r.dim_),array(r.array) {}
	field(const dim_type &dim, const value_type& t = value_type(), const allocator_type& alloc = allocator_type()) : dim_(dim), array(field_count(), t, alloc) {}
	// same as above just without the dim type
	field(const size_type &x,const size_type &y, const allocator_type& alloc = allocator_type()) : dim_(x,y),array(alloc) { array.resize(field_count()); }

	template<typename Iterator>
	field(const size_type &x,const size_type &y,Iterator b,Iterator e,const allocator_type &alloc = allocator_type()) 
		: dim_(x,y),array(alloc) 
	{ 
		array.resize(field_count());
		std::copy(b,e,begin()); 
	}

	template<typename Iterator>
	field(const dim_type &dim_,Iterator b,Iterator e,const allocator_type &alloc = allocator_type()) 
		: dim_(dim_),array(alloc) 
	{ 
		array.resize(field_count());
		std::copy(b,e,begin()); 
	}

	// again, container requirements
	bool operator==(const field &r) const { return dim_ == r.dim_ && std::equal(begin(),end(),r.begin()); }
	bool operator!=(const field &r) const { return !(*this == *r); }
	void swap(field &r) { std::swap(dim_,r.dim_); array.swap(r.array); }
	field &operator=(const field &r) { if(&r != this) { dim_ = r.dim_; array = r.array; } return *this; }
	size_type size() const { return array.size();  }
	size_type max_size() const { return array.max_size(); }
	bool empty() const { return array.empty(); }
	iterator begin() { return array.begin(); }
	iterator end() { return array.end(); }
	const_iterator begin() const { return array.begin(); }
	const_iterator end() const { return array.end(); }
	reverse_iterator rbegin() { return array.rbegin(); }
	reverse_iterator rend() { return array.rend(); }
	const_reverse_iterator rbegin() const { return array.rbegin(); }
	const_reverse_iterator rend() const { return array.rend(); }
	const vector_type position(const const_iterator it) const
	{
		const difference_type diff = std::distance(begin(), it);
		return vector_type(diff % w(), diff / w());
	}
	iterator position_it(const size_type &x,const size_type &y) { return begin() + y * w() + x; }
	const_iterator position_it(const size_type &x,const size_type &y) const { return begin() + y * w() + x; }

	allocator_type get_allocator() const { return array.get_allocator(); }

	void zero() { std::fill(begin(),end(),static_cast<value_type>(0)); }
	void resize(const size_type &x,const size_type &y, const_reference value = value_type()) { resize(dim_type(x,y), value); }
	void resize(const dim_type &n, const_reference value = value_type()) { if (dim_ == n) return; dim_ = n; array.resize(field_count(), value); }

	value_type &pos_mod(size_type x,size_type y) { x = x % w(); y = y % h(); return array[y * dim_.w() + x]; }
	const value_type &pos_mod(size_type x,size_type y) const { x = x % w(); y = y % h(); return array[y * dim_.w() + x]; }
	value_type &pos_mod(vector_type p) { p.x() = p.x() % w(); p.y() = p.y() % h(); return pos(p.x(),p.y()); }
	const value_type &pos_mod(vector_type p) const { p.x() = p.x() % w(); p.y() = p.y() % h(); return pos(p.x(),p.y()); }
#ifndef SGE_FIELD_RANGE_CHECK
	value_type &pos(const size_type &x,const size_type &y) { return array[y * dim_.w() + x]; }
	const value_type &pos(const size_type &x,const size_type &y) const { return array[y * dim_.w() + x]; }
	value_type &pos(const vector_type &p) { return pos(p.x(),p.y()); }
	const value_type &pos(const vector_type &p) const { return pos(p.x(),p.y()); }
#else
	void range_check(const size_type &x,const size_type &y) const
	{ 
		if (x >= dim_.w() || y >= dim_.h()) 
			throw sge::exception((format(SGE_TEXT("tried to access position %ix%i")) % x % y).str());
	}
	value_type &pos(const size_type &x,const size_type &y) { range_check(x,y); return array[y * dim_.w() + x]; }
	const value_type &pos(const size_type &x,const size_type &y) const { range_check(x,y); return array[y * dim_.w() + x]; }
	value_type &pos(const vector_type &p) { range_check(p.x(),p.y()); return pos(p.x(),p.y()); }
	const value_type &pos(const vector_type &p) const { range_check(p.x(),p.y()); return pos(p.x(),p.y()); }
#endif

	reference front() { return array.front(); }
	const_reference front() const { return array.front(); }
	reference back() { return array.back(); }
	const_reference back() const { return array.back(); }

	value_type x(const const_iterator &p) const { if (w() == 0) throw std::range_error("width is zero, cannot execute x()"); return std::distance(begin(),p) % w(); }
	value_type y(const const_iterator &p) const { if (w() == 0) throw std::range_error("width is zero, cannot execute y()"); return std::distance(begin(),p) / w(); }
	vector_type pos(const const_iterator &p) const { if (w() == 0) throw std::range_error("width is zero, cannot execute pos()"); return vector_type(x(p),y(p)); }

	size_type w() const { return dim_.w(); }
	size_type h() const { return dim_.h(); }
	size_type field_count() const { return dim_.w()*dim_.h(); }
	dim_type dim() const { return dim_; }

	//array_type container() { return array; }
	//array_type container() const { return array; }
};
typedef field<space_unit> space_field;
}

template<typename T,typename Ch,typename Traits>
std::basic_ostream<Ch,Traits> &operator<<(std::basic_ostream<Ch,Traits> &stream,const sge::field<T> &field)
{
	for (sge::space_field::size_type y = 0; y < field.h(); ++y)
	{
		for (sge::space_field::size_type x = 0; x < field.w(); ++x)
			stream << field.pos(x,y) << stream.widen(' ');
		stream << stream.widen('\n');
	}
	return stream;
}

#endif
