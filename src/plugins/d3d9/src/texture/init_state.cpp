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


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/texture/address_mode.hpp>
#include <sge/d3d9/texture/init_state.hpp>
#include <sge/d3d9/texture/filter/set.hpp>
#include <sge/renderer/caps/texture_stages.hpp>
#include <sge/renderer/texture/address_mode_default.hpp>
#include <sge/renderer/texture/address_mode_s.hpp>
#include <sge/renderer/texture/address_mode_t.hpp>
#include <sge/renderer/texture/address_mode_u.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <sge/renderer/texture/stage_value.hpp>
#include <sge/renderer/texture/filter/default.hpp>
#include <sge/renderer/texture/filter/object.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/mpl/for_each.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>

namespace
{

typedef boost::mpl::vector3<
	sge::renderer::texture::address_mode_s,
	sge::renderer::texture::address_mode_t,
	sge::renderer::texture::address_mode_u
> address_modes;

class address_mode_visitor
{
	FCPPT_NONASSIGNABLE(
		address_mode_visitor
	);
public:
	address_mode_visitor(
		IDirect3DDevice9 *,
		sge::renderer::texture::stage
	);

	typedef void result_type;

	template<
		typename Type
	>
	result_type
	operator()() const;
private:
	IDirect3DDevice9 *const device_;

	sge::renderer::texture::stage const stage_;
};

}

void
sge::d3d9::texture::init_state(
	IDirect3DDevice9 *const _device,
	sge::renderer::caps::texture_stages const _max_stages
)
{
	for(
		sge::renderer::texture::stage_value index(
			0u
		);
		index != _max_stages.get();
		++index
	)
	{
		sge::renderer::texture::stage const stage(
			index
		);

		sge::d3d9::texture::filter::set(
			_device,
			stage,
			sge::renderer::texture::filter::default_()
		);

		fcppt::mpl::for_each<
			address_modes
		>(
			address_mode_visitor(
				_device,
				stage
			)
		);
	}
}

namespace
{

address_mode_visitor::address_mode_visitor(
	IDirect3DDevice9 *const _device,
	sge::renderer::texture::stage const _stage
)
:
	device_(
		_device
	),
	stage_(
		_stage
	)
{
}

template<
	typename Type
>
address_mode_visitor::result_type
address_mode_visitor::operator()() const
{
	sge::d3d9::texture::address_mode(
		device_,
		stage_,
		Type(
			sge::renderer::texture::address_mode_default()
		)
	);
}

}
