//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_PROXY_DECL_HPP_INCLUDED
#define SGE_RENDERER_VF_PROXY_DECL_HPP_INCLUDED

#include <sge/renderer/vf/is_const_tag.hpp>
#include <sge/renderer/vf/is_part.hpp>
#include <sge/renderer/vf/label_value_type.hpp>
#include <sge/renderer/vf/pointer.hpp>
#include <sge/renderer/vf/proxy_fwd.hpp>
#include <sge/renderer/vf/vertex_fwd.hpp>


namespace sge::renderer::vf
{

template<
	typename Part,
	typename Constness
>
class proxy
{
public:
	static_assert(
		sge::renderer::vf::is_part<
			Part
		>::value
	);

	static_assert(
		sge::renderer::vf::is_const_tag<
			Constness
		>::value
	);

	using
	pointer
	=
	sge::renderer::vf::pointer<
		Constness
	>;

	using
	vertex_type
	=
	sge::renderer::vf::vertex<
		Part
	>;

	using
	elements
	=
	typename
	Part::elements;

	using
	offsets
	=
	typename
	Part::offsets;

	explicit
	proxy(
		pointer
	);

	proxy &
	operator=(
		vertex_type const &
	);

	template<
		typename Label
	>
	void
	set(
		sge::renderer::vf::label_value_type<
			Part,
			Label
		> const &
	);

	template<
		typename Label
	>
	[[nodiscard]]
	sge::renderer::vf::label_value_type<
		Part,
		Label
	>
	get() const;
private:
	pointer data_;
};

}

#endif
