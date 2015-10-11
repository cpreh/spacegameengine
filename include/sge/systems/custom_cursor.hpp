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


#ifndef SGE_SYSTEMS_CUSTOM_CURSOR_HPP_INCLUDED
#define SGE_SYSTEMS_CUSTOM_CURSOR_HPP_INCLUDED

#include <sge/input/cursor/object_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/systems/cursor_hotspot_fwd.hpp>
#include <sge/systems/custom_cursor_fwd.hpp>
#include <sge/systems/detail/custom_cursor_fwd.hpp>
#include <sge/systems/detail/symbol.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sge
{
namespace systems
{

class custom_cursor
{
	FCPPT_NONCOPYABLE(
		custom_cursor
	);
public:
	SGE_SYSTEMS_DETAIL_SYMBOL
	custom_cursor(
		sge::renderer::device::ffp &,
		sge::input::cursor::object &,
		sge::texture::part const &,
		sge::systems::cursor_hotspot
	);

	SGE_SYSTEMS_DETAIL_SYMBOL
	custom_cursor(
		custom_cursor &&
	);

	SGE_SYSTEMS_DETAIL_SYMBOL
	custom_cursor &
	operator=(
		custom_cursor &&
	);

	SGE_SYSTEMS_DETAIL_SYMBOL
	~custom_cursor();

	SGE_SYSTEMS_DETAIL_SYMBOL
	void
	draw(
		sge::renderer::context::ffp &
	);

	SGE_SYSTEMS_DETAIL_SYMBOL
	sge::systems::cursor_hotspot
	hotspot() const;
private:
	fcppt::unique_ptr<
		sge::systems::detail::custom_cursor
	> impl_;
};

}
}

#endif
