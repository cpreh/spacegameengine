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


#ifndef SGE_WINDOW_SYSTEM_HPP_INCLUDED
#define SGE_WINDOW_SYSTEM_HPP_INCLUDED

#include <sge/window/object_ptr.hpp>
#include <sge/window/symbol.hpp>
#include <sge/window/system_fwd.hpp>
#include <awl/event/processor_fwd.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/system/event/processor_fwd.hpp>
#include <awl/window/instance_fwd.hpp>
#include <awl/window/event/processor_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace window
{

class system
{
	FCPPT_NONCOPYABLE(
		system
	);
public:
	SGE_WINDOW_SYMBOL
	system(
		awl::system::object &,
		awl::system::event::processor &,
		awl::event::processor &
	);

	SGE_WINDOW_SYMBOL
	~system();

	SGE_WINDOW_SYMBOL
	awl::system::object &
	awl_system() const;

	SGE_WINDOW_SYMBOL
	awl::event::processor &
	awl_event_processor() const;

	SGE_WINDOW_SYMBOL
	awl::system::event::processor &
	awl_system_event_processor() const;

	SGE_WINDOW_SYMBOL
	sge::window::object_ptr const
	create(
		awl::window::instance &,
		awl::window::event::processor &
	) const;

	SGE_WINDOW_SYMBOL
	bool
	poll();

	SGE_WINDOW_SYMBOL
	void
	next();
private:
	awl::system::object &awl_system_;

	awl::system::event::processor &awl_system_event_processor_;

	awl::event::processor &awl_event_processor_;
};

}
}

#endif
