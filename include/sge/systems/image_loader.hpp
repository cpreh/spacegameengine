/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SYSTEMS_IMAGE_LOADER_HPP_INCLUDED
#define SGE_SYSTEMS_IMAGE_LOADER_HPP_INCLUDED

#include <sge/image/capabilities_field.hpp>
#include <sge/extension_set.hpp>
#include <sge/symbol.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>

namespace sge
{
namespace systems
{

class image_loader
{
public:
	SGE_SYMBOL explicit image_loader(
		sge::image::capabilities_field const &,
		sge::extension_set const &
	);
	
	SGE_SYMBOL sge::image::capabilities_field const &
	capabilities() const;

	SGE_SYMBOL sge::extension_set const &
	extensions() const;
private:
	sge::image::capabilities_field const capabilities_;

	sge::extension_set const extensions_;
};

}
}

#endif
