/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RESOURCE_TREE_DETAIL_ELEMENT_IMPL_HPP_INCLUDED
#define SGE_RESOURCE_TREE_DETAIL_ELEMENT_IMPL_HPP_INCLUDED

#include <sge/resource_tree/exception.hpp>
#include <sge/resource_tree/path.hpp>
#include <sge/resource_tree/detail/element_decl.hpp>
#include <sge/resource_tree/detail/path_with_resource_impl.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/throw.hpp>
#include <fcppt/random/variate_impl.hpp>
#include <fcppt/random/distribution/uniform_int_impl.hpp>


template<
	typename T,
	typename Rng
>
sge::resource_tree::detail::element<
	T,
	Rng
>::element(
	resource_tree::path const &_base_path,
	resource_container const &_resources,
	Rng &_rng)
:
	base_path_(
		_base_path),
	resources_(
		_resources),
	rng_(
		_rng,
		// TODO: Create something else for this!
		container_distribution(
			typename container_distribution::min(
				0u),
			// Empty resource containers are allowed.
			// In this case, rng_ should not be used.
			typename container_distribution::max(
				resources_.empty()
				?
					0u
				:
					resources_.size() - 1u)))
{
}

template<
	typename T,
	typename Rng
>
sge::resource_tree::path const &
sge::resource_tree::detail::element<
	T,
	Rng
>::base_path() const
{
	return
		base_path_;
}

template<
	typename T,
	typename Rng
>
bool
sge::resource_tree::detail::element<
	T,
	Rng
>::contains(
	sge::resource_tree::path const &_path
) const
{
	return
		this->get_opt(
			_path
		).has_value();
}

template<
	typename T,
	typename Rng
>
T
sge::resource_tree::detail::element<
	T,
	Rng
>::get(
	sge::resource_tree::path const &_path
) const
{
	optional_type const result(
		this->get_opt(
			_path
		)
	);

	if(
		!result
	)
		throw sge::resource_tree::exception(
			FCPPT_TEXT("Path ")
			+
			_path.string()
			+
			FCPPT_TEXT(" not found!")
		);

	return
		*result;
}

template<
	typename T,
	typename Rng
>
T
sge::resource_tree::detail::element<
	T,
	Rng
>::get_random() const
{
	FCPPT_ASSERT_THROW(
		!resources_.empty(),
		sge::resource_tree::exception
	);

	return
		resources_[
			rng_()
		].resource();
}

template<
	typename T,
	typename Rng
>
sge::resource_tree::detail::element<
	T,
	Rng
>::~element()
{
}

template<
	typename T,
	typename Rng
>
typename
sge::resource_tree::detail::element<
	T,
	Rng
>::optional_type const
sge::resource_tree::detail::element<
	T,
	Rng
>::get_opt(
	sge::resource_tree::path const &_path
) const
{
	for(
		auto const &cur : resources_
	)
		if(
			(
				base_path_
				/
				cur.path().string()
			)
			==
			_path
		)
			return
				optional_type(
					cur.resource()
				);
	return
		optional_type();
}

#endif
