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


#ifndef SGE_RENDERER_CONTEXT_FFP_HPP_INCLUDED
#define SGE_RENDERER_CONTEXT_FFP_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/renderer/context/core.hpp>
#include <sge/renderer/state/ffp/alpha_test/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/clip_plane/const_object_ref_vector.hpp>
#include <sge/renderer/state/ffp/lighting/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/light/const_object_ref_vector.hpp>
#include <sge/renderer/state/ffp/lighting/material/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/misc/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/sampler/const_object_ref_vector.hpp>
#include <sge/renderer/state/ffp/transform/parameters_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace context
{

class SGE_CLASS_SYMBOL ffp
:
	public sge::renderer::context::core
{
	FCPPT_NONCOPYABLE(
		ffp
	);
protected:
	SGE_RENDERER_SYMBOL
	ffp();
public:
	SGE_RENDERER_SYMBOL
	virtual
	~ffp() = 0;

	virtual
	void
	alpha_test_state(
		sge::renderer::state::ffp::alpha_test::const_optional_object_ref const &
	) = 0;

	virtual
	void
	clip_plane_state(
		sge::renderer::state::ffp::clip_plane::const_object_ref_vector const &
	) = 0;

	virtual
	void
	lighting_state(
		sge::renderer::state::ffp::lighting::const_optional_object_ref const &
	) = 0;

	virtual
	void
	lights_state(
		sge::renderer::state::ffp::lighting::light::const_object_ref_vector const &
	) = 0;

	virtual
	void
	material_state(
		sge::renderer::state::ffp::lighting::material::const_optional_object_ref const &
	) = 0;

	virtual
	void
	misc_state(
		sge::renderer::state::ffp::misc::const_optional_object_ref const &
	) = 0;

	virtual
	void
	sampler_ffp_state(
		sge::renderer::state::ffp::sampler::const_object_ref_vector const &
	) = 0;

	virtual
	void
	transform(
		sge::renderer::state::ffp::transform::parameters const &
	) = 0;
};

}
}
}

#endif
