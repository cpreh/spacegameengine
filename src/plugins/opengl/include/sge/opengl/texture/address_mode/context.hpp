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


#ifndef SGE_OPENGL_TEXTURE_ADDRESS_MODE_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_ADDRESS_MODE_CONTEXT_HPP_INCLUDED

#include <sge/opengl/context/device/base.hpp>
#include <sge/opengl/context/device/id.hpp>
#include <sge/opengl/texture/address_mode/context_fwd.hpp>
#include <sge/renderer/state/core/sampler/address/parameters.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/container/index_map_decl.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{
namespace address_mode
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

	sge::renderer::state::core::sampler::address::parameters const &
	get(
		sge::renderer::texture::stage
	);

	bool
	set(
		sge::renderer::texture::stage,
		sge::renderer::state::core::sampler::address::parameters const &
	);

	typedef void needs_before;

	static sge::opengl::context::device::id const static_id;
private:
	sge::renderer::state::core::sampler::address::parameters &
	get_mutable(
		sge::renderer::texture::stage
	);

	typedef fcppt::container::index_map<
		sge::renderer::state::core::sampler::address::parameters
	> address_mode_map;

	address_mode_map modes_;
};

}
}
}
}

#endif
