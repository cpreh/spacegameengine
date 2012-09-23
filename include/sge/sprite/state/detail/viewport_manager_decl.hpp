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


#ifndef SGE_SPRITE_STATE_DETAIL_VIEWPORT_MANAGER_DECL_HPP_INCLUDED
#define SGE_SPRITE_STATE_DETAIL_VIEWPORT_MANAGER_DECL_HPP_INCLUDED

#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/target/viewport_fwd.hpp>
#include <sge/sprite/state/detail/object_class.hpp>
#include <sge/sprite/state/detail/viewport_manager_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/scoped_connection.hpp>


namespace sge
{
namespace sprite
{
namespace state
{
namespace detail
{

template<
	typename StateChoices
>
class viewport_manager
{
	FCPPT_NONCOPYABLE(
		viewport_manager
	);
public:
	typedef typename sge::sprite::state::detail::object_class<
		StateChoices
	>::type object_class;

	viewport_manager(
		object_class &,
		sge::renderer::device::ffp &,
		sge::viewport::manager &
	);

	~viewport_manager();
private:
	void
	on_manage(
		sge::renderer::target::viewport const &
	);

	object_class &objects_;

	sge::renderer::device::ffp &renderer_;

	fcppt::signal::scoped_connection const resize_connection_;
};

}
}
}
}

#endif
