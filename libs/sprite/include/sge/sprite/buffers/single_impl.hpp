//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_BUFFERS_SINGLE_IMPL_HPP_INCLUDED
#define SGE_SPRITE_BUFFERS_SINGLE_IMPL_HPP_INCLUDED

#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/sprite/count.hpp>
#include <sge/sprite/buffers/allocate.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/option_to_resource_flags.hpp>
#include <sge/sprite/buffers/parameters.hpp>
#include <sge/sprite/buffers/single_decl.hpp>
#include <sge/sprite/buffers/slice_impl.hpp>
#include <sge/sprite/buffers/vertex_count.hpp>
#include <sge/sprite/buffers/zero_offset.hpp>
#include <sge/sprite/buffers/roles/vertex_buffer.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/optional/assign.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/record/get.hpp>


template<
	typename Choices
>
sge::sprite::buffers::single<
	Choices
>::single(
	sge::sprite::buffers::parameters const &_parameters,
	sge::sprite::buffers::option const _buffers_option
)
:
	parameters_(
		_parameters
	),
	buffers_option_(
		_buffers_option
	),
	buffers_object_{}
{
}

template<
	typename Choices
>
sge::sprite::buffers::single<
	Choices
>::~single()
{
}

template<
	typename Choices
>
typename
sge::sprite::buffers::single<
	Choices
>::slice_type
sge::sprite::buffers::single<
	Choices
>::allocate(
	sge::sprite::count const _num_sprites
)
{
	return
		slice_type(
			fcppt::optional::maybe(
				buffers_object_,
				[
					this,
					_num_sprites
				]()
				{
					return
						fcppt::make_cref(
							fcppt::optional::assign(
								buffers_object_,
								sge::sprite::buffers::allocate<
									Choices
								>(
									parameters_,
									_num_sprites,
									sge::sprite::buffers::option_to_resource_flags(
										buffers_option_
									)
								)
							)
						);

				},
				[
					this,
					_num_sprites
				](
					buffers_object &_buffers
				)
				{
					if(
						fcppt::record::get<
							sge::sprite::buffers::roles::vertex_buffer
						>(
							_buffers
						)->linear_size()
						<
						sge::sprite::buffers::vertex_count<
							Choices
						>(
							_num_sprites
						).get()
					)
						_buffers =
							sge::sprite::buffers::allocate<
								Choices
							>(
								parameters_,
								_num_sprites,
								sge::sprite::buffers::option_to_resource_flags(
									buffers_option_
								)
							);

					return
						fcppt::make_cref(
							_buffers
						);
				}
			),
			sge::sprite::buffers::zero_offset<
				Choices
			>()
		);
}

template<
	typename Choices
>
sge::sprite::buffers::parameters const &
sge::sprite::buffers::single<
	Choices
>::parameters() const
{
	return
		parameters_;
}

#endif
