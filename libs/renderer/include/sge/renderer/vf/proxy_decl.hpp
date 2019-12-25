//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_PROXY_DECL_HPP_INCLUDED
#define SGE_RENDERER_VF_PROXY_DECL_HPP_INCLUDED

#include <sge/renderer/vf/label_value_type.hpp>
#include <sge/renderer/vf/pointer.hpp>
#include <sge/renderer/vf/proxy_fwd.hpp>
#include <sge/renderer/vf/vertex_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{

template<
	typename Part,
	typename Constness
>
class proxy
{
public:
	typedef
	sge::renderer::vf::pointer<
		Constness
	>
	pointer;

	typedef
	sge::renderer::vf::vertex<
		Part
	>
	vertex_type;

	typedef typename Part::elements elements;

	typedef typename Part::offsets offsets;

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
	sge::renderer::vf::label_value_type<
		Part,
		Label
	>
	get() const;
private:
	pointer data_;
};

}
}
}

#endif
