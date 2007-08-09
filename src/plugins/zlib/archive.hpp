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


#ifndef SGE_ZLIB_ARCHIVE_HPP_INCLUDED
#define SGE_ZLIB_ARCHIVE_HPP_INCLUDED

#include "../../archive/archive.hpp"
#include "zip_file.hpp"

namespace sge
{
namespace zlib
{

class archive : public sge::archive {
public:
	archive(const std::string& path);
	void goto_begin();
	bool next();
	bool goto_entry(const std::string&);
	void open(archive_entry_ptr&);
private:
	zip_file file;
};

}
}

#endif
