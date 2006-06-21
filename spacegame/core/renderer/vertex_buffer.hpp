#ifndef SGE_VERTEX_BUFFER_HPP_INCLUDED
#define SGE_VERTEX_BUFFER_HPP_INCLUDED

#include <iterator>
#include <cstddef>
#include <boost/iterator/iterator_facade.hpp>
#include "../main/shared_ptr.hpp"
#include "../main/types.hpp"
#include "../main/algorithm.hpp"
#include "../math/vector2.hpp"
#include "../math/vector3.hpp"
#include "../math/vector4.hpp"
#include "./vertex_format.hpp"
#include "./renderer_types.hpp"

namespace sge
{
class vertex_buffer {
	friend class iterator;
	friend class const_iterator;
public:
	typedef vertex_pointer::value_type      value_type;
	typedef vertex_pointer::size_type       size_type;
	typedef vertex_pointer::difference_type difference_type;
	typedef vertex_pointer::pointer         pointer;
	typedef const_vertex_pointer::pointer   const_pointer;
private:
	template<typename Stored>
	class iterator_impl : public boost::iterator_facade<iterator_impl<Stored>,Stored,std::random_access_iterator_tag,Stored,difference_type> {
		friend class vertex_buffer;
		
		typename Stored::pointer data;
		size_type stride;
		const offset_info& oi;

		friend class boost::iterator_core_access;
		void advance(difference_type d) { data += stride * d; }
		void increment() { data += stride; }
		void decrement() { data -= stride; }
		bool equal(const iterator_impl& r) const { return data == r.data; }
		Stored dereference() const { return Stored(data,stride,oi); }
		template<typename OtherStored> friend class iterator_impl;
	public:
		template<typename OtherStored>
		iterator_impl(const iterator_impl<OtherStored&> r)
		: data(r.data), stride(r.stride), oi(r.oi) {}

		iterator_impl(typename Stored::pointer data, const size_type stride, const offset_info& oi)
			: data(data), stride(stride), oi(oi) {}
	};

public:
	typedef iterator_impl<vertex_pointer> iterator;
	typedef iterator_impl<const_vertex_pointer> const_iterator;

	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	virtual iterator begin() = 0;
	virtual const_iterator begin() const = 0;
	virtual iterator end() = 0;
	virtual const_iterator end() const = 0;
	virtual reverse_iterator rbegin() = 0;
	virtual const_reverse_iterator rbegin() const = 0;
	virtual reverse_iterator rend() = 0;
	virtual const_reverse_iterator rend() const = 0;
	virtual size_type size() const = 0;
	virtual resource_flag_t flags() const = 0;
	virtual void lock(lock_flag_t flags = LF_Default) = 0;
	virtual void unlock() = 0;
	virtual void set_data(const_pointer data, size_type first, size_type count) = 0;
	virtual void resize(size_type newsize, const_pointer data = 0) = 0;
	virtual size_type stride() const = 0;
	virtual iterator create_iterator(pointer data) = 0;
	virtual const_iterator create_iterator(const_pointer data) const = 0;
	virtual pointer data() = 0;
	virtual const_pointer data() const = 0;
	virtual const vertex_format& get_vertex_format() const = 0;
	virtual ~vertex_buffer(){}
};

typedef shared_ptr<vertex_buffer> vertex_buffer_ptr;

}

#endif
