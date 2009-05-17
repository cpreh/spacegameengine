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
#include <sge/gui/layouts/null.hpp>
#include <sge/gui/widgets/base.hpp>
#include <sge/gui/manager.hpp>
#include <sge/math/rect/basic_impl.hpp>
#include <sge/gui/log.hpp>

namespace
{
sge::gui::logger mylogger(
	sge::gui::global_log(),
	SGE_TEXT("layouts::null"),
	false);
}

sge::gui::layouts::null::null()
: 
	base()
{
}

void sge::gui::layouts::null::compile(
	invalidation::type const &)
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("in compile, doing nothing"));
}

void sge::gui::layouts::null::compile_static()
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("in compile_static, doing nothing"));
	
	connected_widget().parent_manager().dirty(
		connected_widget(),
		rect(
			rect::point_type::null(),
			connected_widget().size()));
}

sge::gui::dim const sge::gui::layouts::null::optimal_size() const
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("getting size hint from skin"));
	return connected_widget().parent_manager().skin().optimal_size(
		connected_widget());
}
