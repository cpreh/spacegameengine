//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_VERTEX_DECL_HPP_INCLUDED
#define SGE_RENDERER_VF_VERTEX_DECL_HPP_INCLUDED

#include <sge/renderer/vf/pointer.hpp>
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
class vertex
{
public:
	typedef
	sge::renderer::vf::pointer<
		Constness
	>
	pointer;

	typedef typename Part::elements elements;

	typedef typename Part::offsets offsets;

	explicit
	vertex(
		pointer
	);

	template<
		typename Field
	>
	void
	set(
		typename Field::packed_type const &
	);

	template<
		typename Field
	>
	typename
	Field::packed_type
	get() const;
private:
	pointer data_;
};

}
}
}

#endif
