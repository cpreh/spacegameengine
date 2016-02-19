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


#ifndef SGE_RESOURCE_TREE_DETAIL_ADD_DIRECTORY_HPP_INCLUDED
#define SGE_RESOURCE_TREE_DETAIL_ADD_DIRECTORY_HPP_INCLUDED

#include <sge/resource_tree/path_to_resource_function.hpp>
#include <sge/resource_tree/detail/base_path.hpp>
#include <sge/resource_tree/detail/element_impl.hpp>
#include <sge/resource_tree/detail/path_with_resource_impl.hpp>
#include <sge/resource_tree/detail/strip_file_extension.hpp>
#include <sge/resource_tree/detail/strip_path_prefix.hpp>
#include <sge/resource_tree/detail/sub_path.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <utility>
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
sge::resource_tree::detail::element<
	T,
	Rng
>
add_directory(
	sge::resource_tree::detail::base_path const &_base_path,
	sge::resource_tree::detail::sub_path const &_sub_path,
	sge::resource_tree::path_to_resource_function<
		T
	> const &_path_to_resource,
	Rng &_random_generator
)
{
	typedef
	sge::resource_tree::detail::element<
		T,
		Rng
	>
	element_type;

	typedef
	typename
	element_type::resource_container
	resource_container;

	resource_container resources(
		fcppt::algorithm::map_optional<
			resource_container
		>(
			boost::make_iterator_range(
				boost::filesystem::directory_iterator(
					_sub_path.get()
				),
				boost::filesystem::directory_iterator()
			),
			[
				&_sub_path,
				&_path_to_resource
			](
				boost::filesystem::path const &_path
			)
			{
				typedef
				sge::resource_tree::detail::path_with_resource<
					T
				>
				path_type;

				typedef
				fcppt::optional::object<
					path_type
				>
				result_type;

				return
					boost::filesystem::is_regular_file(
						_path
					)
					?
						result_type{
							path_type{
								sge::resource_tree::detail::strip_file_extension(
									sge::resource_tree::detail::strip_path_prefix(
										sge::resource_tree::detail::base_path(
											_sub_path.get()
										),
										sge::resource_tree::detail::sub_path(
											_path
										)
									)
								),
								_path_to_resource(
									_path
								)
							}
						}
					:
						result_type{}
					;
			}
		)
	);

	return
		// Second, create the element structure containing the files
		element_type{
			sge::resource_tree::detail::strip_path_prefix(
				_base_path,
				_sub_path
			),
			std::move(
				resources
			),
			_random_generator
		};
}

}
}
}

#endif
