/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_INDEX_BUFFER_HPP_INCLUDED
#define SGE_INDEX_BUFFER_HPP_INCLUDED

#include <cstddef>
#include <iterator>
#include "../shared_ptr.hpp"
#include "../typeswitch.hpp"
#include "../export.hpp"
#include "types.hpp"

namespace sge
{

class index_buffer {
public:
	typedef std::size_t                           size_type;
	typedef std::ptrdiff_t                        difference_type;
	typedef uint32                                value_type;

	typedef value_type&                           reference;
	typedef const value_type&                     const_reference;
	typedef value_type*                           pointer;
	typedef const value_type*                     const_pointer;
	typedef pointer                               iterator;
	typedef const_pointer                         const_iterator;
	typedef std::reverse_iterator<iterator>       reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
	
	SGE_SYMBOL iterator end();
	SGE_SYMBOL const_iterator end() const;
	SGE_SYMBOL reverse_iterator rbegin();
	SGE_SYMBOL const_reverse_iterator rbegin() const;
	SGE_SYMBOL reverse_iterator rend();
	SGE_SYMBOL const_reverse_iterator rend() const;
	SGE_SYMBOL reference operator[](size_type);
	SGE_SYMBOL const_reference operator[](size_type) const;

	virtual void lock(lock_flag_t flags = lock_flags::default_) = 0;
	virtual void unlock() = 0;
	virtual void set_data(const_pointer data, size_type first, size_type count) = 0;
	virtual iterator begin() = 0;
	virtual const_iterator begin() const = 0;
	virtual size_type size() const = 0;
	virtual resource_flag_t flags() const = 0;

	virtual void resize(size_type newsize, const_pointer data = 0) = 0;
	virtual pointer data() = 0;
	virtual const_pointer data() const = 0;
	SGE_SYMBOL virtual ~index_buffer();
};

typedef shared_ptr<index_buffer> index_buffer_ptr;

}

#endif
