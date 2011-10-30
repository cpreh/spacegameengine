/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_INDEX_BUFFER_HPP_INCLUDED
#define SGE_RENDERER_INDEX_BUFFER_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/renderer/index_buffer_fwd.hpp>
#include <sge/renderer/index_buffer_types.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{

class SGE_CLASS_SYMBOL index_buffer
{
	FCPPT_NONCOPYABLE(
		index_buffer
	);
protected:
	SGE_RENDERER_SYMBOL
	index_buffer();
public:
	typedef renderer::index_buffer_types::first_type first_type;

	typedef renderer::index_buffer_types::count_type count_type;

	typedef renderer::index_buffer_types::view_type view_type;

	typedef renderer::index_buffer_types::const_view_type const_view_type;

	typedef renderer::size_type size_type;

	SGE_RENDERER_SYMBOL
	static size_type const npos;

	virtual view_type const
	lock(
		lock_mode::type,
		first_type =
			first_type(0),
		count_type
			= npos
	) = 0;

	virtual const_view_type const
	lock(
		first_type
			= first_type(0),
		count_type
			= npos
	) const = 0;

	virtual void
	unlock() const = 0;

	virtual count_type const
	size() const = 0;

	virtual resource_flags_field const
	resource_flags() const = 0;

	virtual index::dynamic::format::type
	format() const = 0;

	SGE_RENDERER_SYMBOL
	virtual ~index_buffer() = 0;
};

}
}

#endif
