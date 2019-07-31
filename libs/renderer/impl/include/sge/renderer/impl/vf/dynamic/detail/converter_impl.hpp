//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_IMPL_VF_DYNAMIC_DETAIL_CONVERTER_IMPL_HPP_INCLUDED
#define SGE_RENDERER_IMPL_VF_DYNAMIC_DETAIL_CONVERTER_IMPL_HPP_INCLUDED

#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/impl/vf/dynamic/element_converter.hpp>
#include <sge/renderer/impl/vf/dynamic/lock_interval.hpp>
#include <sge/renderer/impl/vf/dynamic/unlock.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/renderer/vf/dynamic/color_format_vector.hpp>
#include <sge/renderer/vf/dynamic/part_fwd.hpp>
#include <sge/renderer/vf/dynamic/detail/converter_impl_fwd.hpp>
#include <sge/renderer/vf/dynamic/detail/lock_interval_set.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{
namespace dynamic
{
namespace detail
{

class converter_impl
{
	FCPPT_NONCOPYABLE(
		converter_impl
	);
public:
	converter_impl(
		sge::renderer::vf::dynamic::part const &,
		sge::renderer::vf::dynamic::color_format_vector const &
	);

	~converter_impl();

	void
	convert_lock(
		sge::renderer::raw_pointer data,
		sge::renderer::vertex::first,
		sge::renderer::vf::dynamic::detail::lock_interval_set const &,
		sge::renderer::impl::vf::dynamic::lock_interval const &
	);

	void
	convert_unlock(
		sge::renderer::raw_pointer data,
		sge::renderer::vertex::first,
		sge::renderer::impl::vf::dynamic::lock_interval const &
	);
private:
	void
	do_convert(
		sge::renderer::raw_pointer data,
		sge::renderer::vertex::first,
		sge::renderer::impl::vf::dynamic::lock_interval const &,
		sge::renderer::impl::vf::dynamic::unlock
	);

	typedef
	std::vector<
		sge::renderer::impl::vf::dynamic::element_converter
	>
	element_converter_vector;

	element_converter_vector const element_converters_;
};

}
}
}
}
}

#endif
