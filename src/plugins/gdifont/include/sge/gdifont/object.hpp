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


#ifndef SGE_GDIFONT_OBJECT_HPP_INCLUDED
#define SGE_GDIFONT_OBJECT_HPP_INCLUDED

#include <sge/font/object.hpp>
#include <sge/font/parameters_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/font/text_unique_ptr.hpp>
#include <sge/gdifont/delete_object_deleter_fwd.hpp>
#include <sge/gdifont/device_context_fwd.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <sge/image/color/optional_format_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace gdifont
{

class object
:
	public sge::font::object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		sge::gdifont::device_context const &,
		sge::font::parameters const &
	);

	~object();
private:
	sge::font::text_unique_ptr
	create_text(
		sge::font::string const &,
		sge::font::text_parameters const &
	);

	sge::image::color::optional_format const
	color_format() const;

	sge::gdifont::device_context const &device_context_;

	typedef fcppt::scoped_ptr<
		boost::remove_pointer<
			HFONT
		>::type,
		sge::gdifont::delete_object_deleter
	> hfont_scoped_ptr;

	hfont_scoped_ptr const font_;
};

}
}

#endif
