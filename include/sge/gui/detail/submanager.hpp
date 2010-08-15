/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_GUI_DETAIL_SUBMANAGER_HPP_INCLUDED
#define SGE_GUI_DETAIL_SUBMANAGER_HPP_INCLUDED

#include <sge/gui/widgets/fwd.hpp>
#include <sge/gui/invalidation.hpp>
#include <sge/gui/activation_state.hpp>
#include <sge/gui/dim.hpp>
#include <sge/gui/depth_type.hpp>
#include <sge/gui/point.hpp>
#include <sge/gui/rect.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace gui
{
namespace detail
{
class submanager
{
	FCPPT_NONCOPYABLE(submanager)
	protected:
	submanager();
	public:
	virtual void update();
	virtual void add(
		widgets::base &);
	virtual void activation(
		widgets::base &,
		activation_state::type);
	virtual void remove(
		widgets::base &);
	virtual void dirty(
		widgets::base &,
		rect const &);
	virtual void resize(
		widgets::base &,
		dim const &);
	virtual void reposition(
		widgets::base &,
		point const &);
	virtual void invalidate(
		widgets::base &,
		invalidation::type const &);
	virtual void z(
		widgets::base &,
		depth_type);
	virtual ~submanager();
};
}
}
}

#endif
