//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_VERTEX_IMPL_HPP_INCLUDED
#define SGE_RENDERER_VF_VERTEX_IMPL_HPP_INCLUDED

#include <sge/renderer/vf/vertex_decl.hpp>
#include <sge/renderer/vf/detail/copy_n.hpp>
#include <sge/renderer/vf/detail/element_stride.hpp>
#include <sge/renderer/vf/detail/raw_data.hpp>
#include <sge/renderer/vf/detail/read_wrapper_impl.hpp>
#include <fcppt/brigand/found_t.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/algorithms/index_of.hpp>
#include <brigand/sequences/at.hpp>
#include <fcppt/config/external_end.hpp>


template<
	typename Part,
	typename Constness
>
sge::renderer::vf::vertex<
	Part,
	Constness
>::vertex(
	pointer const _data
)
:
	data_(
		_data
	)
{
}

template<
	typename Part,
	typename Constness
>
template<
	typename Field
>
void
sge::renderer::vf::vertex<
	Part,
	Constness
>::set(
	typename Field::packed_type const &_value
)
{
	static_assert(
		fcppt::brigand::found_t<
			elements,
			Field
		>::value,
		"Field not part of vertex format"
	);

	typedef
	brigand::index_of<
		elements,
		Field
	>
	index;

	typedef
	brigand::at<
		elements,
		index
	>
	element;

	typedef
	brigand::at<
		offsets,
		index
	>
	offset;

	sge::renderer::vf::detail::copy_n(
		sge::renderer::vf::detail::raw_data(
			_value
		),
		sge::renderer::vf::detail::element_stride<
			element
		>::value,
		data_
		+
		offset::value
	);
}

template<
	typename Part,
	typename Constness
>
template<
	typename Field
>
typename
Field::packed_type
sge::renderer::vf::vertex<
	Part,
	Constness
>::get() const
{
	static_assert(
		fcppt::brigand::found_t<
			elements,
			Field
		>::value,
		"Field not part of vertex format"
	);

	typedef
	brigand::index_of<
		elements,
		Field
	>
	index;

	typedef
	brigand::at<
		elements,
		index
	>
	element;

	typedef
	brigand::at<
		offsets,
		index
	>
	offset;

	typedef
	typename
	element::packed_type
	packed_type;

	sge::renderer::vf::detail::read_wrapper<
		packed_type
	> ret{};

	sge::renderer::vf::detail::copy_n(
		data_
		+
		offset::value,
		sge::renderer::vf::detail::element_stride<
			element
		>::value,
		sge::renderer::vf::detail::raw_data(
			ret.get()
		)
	);

	return
		ret.get();
}

#endif
