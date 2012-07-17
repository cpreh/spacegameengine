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


#include <sge/resource_tree/path.hpp>
#include <sge/resource_tree/detail/strip_file_extension.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/next_prior.hpp>
#include <boost/spirit/home/phoenix/core.hpp>
#include <boost/spirit/home/phoenix/operator.hpp>
#include <functional>
#include <numeric>
#include <fcppt/config/external_end.hpp>


sge::resource_tree::path const
sge::resource_tree::detail::strip_file_extension(
	sge::resource_tree::path const &p)
{
	fcppt::string const filename =
		p.back();

	fcppt::string::size_type const dot_position =
		filename.find(
			FCPPT_TEXT('.'));

	if(dot_position == fcppt::string::npos)
		return p;

	return
		std::accumulate(
			p.begin(),
			boost::prior(
				p.end()),
			resource_tree::path(),
			boost::phoenix::arg_names::arg1 / boost::phoenix::arg_names::arg2) /
		filename.substr(0,dot_position);
}
