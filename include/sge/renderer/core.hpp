/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_CORE_HPP_INCLUDED
#define SGE_RENDERER_CORE_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/renderer/core_fwd.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/renderer/system_unique_ptr.hpp>
#include <sge/renderer/caps/system_field_fwd.hpp>
#include <awl/system/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{

class SGE_CLASS_SYMBOL core
{
	FCPPT_NONCOPYABLE(
		core
	);
protected:
	SGE_RENDERER_SYMBOL
	core();
public:
	SGE_RENDERER_SYMBOL
	virtual
	~core() = 0;

	virtual
	sge::renderer::system_unique_ptr
	create_system(
		awl::system::object &
	) = 0;

	/**
	\brief Returns the system's capabilities
	*/
	virtual
	sge::renderer::caps::system_field const
	caps() const = 0;
};

}
}

#endif
