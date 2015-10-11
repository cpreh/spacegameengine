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


#ifndef SGE_GUI_CONTEXT_HPP_INCLUDED
#define SGE_GUI_CONTEXT_HPP_INCLUDED

#include <sge/gui/context_fwd.hpp>
#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/widget/base_fwd.hpp>
#include <sge/gui/widget/optional_ref.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sge
{
namespace gui
{

class context
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	SGE_GUI_DETAIL_SYMBOL
	context();

	SGE_GUI_DETAIL_SYMBOL
	~context();

	void
	focus(
		sge::gui::widget::base &
	);

	void
	destroy(
		sge::gui::widget::base const &
	);

	sge::gui::widget::optional_ref
	focus() const;
private:
	sge::gui::widget::optional_ref focus_;
};

}
}

#endif
