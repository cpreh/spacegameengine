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


#ifndef SGE_RESOURCE_TREE_DETAIL_INIT_HPP_INCLUDED
#define SGE_RESOURCE_TREE_DETAIL_INIT_HPP_INCLUDED

#include <sge/resource_tree/exception.hpp>
#include <sge/resource_tree/path_to_resource_function.hpp>
#include <sge/resource_tree/detail/add_directory.hpp>
#include <sge/resource_tree/detail/base_path.hpp>
#include <sge/resource_tree/detail/element_vector.hpp>
#include <sge/resource_tree/detail/sub_path.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/assert/throw_message.hpp>
#include <fcppt/container/join.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace resource_tree
{
namespace detail
{

template<
	typename T,
	typename Rng
>
sge::resource_tree::detail::element_vector<
	T,
	Rng
>
init(
	boost::filesystem::path const &_path,
	sge::resource_tree::path_to_resource_function<
		T
	> const &_path_to_resource,
	Rng &_random_generator
)
{
	FCPPT_ASSERT_THROW_MESSAGE(
		boost::filesystem::exists(
			_path
		),
		sge::resource_tree::exception,
		fcppt::filesystem::path_to_string(
			_path
		)
		+
		FCPPT_TEXT(" does not exist!")
	);

	FCPPT_ASSERT_THROW_MESSAGE(
		boost::filesystem::is_directory(
			_path
		),
		sge::resource_tree::exception,
		fcppt::filesystem::path_to_string(
			_path.string()
		)
		+
		FCPPT_TEXT(" is not a directory!")
	);

	typedef
	std::vector<
		boost::filesystem::path
	>
	path_vector;

	path_vector const directories(
		fcppt::container::join(
			path_vector{
				_path
			},
			boost::make_iterator_range(
				boost::filesystem::recursive_directory_iterator(
					_path
				),
				boost::filesystem::recursive_directory_iterator()
			)
			|
			boost::adaptors::filtered(
				[](
					boost::filesystem::path const &_cur_path
				)
				{
					return
						boost::filesystem::is_directory(
							_cur_path
						);
				}
			)
		)
	);

	return
		fcppt::algorithm::map<
			sge::resource_tree::detail::element_vector<
				T,
				Rng
			>
		>(
			directories,
			[
				&_path,
				&_path_to_resource,
				&_random_generator
			](
				boost::filesystem::path const &_cur_path
			)
			{
				return
					sge::resource_tree::detail::add_directory(
						sge::resource_tree::detail::base_path(
							_path
						),
						sge::resource_tree::detail::sub_path(
							_cur_path
						),
						_path_to_resource,
						_random_generator
					);
			}
		);
}

}
}
}

#endif
