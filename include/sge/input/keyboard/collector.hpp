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


#ifndef SGE_INPUT_KEYBOARD_COLLECTOR_HPP_INCLUDED
#define SGE_INPUT_KEYBOARD_COLLECTOR_HPP_INCLUDED

#include <sge/input/processor_fwd.hpp>
#include <sge/input/detail/symbol.hpp>
#include <sge/input/keyboard/collector_fwd.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_callback.hpp>
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <sge/input/keyboard/key_signal.hpp>
#include <sge/input/keyboard/manager.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/object_decl.hpp>


namespace sge
{
namespace input
{
namespace keyboard
{

class collector
:
	public sge::input::keyboard::device
{
	FCPPT_NONCOPYABLE(
		collector
	);
public:
	SGE_INPUT_DETAIL_SYMBOL
	explicit
	collector(
		sge::input::processor &
	);

	SGE_INPUT_DETAIL_SYMBOL
	~collector()
	override;

	SGE_INPUT_DETAIL_SYMBOL
	fcppt::signal::auto_connection
	key_callback(
		sge::input::keyboard::key_callback const &
	)
	override;
private:
	void
	key_callback_internal(
		sge::input::keyboard::device &,
		sge::input::keyboard::key_event const &
	);

	sge::input::keyboard::manager manager_;

	sge::input::keyboard::key_signal key_signal_;
};

}
}
}

#endif
