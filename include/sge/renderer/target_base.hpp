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


#ifndef SGE_RENDERER_TARGET_BASE_HPP_INCLUDED
#define SGE_RENDERER_TARGET_BASE_HPP_INCLUDED

#include <sge/renderer/target_base_fwd.hpp>
#include <sge/renderer/viewport.hpp>
#include <sge/class_symbol.hpp>
#include <sge/symbol.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace renderer
{

class SGE_CLASS_SYMBOL target_base
{
	FCPPT_NONCOPYABLE(
		target_base
	);
protected:
	SGE_SYMBOL
	target_base();
public:
	virtual void
	viewport(
		renderer::viewport const &
	) = 0;

        virtual
	renderer::viewport const
	viewport() const = 0;

	SGE_SYMBOL
	virtual ~target_base();
};

}
}

#endif
