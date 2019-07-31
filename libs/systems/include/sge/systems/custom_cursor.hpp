//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_CUSTOM_CURSOR_HPP_INCLUDED
#define SGE_SYSTEMS_CUSTOM_CURSOR_HPP_INCLUDED

#include <sge/input/processor_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/systems/cursor_hotspot_fwd.hpp>
#include <sge/systems/custom_cursor_fwd.hpp>
#include <sge/systems/detail/custom_cursor_fwd.hpp>
#include <sge/systems/detail/symbol.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sge
{
namespace systems
{

class custom_cursor
{
	FCPPT_NONCOPYABLE(
		custom_cursor
	);
public:
	SGE_SYSTEMS_DETAIL_SYMBOL
	custom_cursor(
		sge::input::processor const &,
		sge::renderer::device::ffp &,
		sge::texture::part const &,
		sge::systems::cursor_hotspot
	);

	SGE_SYSTEMS_DETAIL_SYMBOL
	custom_cursor(
		custom_cursor &&
	);

	SGE_SYSTEMS_DETAIL_SYMBOL
	custom_cursor &
	operator=(
		custom_cursor &&
	);

	SGE_SYSTEMS_DETAIL_SYMBOL
	~custom_cursor();

	SGE_SYSTEMS_DETAIL_SYMBOL
	void
	draw(
		sge::renderer::context::ffp &
	);

	SGE_SYSTEMS_DETAIL_SYMBOL
	sge::systems::cursor_hotspot
	hotspot() const;
private:
	fcppt::unique_ptr<
		sge::systems::detail::custom_cursor
	> impl_;
};

}
}

#endif
