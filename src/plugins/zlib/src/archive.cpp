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


#include "../../../exception.hpp"
#include "../archive.hpp"
#include "../archive_entry.hpp"

sge::zlib::archive::archive(const path& file)
: file(file)
{}

void sge::zlib::archive::goto_begin()
{
	if(unzGoToFirstFile(file.handle()) != UNZ_OK)
		throw exception(SGE_TEXT("unzGoToFirstFile() failed!"));
}

bool sge::zlib::archive::next()
{
	const int ret = unzGoToNextFile(file.handle());
	switch(ret) {
	case UNZ_OK:
		return true;
	case UNZ_END_OF_LIST_OF_FILE:
		return false;
	default:
		throw exception(SGE_TEXT("unzGoToNextFile() failed!"));
	}
}

bool sge::zlib::archive::goto_entry(const std::string& name)
{
	const int ret = unzLocateFile(file.handle(), name.c_str(), 0);
	switch(ret) {
	case UNZ_OK:
		return true;
	case UNZ_END_OF_LIST_OF_FILE:
		return false;
	default:
		throw exception(SGE_TEXT("unzLocalteFile() failed!"));
	}
}

void sge::zlib::archive::open(archive_entry_ptr& ptr)
{
	if(ptr.use_count() > 1)
		throw exception(SGE_TEXT("The shared_ptr passed to archive::open() has to have its usecount set to <= 1!"));
	ptr.reset(new archive_entry(file));
}
