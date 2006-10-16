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


#include "../handler.hpp"
#include "../system.hpp"
#include <boost/filesystem/convenience.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

sge::image_loader_handler::image_loader_handler(const std::string& path, const image_loader_ptr il)
 : path(path), il(il)
{}

bool sge::image_loader_handler::operator()(sprite_system& ss, const std::string& name) const
{
	const boost::filesystem::directory_iterator end;
	for(boost::filesystem::directory_iterator it(path); it != end; ++it)
		if(boost::filesystem::basename(*it) == name)
		{
			ss.add_texture(il->load_image(it->string()),name);
			return true;
		}                                                         
	return false;                                                 
}
