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


#ifndef SGE_D3D9_STATE_FFP_DEFAULTS_HPP_INCLUDED
#define SGE_D3D9_STATE_FFP_DEFAULTS_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/ffp/defaults_fwd.hpp>
#include <sge/d3d9/state/ffp/alpha_test/object_fwd.hpp>
#include <sge/d3d9/state/ffp/fog/object_fwd.hpp>
#include <sge/d3d9/state/ffp/lighting/object_fwd.hpp>
#include <sge/d3d9/state/ffp/lighting/material/object_fwd.hpp>
#include <sge/d3d9/state/ffp/misc/object_fwd.hpp>
#include <sge/d3d9/state/ffp/sampler/object_fwd.hpp>
#include <sge/d3d9/state/ffp/transform/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace d3d9
{
namespace state
{
namespace ffp
{

class defaults
{
	FCPPT_NONCOPYABLE(
		defaults
	);
public:
	explicit
	defaults(
		IDirect3DDevice9 &
	);

	~defaults();

	sge::d3d9::state::ffp::alpha_test::object const &
	alpha_test() const;

	sge::d3d9::state::ffp::fog::object const &
	fog() const;

	sge::d3d9::state::ffp::lighting::object const &
	lighting() const;

	sge::d3d9::state::ffp::lighting::material::object const &
	material() const;

	sge::d3d9::state::ffp::misc::object const &
	misc() const;

	sge::d3d9::state::ffp::sampler::object const &
	sampler() const;

	sge::d3d9::state::ffp::transform::object const &
	transform() const;
private:
	typedef std::unique_ptr<
		sge::d3d9::state::ffp::alpha_test::object
	> alpha_test_unique_ptr;

	typedef std::unique_ptr<
		sge::d3d9::state::ffp::fog::object
	> fog_unique_ptr;

	typedef std::unique_ptr<
		sge::d3d9::state::ffp::lighting::object
	> lighting_unique_ptr;

	typedef std::unique_ptr<
		sge::d3d9::state::ffp::lighting::material::object
	> material_unique_ptr;

	typedef std::unique_ptr<
		sge::d3d9::state::ffp::misc::object
	> misc_unique_ptr;

	typedef std::unique_ptr<
		sge::d3d9::state::ffp::sampler::object
	> sampler_unique_ptr;

	typedef std::unique_ptr<
		sge::d3d9::state::ffp::transform::object
	> transform_unique_ptr;

	alpha_test_unique_ptr const alpha_test_;

	fog_unique_ptr const fog_;

	lighting_unique_ptr const lighting_;

	material_unique_ptr const material_;

	misc_unique_ptr const misc_;

	sampler_unique_ptr const sampler_;

	transform_unique_ptr const transform_;
};

}
}
}
}

#endif
