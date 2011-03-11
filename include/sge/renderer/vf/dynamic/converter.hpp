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


#ifndef SGE_RENDERER_VF_DYNAMIC_CONVERTER_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_CONVERTER_HPP_INCLUDED

#include <sge/renderer/vf/dynamic/part_fwd.hpp>
#include <sge/renderer/vf/dynamic/locked_part.hpp>
#include <sge/renderer/vf/dynamic/detail/converter_fwd.hpp>
#include <sge/renderer/vf/dynamic/detail/lock_interval_set.hpp>
#include <sge/image/algorithm/accepted_format_array.hpp>
#include <sge/symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/scoped_ptr_decl.hpp>

namespace sge
{
namespace renderer
{
namespace vf
{
namespace dynamic
{

class converter
{
	FCPPT_NONCOPYABLE(
		converter
	);
public:
	SGE_SYMBOL
	converter(
		dynamic::part const &,
		sge::image::algorithm::accepted_format_array const &
	);

	SGE_SYMBOL
	~converter();

	SGE_SYMBOL
	void
	lock(
		dynamic::locked_part const &
	);

	SGE_SYMBOL
	void
	unlock();
private:
	dynamic::part const &part_;

	sge::image::algorithm::accepted_format_array const accepted_formats_;

	dynamic::detail::lock_interval_set written_intervals_;

	typedef fcppt::optional<
		dynamic::locked_part
	> optional_locked_part;

	optional_locked_part locked_part_;

	typedef fcppt::scoped_ptr<
		dynamic::detail::converter
	> converter_ptr;

	converter_ptr converter_;
};

}
}
}
}

#endif
