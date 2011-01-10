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


#ifndef SGE_GUI_LAYOUTS_BASE_HPP_INCLUDED
#define SGE_GUI_LAYOUTS_BASE_HPP_INCLUDED

#include <sge/gui/widgets/fwd.hpp>
#include <sge/gui/layouts/base_fwd.hpp>
#include <sge/gui/point.hpp>
#include <sge/gui/dim.hpp>
#include <sge/gui/invalidation.hpp>
#include <sge/gui/export.hpp>
#include <sge/class_symbol.hpp>

namespace sge
{
namespace gui
{
namespace layouts
{
class SGE_CLASS_SYMBOL base
{
public:
	SGE_GUI_SYMBOL base();

	SGE_GUI_SYMBOL virtual void compile(invalidation::type const &);
	virtual void compile_static() = 0;
	virtual dim const optimal_size() const = 0;
	SGE_GUI_SYMBOL virtual void invalidate(
		widgets::base &,
		invalidation::type const &);

	SGE_GUI_SYMBOL widgets::base &connected_widget();
	SGE_GUI_SYMBOL widgets::base const &connected_widget() const;

	SGE_GUI_SYMBOL virtual ~base();
protected:
	void set_widget_size(
		widgets::base &,
		dim const &);
	void set_widget_pos(
		widgets::base &,
		point const &);
	void compile_widget(
		widgets::base &,
		invalidation::type const &);

private:
	widgets::base *widget_;

	friend class widgets::base;
	void connected_widget(widgets::base &);
};

}
}
}

#endif
