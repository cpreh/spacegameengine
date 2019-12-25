//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_PROXY_IMPL_HPP_INCLUDED
#define SGE_RENDERER_VF_PROXY_IMPL_HPP_INCLUDED

#include <sge/renderer/vf/proxy_decl.hpp>
#include <sge/renderer/vf/to_packed_type.hpp>
#include <sge/renderer/vf/detail/copy_n.hpp>
#include <sge/renderer/vf/detail/element_index.hpp>
#include <sge/renderer/vf/detail/element_stride.hpp>
#include <sge/renderer/vf/detail/raw_data.hpp>
#include <sge/renderer/vf/detail/read_wrapper_impl.hpp>
#include <fcppt/use.hpp>
#include <fcppt/tag_type.hpp>
#include <fcppt/algorithm/loop.hpp>
#include <fcppt/algorithm/loop_break_metal.hpp>
#include <fcppt/metal/set/to_list.hpp>
#include <fcppt/record/label_set.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <fcppt/config/external_end.hpp>


template<
	typename Part,
	typename Constness
>
sge::renderer::vf::proxy<
	Part,
	Constness
>::proxy(
	pointer const _data
)
:
	data_{
		_data
	}
{
}


template<
	typename Part,
	typename Constness
>
sge::renderer::vf::proxy<
	Part,
	Constness
> &
sge::renderer::vf::proxy<
	Part,
	Constness
>::operator=(
	vertex_type const &_value
)
{
	fcppt::algorithm::loop(
		fcppt::metal::set::to_list<
			fcppt::record::label_set<
				typename
				vertex_type::record_type
			>
		>{},
		[
			&_value,
			this
		](
			auto const &_label_tag
		)
		{
			FCPPT_USE(
				_label_tag
			);

			typedef
			fcppt::tag_type<
				decltype(
					_label_tag
				)
			>
			label;

			this-> template set<
				label
			>(
				_value. template get<
					label
				>()
			);
		}
	);

	return
		*this;
}

template<
	typename Part,
	typename Constness
>
template<
	typename Label
>
void
sge::renderer::vf::proxy<
	Part,
	Constness
>::set(
	sge::renderer::vf::label_value_type<
		Part,
		Label
	> const &_value
)
{
	typedef
	sge::renderer::vf::detail::element_index<
		elements,
		Label
	>
	index;

	typedef
	metal::at<
		elements,
		index
	>
	element;

	typedef
	metal::at<
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
		this->data_
		+
		offset::value
	);
}

template<
	typename Part,
	typename Constness
>
template<
	typename Label
>
sge::renderer::vf::label_value_type<
	Part,
	Label
>
sge::renderer::vf::proxy<
	Part,
	Constness
>::get() const
{
	typedef
	sge::renderer::vf::detail::element_index<
		elements,
		Label
	>
	index;

	typedef
	metal::at<
		elements,
		index
	>
	element;

	typedef
	metal::at<
		offsets,
		index
	>
	offset;

	typedef
	sge::renderer::vf::to_packed_type<
		element
	>
	packed_type;

	sge::renderer::vf::detail::read_wrapper<
		packed_type
	> ret{};

	sge::renderer::vf::detail::copy_n(
		this->data_
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
