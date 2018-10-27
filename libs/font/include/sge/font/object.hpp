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


#ifndef SGE_FONT_OBJECT_HPP_INCLUDED
#define SGE_FONT_OBJECT_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/font/metrics_fwd.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/font/text_unique_ptr.hpp>
#include <sge/font/detail/symbol.hpp>
#include <sge/image/color/optional_format_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace font
{

class SGE_CORE_DETAIL_CLASS_SYMBOL object
{
	FCPPT_NONCOPYABLE(
		object
	);
protected:
	SGE_FONT_DETAIL_SYMBOL
	object();
public:
	SGE_FONT_DETAIL_SYMBOL
	virtual
	~object();

	virtual
	sge::font::text_unique_ptr
	create_text(
		sge::font::string const &,
		sge::font::text_parameters const &
	) = 0;

	/**
	\brief Tells which color format is preferred by this font, if any.
	*/
	virtual
	sge::image::color::optional_format
	preferred_color_format() const = 0;

	virtual
	sge::font::metrics
	metrics() const = 0;
};

}
}

#endif
