/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_RENDERER_CONTEXT_SCOPED_CORE_HPP_INCLUDED
#define SGE_RENDERER_CONTEXT_SCOPED_CORE_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/context/core_unique_ptr.hpp>
#include <sge/renderer/context/scoped_core_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/target/base_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace context
{

class scoped_core
{
	FCPPT_NONCOPYABLE(
		scoped_core
	);
public:
	SGE_RENDERER_DETAIL_SYMBOL
	scoped_core(
		sge::renderer::device::core &,
		sge::renderer::target::base &
	);

	SGE_RENDERER_DETAIL_SYMBOL
	~scoped_core();

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::context::core &
	get() const;
private:
	sge::renderer::device::core &device_;

	sge::renderer::context::core_unique_ptr const context_;
};

}
}
}

#endif
