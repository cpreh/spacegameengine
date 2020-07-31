//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RESOURCE_TREE_DETAIL_ELEMENT_IMPL_HPP_INCLUDED
#define SGE_RESOURCE_TREE_DETAIL_ELEMENT_IMPL_HPP_INCLUDED

#include <sge/resource_tree/exception.hpp>
#include <sge/resource_tree/path.hpp>
#include <sge/resource_tree/detail/element_decl.hpp>
#include <sge/resource_tree/detail/path_with_resource_impl.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/find_by_opt.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/random/make_variate.hpp>
#include <fcppt/random/variate_impl.hpp>
#include <fcppt/random/wrapper/make_uniform_container.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


template<
	typename T,
	typename Rng
>
sge::resource_tree::detail::element<
	T,
	Rng
>::element(
	resource_tree::path &&_base_path,
	resource_container &&_resources,
	fcppt::reference<
		Rng
	> const _rng
)
:
	base_path_(
		std::move(
			_base_path
		)
	),
	resources_(
		std::move(
			_resources
		)
	),
	rng_(
		fcppt::optional::map(
			fcppt::random::wrapper::make_uniform_container(
				resources_
			),
			[
				&_rng
			](
				fcppt::random::wrapper::uniform_container<
					resource_container
				> const &_distribution
			)
			{
				return
					fcppt::random::make_variate(
						_rng.get(), // TODO(philipp)
						_distribution
					);
			}
		)
	)
{
}

template<
	typename T,
	typename Rng
>
sge::resource_tree::detail::element<
	T,
	Rng
>::element(
	element &&
)
noexcept
= default;

template<
	typename T,
	typename Rng
>
sge::resource_tree::detail::element<
	T,
	Rng
> &
sge::resource_tree::detail::element<
	T,
	Rng
>::operator=(
	element &&
)
noexcept
= default;

template<
	typename T,
	typename Rng
>
sge::resource_tree::detail::element<
	T,
	Rng
>::~element()
= default;

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
T const &
sge::resource_tree::detail::element<
	T,
	Rng
>::get_random() const
{
	return
		fcppt::optional::to_exception(
			rng_,
			[
				this
			]{
				return
					sge::resource_tree::exception(
						FCPPT_TEXT("No elements in ")
						+
						base_path_.string()
					);
			}
		)().resource();
}

template<
	typename T,
	typename Rng
>
typename
sge::resource_tree::detail::element<
	T,
	Rng
>::optional_type
sge::resource_tree::detail::element<
	T,
	Rng
>::get_opt(
	sge::resource_tree::path const &_path
) const
{
	return
		fcppt::algorithm::find_by_opt(
			resources_,
			[
				&_path,
				this
			](
				sge::resource_tree::detail::path_with_resource<
					T
				> const &_cur
			)
			{
				return
					(
						base_path_
						/
						_cur.path().string()
					)
					==
					_path
					?
						optional_type(
							fcppt::make_cref(
								_cur.resource()
							)
						)
					:
						optional_type()
					;
			}
		);
}

#endif
