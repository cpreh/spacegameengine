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


#include <sge/gui/widgets/label.hpp>
#include <sge/gui/widgets/parameters.hpp>
#include <sge/gui/events/invalid_area.hpp>
#include <sge/gui/manager.hpp>
#include <sge/gui/widgets/log.hpp>
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/text.hpp>

namespace
{

fcppt::log::object mylogger(
	fcppt::log::parameters::inherited(
		sge::gui::widgets::global_log(),
		FCPPT_TEXT("label")
	)
);

}

sge::gui::widgets::label::label(
	parent_data const &_parent,
	parameters _params,
	fcppt::string const &_text,
	sge::font::text::align_h::type _align_h,
	sge::font::text::align_v::type _align_v,
	optional_dim const &_static_size)
:
	base(
		_parent,
		_params.size_policy(
			sge::gui::size_policy(
				axis_policy::none,
				axis_policy::none))),
	text_(_text),
	align_h_(_align_h),
	align_v_(_align_v),
	static_size_(_static_size)
{
}

fcppt::string const sge::gui::widgets::label::text() const
{
	return text_;
}

sge::font::text::align_h::type sge::gui::widgets::label::align_h() const
{
	return align_h_;
}

sge::font::text::align_v::type sge::gui::widgets::label::align_v() const
{
	return align_v_;
}

void sge::gui::widgets::label::text(
	fcppt::string const &_text)
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_
			<< FCPPT_TEXT("setting text to: ")
			<< _text
	);
	text_ = _text;
	invalidate(
		*this,
		invalidation::all);
}

sge::gui::widgets::optional_dim const &
sge::gui::widgets::label::static_size() const
{
	return static_size_;
}
