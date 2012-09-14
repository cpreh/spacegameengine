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


#ifndef SGE_OPENGL_STATE_CORE_SAMPLER_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_STATE_CORE_SAMPLER_CONTEXT_HPP_INCLUDED

#include <sge/opengl/context/device/base.hpp>
#include <sge/opengl/context/device/id.hpp>
#include <sge/opengl/state/core/sampler/object_fwd.hpp>
#include <sge/renderer/state/core/sampler/const_object_ref_vectgor.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/reference_wrapper.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace state
{
namespace core
{
namespace sampler
{

class context
:
	public sge::opengl::context::device::base
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	context();

	~context();

	void
	set(
		sge::renderer::state::core::sampler::const_object_ref_vector const &
	);

	typedef void needs_before;

	static
	sge::opengl::context::device::id const
	static_id;
private:
	typedef fcppt::scoped_ptr<
		sge::opengl::state::core::sampler::object
	> object_scoped_ptr;

	object_scoped_ptr const defaults_;

	typedef std::vector<
		fcppt::reference_wrapper<
			sge::opengl::state::core::sampler::object const
		>
	> object_ref_vector;

	object_ref_vector objects_;
};

}
}
}
}
}

#endif
