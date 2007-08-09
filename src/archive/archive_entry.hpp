/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_ARCHIVE_ENTRY_HPP_INCLUDED
#define SGE_ARCHIVE_ENTRY_HPP_INCLUDED

#include <cstddef>
#include <string>
#include "../shared_ptr.hpp"

namespace sge
{

class archive_entry {
public:
	typedef unsigned char value_type;
	typedef value_type*   pointer;
	typedef std::size_t   size_type;

	virtual const std::string& name() const = 0;
	virtual size_type uncompressed_size() const = 0;
	virtual void uncompress(pointer data) = 0;
	virtual ~archive_entry() {}
};

typedef shared_ptr<archive_entry> archive_entry_ptr;

}

#endif
