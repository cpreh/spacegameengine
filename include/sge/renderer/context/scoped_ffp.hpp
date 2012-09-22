/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_CONTEXT_SCOPED_FFP_HPP_INCLUDED
#define SGE_RENDERER_CONTEXT_SCOPED_FFP_HPP_INCLUDED

#include <sge/renderer/symbol.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/context/ffp_scoped_ptr.hpp>
#include <sge/renderer/context/scoped_ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/target/base_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace context
{

class scoped_ffp
{
	FCPPT_NONCOPYABLE(
		scoped_ffp
	);
public:
	SGE_RENDERER_SYMBOL
	scoped_ffp(
		sge::renderer::device::ffp &,
		sge::renderer::target::base &
	);

	SGE_RENDERER_SYMBOL
	~scoped_ffp();

	SGE_RENDERER_SYMBOL
	sge::renderer::context::ffp &
	get() const;
private:
	sge::renderer::device::ffp &device_;

	sge::renderer::context::ffp_scoped_ptr const context_;
};

}
}
}

#endif
