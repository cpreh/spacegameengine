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


#ifndef SGE_WINDOW_OBJECT_HPP_INCLUDED
#define SGE_WINDOW_OBJECT_HPP_INCLUDED

#include <sge/window/dim_fwd.hpp>
#include <sge/window/event_function.hpp>
#include <sge/window/event_function_type.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/system_fwd.hpp>
#include <sge/window/detail/symbol.hpp>
#include <awl/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_decl.hpp>


namespace sge
{
namespace window
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	SGE_WINDOW_DETAIL_SYMBOL
	object(
		sge::window::system &,
		awl::window::object &
	);

	SGE_WINDOW_DETAIL_SYMBOL
	~object();

	SGE_WINDOW_DETAIL_SYMBOL
	sge::window::dim
	size() const;

	SGE_WINDOW_DETAIL_SYMBOL
	void
	show();

	SGE_WINDOW_DETAIL_SYMBOL
	awl::window::object &
	awl_object() const;

	SGE_WINDOW_DETAIL_SYMBOL
	fcppt::signal::auto_connection
	event_handler(
		sge::window::event_function
	);

	SGE_WINDOW_DETAIL_SYMBOL
	sge::window::system &
	system() const;
private:
	sge::window::system &system_;

	awl::window::object &awl_object_;

	typedef
	fcppt::signal::object<
		sge::window::event_function_type
	>
	event_signal;

	event_signal event_signal_;

	fcppt::signal::auto_connection const connection_;
};

}
}

#endif
