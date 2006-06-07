#ifndef SGE_INDEX_BUFFER_HPP_INCLUDED
#define SGE_INDEX_BUFFER_HPP_INCLUDED

#include <cstddef>
#include <iterator>
#include "../main/shared_ptr.hpp"
#include "../main/types.hpp"
#include "./renderer_types.hpp"

namespace sge
{
	class index_buffer {
	public:
		typedef std::size_t      size_type;
		typedef std::ptrdiff_t   difference_type;
		typedef uint16           value_type;

		typedef value_type&        reference;
		typedef const value_type&  const_reference;
		typedef value_type*        pointer;
		typedef const value_type*  const_pointer;
		typedef pointer            iterator;
		typedef const_pointer      const_iterator;
		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
		static const size_type stride = sizeof(value_type);

		virtual void lock(lock_flag_t flags = LF_Default) = 0;
		virtual void unlock() = 0;
		virtual void set_data(const_pointer data, size_type first, size_type count) = 0;
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
		virtual void resize(size_type newsize, const_pointer data = 0) = 0;
		virtual pointer data() = 0;
		virtual const_pointer data() const = 0;
		virtual ~index_buffer(){}
	};

	typedef shared_ptr<index_buffer> index_buffer_ptr;
}

#endif
