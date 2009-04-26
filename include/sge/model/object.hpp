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



#ifndef SGE_MODEL_OBJECT_HPP_INCLUDED
#define SGE_MODEL_OBJECT_HPP_INCLUDED

#include <sge/renderer/index/view.hpp>
#include <sge/renderer/vf/dynamic_view_fwd.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/noncopyable.hpp>
#include <sge/export.hpp>

namespace sge
{
namespace renderer
{
namespace vf
{
class dynamic_format;
}
}
namespace model
{

class SGE_CLASS_SYMBOL object {
	SGE_NONCOPYABLE(object)
protected:
	SGE_SYMBOL object();
public:
	// very basic interface
	// will need a lot more abstraction
	
	virtual renderer::vf::dynamic_format const
	format() const = 0;

	virtual renderer::size_type
	vertices() const = 0;

	virtual renderer::size_type
	indices() const = 0;

	virtual void
	copy_vertices(
		renderer::vf::dynamic_view const &) = 0;
	
	virtual void
	copy_indices(
		renderer::index::view const &) = 0;
	
	SGE_SYMBOL virtual ~object();
};

}
}

#endif
