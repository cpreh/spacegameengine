/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/core_fwd.hpp>
#include <sge/renderer/system_unique_ptr.hpp>
#include <sge/renderer/caps/system_field_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/window/system_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{

/**
\brief The staring class of a renderer plugin

\ingroup sge_renderer

Creates renderer systems from window systems and provides the plugin's
capabilities.
*/
class SGE_CORE_DETAIL_CLASS_SYMBOL core
{
	FCPPT_NONCOPYABLE(
		core
	);
protected:
	SGE_RENDERER_DETAIL_SYMBOL
	core();
public:
	SGE_RENDERER_DETAIL_SYMBOL
	virtual
	~core();

	virtual
	sge::renderer::system_unique_ptr
	create_system(
		sge::window::system &
	) = 0;

	virtual
	sge::renderer::caps::system_field
	caps() const = 0;
};

}
}

#endif
