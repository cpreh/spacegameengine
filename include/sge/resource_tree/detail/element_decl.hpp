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


#ifndef SGE_RESOURCE_TREE_DETAIL_ELEMENT_DECL_HPP_INCLUDED
#define SGE_RESOURCE_TREE_DETAIL_ELEMENT_DECL_HPP_INCLUDED

#include <sge/resource_tree/path.hpp>
#include <sge/resource_tree/detail/element_fwd.hpp>
#include <sge/resource_tree/detail/path_with_resource_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/random/variate_decl.hpp>
#include <fcppt/random/wrapper/uniform_container_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace resource_tree
{
namespace detail
{
/**
\brief Represents one directory with the immediately contained resources (no recursion)

An element is a container for resources along with their paths. When the tree
is asked to return a resource (designated by a path, of course), it...

<ul>
	<li>
		...iterates through its elements and checks if the current
		element's base path is equal to the specified path or not.
	</li>
	<li>
		If it's equal, it calls sge::resource_tree::element::get_random to
		get a random element.
	</li>
	<li>
		If it's not equal, check if the element contains the path using
		sge::resource_tree::element::contains. If it doesn't,
		proceed to the next element. If it does contain the path,
		return the resource attached to it using
		sge::resource_tree::element::get.
	</li>
</ul>
*/
template<
	typename T,
	typename Rng
>
class element
{
	FCPPT_NONCOPYABLE(
		element
	);
public:
	typedef
	std::vector<
		sge::resource_tree::detail::path_with_resource<
			T
		>
	>
	resource_container;

	element(
		sge::resource_tree::path &&,
		resource_container &&,
		Rng &
	);

	element(
		element &&
	);

	element &
	operator=(
		element &&
	);

	~element();

	sge::resource_tree::path const &
	base_path() const;

	T const &
	get_random() const;

	typedef
	fcppt::optional<
		T const &
	>
	optional_type;

	optional_type
	get_opt(
		sge::resource_tree::path const &
	) const;
private:
	sge::resource_tree::path base_path_;

	resource_container resources_;

	typedef
	fcppt::random::wrapper::uniform_container<
		resource_container
	>
	container_distribution;

	typedef
	fcppt::random::variate<
		Rng,
		container_distribution
	>
	variate;

	mutable
	fcppt::optional<
		variate
	>
	rng_;
};

}
}
}

#endif
