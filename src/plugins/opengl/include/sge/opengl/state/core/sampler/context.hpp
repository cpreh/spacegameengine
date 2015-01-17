/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/state/core/sampler/object_fwd.hpp>
#include <sge/renderer/state/core/sampler/const_optional_object_ref_map.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <memory>
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
	typedef sge::opengl::context::system::object &parameter;

	explicit
	context(
		parameter
	);

	~context()
	override;

	void
	set(
		sge::renderer::state::core::sampler::const_optional_object_ref_map const &
	);

	sge::opengl::state::core::sampler::object const &
	get(
		sge::renderer::texture::stage
	) const;

	void
	reset();

	static
	sge::opengl::context::device::id const
	static_id;
private:
	typedef
	std::unique_ptr<
		sge::opengl::state::core::sampler::object
	>
	object_unique_ptr;

	typedef fcppt::optional<
		sge::opengl::state::core::sampler::object const &
	> optional_object_ref;

	typedef std::map<
		sge::renderer::texture::stage,
		optional_object_ref
	> optional_object_ref_map;

	object_unique_ptr const defaults_;

	optional_object_ref_map objects_;
};

}
}
}
}
}

#endif
