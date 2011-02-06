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


#ifndef SGE_FREETYPE_METRICS_HPP_INCLUDED
#define SGE_FREETYPE_METRICS_HPP_INCLUDED

#include "library_fwd.hpp"
#include "face.hpp"
#include "freetype.hpp"
#include <sge/font/metrics.hpp>
#include <sge/font/size_type.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/char_type.hpp>
#include <sge/charconv/system_ptr.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/noncopyable.hpp>
#include <map>

namespace sge
{
namespace freetype
{

class metrics
:
	public font::metrics
{
	FCPPT_NONCOPYABLE(
		metrics
	);
public:
	metrics(
		library &,
		sge::charconv::system_ptr,
		fcppt::filesystem::path const &,
		font::size_type font_height
	);

	~metrics();

	font::char_metric_ptr const
	load_char(
		font::char_type
	);

	font::unit
	line_height() const;
private:
	freetype::face face_;
	
	sge::charconv::system_ptr const conv_system_;

	font::size_type pixel_size_;

	typedef std::map<
		font::char_type,
		font::char_metric_ptr
	> buffer_type;

	buffer_type buffer_;
};

}
}

#endif
