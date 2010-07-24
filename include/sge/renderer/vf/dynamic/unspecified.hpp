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


#ifndef SGE_RENDERER_VF_DYNAMIC_UNSPECIFIED_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_UNSPECIFIED_HPP_INCLUDED

#include <sge/renderer/vf/dynamic/unspecified_fwd.hpp>
#include <sge/renderer/vf/dynamic/unspecified_any.hpp>
#include <sge/renderer/vf/string.hpp>
#include <sge/symbol.hpp>
#include <fcppt/variant/object_impl.hpp>

namespace sge
{
namespace renderer
{
namespace vf
{
namespace dynamic
{

class unspecified
{
public:
	SGE_SYMBOL
	explicit unspecified(
		unspecified_any const &,
		vf::string const &
	);

	SGE_SYMBOL
	unspecified_any const &
	type() const;

	SGE_SYMBOL
	vf::string const &
	tag() const;
private:
	unspecified_any type_;

	vf::string tag_;
};

}
}
}
}

#endif
