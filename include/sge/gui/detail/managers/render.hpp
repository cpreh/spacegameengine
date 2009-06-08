/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_GUI_DETAIL_MANAGERS_RENDER_HPP_INCLUDED
#define SGE_GUI_DETAIL_MANAGERS_RENDER_HPP_INCLUDED

#include <sge/gui/detail/submanager.hpp>
#include <sge/gui/cursor/base_ptr.hpp>
#include <sge/gui/widgets/fwd.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/texture_fwd.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/object.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <map>

namespace sge
{
namespace gui
{
namespace detail
{
namespace managers
{
class render : public submanager
{
	public:
	render(
		renderer::device_ptr,
		cursor::base_ptr);
	void add(
		widgets::base &);
	void update();
	void draw();
	void activation(
		widgets::base &,
		activation_state::type);
	void remove(
		widgets::base &);
	void resize(
		widgets::base &,
		dim const &);
	void reposition(
		widgets::base &,
		point const &);
	void dirty(
		widgets::base &,
		rect const &);
	sge::sprite::object &connected_sprite(
		widgets::base &);
	void z(
		widgets::base &,
		depth_type);
	private:
	class widget_data
	{
	public:
		widget_data();

		renderer::texture_ptr texture;
		sprite::object sprite;
	};

	typedef boost::ptr_map<
		widgets::base*,
		widget_data> widget_container;
	typedef std::multimap<
		widgets::base*,
		rect> dirt_container;

	renderer::device_ptr rend;
	sprite::system ss;
	sprite::container sprites_;
	cursor::base_ptr cursor_;
	widget_container widgets;
	dirt_container dirt_;

	void clean();
};
}
}
}
}

#endif
