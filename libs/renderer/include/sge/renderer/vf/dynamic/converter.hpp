//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_DYNAMIC_CONVERTER_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_CONVERTER_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/vf/dynamic/color_format_vector.hpp>
#include <sge/renderer/vf/dynamic/locked_part.hpp>
#include <sge/renderer/vf/dynamic/part_fwd.hpp>
#include <sge/renderer/vf/dynamic/detail/converter_impl_fwd.hpp>
#include <sge/renderer/vf/dynamic/detail/lock_interval_set.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/optional/object_decl.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{
namespace dynamic
{

class converter
{
	FCPPT_NONCOPYABLE(
		converter
	);
public:
	SGE_RENDERER_DETAIL_SYMBOL
	converter(
		sge::renderer::vf::dynamic::part const &,
		sge::renderer::vf::dynamic::color_format_vector const &
	);

	SGE_RENDERER_DETAIL_SYMBOL
	~converter();

	SGE_RENDERER_DETAIL_SYMBOL
	void
	lock(
		sge::renderer::vf::dynamic::locked_part const &
	);

	SGE_RENDERER_DETAIL_SYMBOL
	void
	unlock();

	SGE_RENDERER_DETAIL_SYMBOL
	void
	reset();
private:
	sge::renderer::vf::dynamic::part const &part_;

	sge::renderer::vf::dynamic::color_format_vector const accepted_formats_;

	sge::renderer::vf::dynamic::detail::lock_interval_set written_intervals_;

	typedef
	fcppt::optional::object<
		sge::renderer::vf::dynamic::locked_part
	>
	optional_locked_part;

	optional_locked_part locked_part_;

	typedef
	fcppt::unique_ptr<
		sge::renderer::vf::dynamic::detail::converter_impl
	>
	converter_unique_ptr;

	typedef
	fcppt::optional::object<
		converter_unique_ptr
	>
	optional_converter_unique_ptr;

	optional_converter_unique_ptr converter_;
};

}
}
}
}

#endif
