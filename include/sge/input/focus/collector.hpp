/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_INPUT_FOCUS_COLLECTOR_HPP_INCLUDED
#define SGE_INPUT_FOCUS_COLLECTOR_HPP_INCLUDED

#include <sge/input/processor_fwd.hpp>
#include <sge/input/detail/symbol.hpp>
#include <sge/input/focus/char_callback.hpp>
#include <sge/input/focus/char_signal.hpp>
#include <sge/input/focus/collector_fwd.hpp>
#include <sge/input/focus/count.hpp>
#include <sge/input/focus/in_callback.hpp>
#include <sge/input/focus/in_signal.hpp>
#include <sge/input/focus/key_callback.hpp>
#include <sge/input/focus/key_repeat_callback.hpp>
#include <sge/input/focus/key_repeat_signal.hpp>
#include <sge/input/focus/key_signal.hpp>
#include <sge/input/focus/manager.hpp>
#include <sge/input/focus/object.hpp>
#include <sge/input/focus/out_callback.hpp>
#include <sge/input/focus/out_signal.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/object_decl.hpp>


namespace sge
{
namespace input
{
namespace focus
{

class collector
:
	public sge::input::focus::object
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
	char_callback(
		sge::input::focus::char_callback const &
	)
	override;

	SGE_INPUT_DETAIL_SYMBOL
	fcppt::signal::auto_connection
	key_callback(
		sge::input::focus::key_callback const &
	)
	override;

	SGE_INPUT_DETAIL_SYMBOL
	fcppt::signal::auto_connection
	key_repeat_callback(
		sge::input::focus::key_repeat_callback const &
	)
	override;

	SGE_INPUT_DETAIL_SYMBOL
	fcppt::signal::auto_connection
	in_callback(
		sge::input::focus::in_callback const &
	)
	override;

	SGE_INPUT_DETAIL_SYMBOL
	fcppt::signal::auto_connection
	out_callback(
		sge::input::focus::out_callback const &
	)
	override;
private:
	sge::input::focus::count in_count_;

	sge::input::focus::char_signal char_signal_;

	sge::input::focus::key_signal key_signal_;

	sge::input::focus::key_repeat_signal key_repeat_signal_;

	sge::input::focus::in_signal in_signal_;

	sge::input::focus::out_signal out_signal_;

	sge::input::focus::manager manager_;
};

}
}
}

#endif
