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


#ifndef SGE_RENDERER_VERTEX_BUFFER_HPP_INCLUDED
#define SGE_RENDERER_VERTEX_BUFFER_HPP_INCLUDED

#include <sge/renderer/vf/dynamic_view.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/export.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace renderer
{

namespace vf
{
class dynamic_format;
}

class SGE_CLASS_SYMBOL vertex_buffer {
	FCPPT_NONCOPYABLE(vertex_buffer)
protected:
	SGE_SYMBOL vertex_buffer();
public:
	typedef renderer::size_type     size_type;
	typedef vf::dynamic_view        view_type;
	typedef vf::const_dynamic_view  const_view_type;

	SGE_SYMBOL static size_type const npos;

	virtual view_type const lock(
		lock_mode::type,
		size_type offset = 0,
		size_type range = npos
	) = 0;

	virtual const_view_type const lock(
		size_type offset = 0,
		size_type range = npos
	) const = 0;

	virtual void
	unlock() const = 0;

	virtual size_type
	size() const = 0;

	virtual resource_flags_field const
	flags() const = 0;

	virtual vf::dynamic_format const &
	format() const = 0;

	SGE_SYMBOL virtual ~vertex_buffer();
};

}
}

#endif
