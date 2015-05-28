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


#ifndef SGE_FONT_SYSTEM_HPP_INCLUDED
#define SGE_FONT_SYSTEM_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/font/added_unique_ptr.hpp>
#include <sge/font/object_unique_ptr.hpp>
#include <sge/font/parameters_fwd.hpp>
#include <sge/font/system_fwd.hpp>
#include <sge/font/detail/symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/preprocessor/warn_unused_result.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace font
{

class SGE_CORE_DETAIL_CLASS_SYMBOL system
{
	FCPPT_NONCOPYABLE(
		system
	);
protected:
	SGE_FONT_DETAIL_SYMBOL
	system();
public:
	SGE_FONT_DETAIL_SYMBOL
	virtual
	~system() = 0;

	virtual
	sge::font::object_unique_ptr
	create_font(
		sge::font::parameters const &
	)
	FCPPT_PP_WARN_UNUSED_RESULT
	= 0;

	virtual
	sge::font::added_unique_ptr
	add_font(
		boost::filesystem::path const &
	)
	FCPPT_PP_WARN_UNUSED_RESULT
	= 0;
};

}
}

#endif
