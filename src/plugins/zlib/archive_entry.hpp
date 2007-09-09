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


#ifndef SGE_ZLIB_ARCHIVE_ENTRY_HPP_INCLUDED
#define SGE_ZLIB_ARCHIVE_ENTRY_HPP_INCLUDED

#include "../../archive/archive_entry.hpp"
#include "current_handle.hpp"
#include "../../../3rdparty/minizip/unzip.h"

namespace sge
{
namespace zlib
{

class zip_file;

class archive_entry : public sge::archive_entry {
public:
	archive_entry(zip_file& file);
	const std::string& name() const;
	size_type uncompressed_size() const;
	void uncompress(pointer dest);
private:
	zip_file& file;
	current_handle open_handle;
	unz_file_info info;
	std::string name_;
};

}
}

#endif
