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


#include <vector>
#include "../../../exception.hpp"
#include "../../../vector.hpp"
#include "../archive_entry.hpp"
#include "../zip_file.hpp"

sge::zlib::archive_entry::archive_entry(zip_file& file)
: file(file),
  open_handle(file)
{
	if(unzGetCurrentFileInfo(file.handle(), &info, 0, 0, 0, 0, 0, 0) != UNZ_OK)
		throw exception(SGE_TEXT("unzGetCurrentFileInfo() failed!"));

	std::vector<char> name_buffer(info.size_filename);

	if(unzGetCurrentFileInfo(file.handle(), 0, data(name_buffer), name_buffer.size(), 0, 0, 0, 0) != UNZ_OK)
		throw exception(SGE_TEXT("unzGetCurrentFileInfo() failed!"));
	name_.assign(name_buffer.begin(), name_buffer.end());
}

const std::string& sge::zlib::archive_entry::name() const
{
	return name_;
}

sge::zlib::archive_entry::size_type sge::zlib::archive_entry::uncompressed_size() const
{
	return info.uncompressed_size;
}

void sge::zlib::archive_entry::uncompress(const pointer dest)
{
	const int ret = unzReadCurrentFile(file.handle(), dest, static_cast<unsigned>(uncompressed_size()));
	if(ret >= 0)
		return;
/*	if(ret == 0)
		return;
	if(ret > 0)
		throw exception("archive_entry::uncompress(): The end of file has not been reached (logic error)!");*/
	throw exception(SGE_TEXT("unzReadCurrentFile() failed!"));
}
