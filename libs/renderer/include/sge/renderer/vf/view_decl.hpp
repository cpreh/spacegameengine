//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_VIEW_DECL_HPP_INCLUDED
#define SGE_RENDERER_VF_VIEW_DECL_HPP_INCLUDED

#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vf/iterator_fwd.hpp>
#include <sge/renderer/vf/pointer.hpp>
#include <sge/renderer/vf/view_fwd.hpp>
#include <sge/renderer/vf/dynamic/basic_view_fwd.hpp>


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
class view
{
public:
	typedef sge::renderer::vf::iterator<
		Part,
		Constness
	> iterator;

	typedef
	sge::renderer::vf::pointer<
		Constness
	>
	pointer;

	typedef sge::renderer::vf::dynamic::basic_view<
		pointer
	> dynamic_view_type;

	typedef sge::renderer::vertex::count size_type;

	explicit
	view(
		dynamic_view_type const &
	);

	template<
		typename OtherView
	>
	explicit
	view(
		sge::renderer::vf::dynamic::basic_view<
			OtherView
		> const &
	);

	iterator
	begin() const;

	iterator
	end() const;
private:
	pointer data_;

	size_type size_;
};

}
}
}

#endif
