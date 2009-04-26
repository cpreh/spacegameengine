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

#ifndef SGE_GUI_DETAIL_MANAGERS_COMPILER_HPP_INCLUDED
#define SGE_GUI_DETAIL_MANAGERS_COMPILER_HPP_INCLUDED

#include <sge/gui/invalidation.hpp>
#include <sge/gui/detail/managers/fwd.hpp>
#include <sge/gui/detail/submanager.hpp>
#include <sge/gui/widgets/fwd.hpp>
#include <map>

namespace sge
{
namespace gui
{
namespace detail
{
namespace managers
{
class compiler : public submanager
{
	public:
	compiler(mouse &,render &);
	void add(widgets::base &);
	void update();
	void remove(widgets::base &);
	void invalidate(
		widgets::base &,
		invalidation::type const &);
	private:
	typedef std::map<
		widgets::base*,
		invalidation::type> recompile_container;

	mouse &mouse_;
	render &render_;
	recompile_container recompiles;
	recompile_container invalidates;

	void insert_or_combine(
		recompile_container &,
		widgets::base &,
		invalidation::type const &);
};
}
}
}
}

#endif
