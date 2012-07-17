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


#include <sge/resource_tree/base_path.hpp>
#include <sge/resource_tree/path.hpp>
#include <sge/resource_tree/strip_path_prefix.hpp>
#include <sge/resource_tree/sub_path.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/next_prior.hpp>
#include <boost/filesystem/path.hpp>
#include <iterator>
#include <fcppt/config/external_end.hpp>


sge::resource_tree::path const
sge::resource_tree::strip_path_prefix(
	resource_tree::base_path const &_base_path,
	resource_tree::sub_path const &_sub_path)
{
	sge::resource_tree::path result;
	for(
		boost::filesystem::path::const_iterator it =
			boost::next(
				_sub_path.get().begin(),
				std::distance(
					_base_path.get().begin(),
					_base_path.get().end()));
		it != _sub_path.get().end();
		++it)
		result /=
			fcppt::filesystem::path_to_string(
				it->string());
	return
		result;
}
