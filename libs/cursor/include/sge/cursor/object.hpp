//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CURSOR_OBJECT_HPP_INCLUDED
#define SGE_CURSOR_OBJECT_HPP_INCLUDED

#include <sge/cursor/hotspot_fwd.hpp>
#include <sge/cursor/object_fwd.hpp>
#include <sge/cursor/detail/object_fwd.hpp>
#include <sge/cursor/detail/symbol.hpp>
#include <sge/input/processor_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sge
{
namespace cursor
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	SGE_CURSOR_DETAIL_SYMBOL
	object(
		sge::input::processor const &,
		sge::renderer::device::ffp &,
		sge::texture::part const &,
		sge::cursor::hotspot
	);

	SGE_CURSOR_DETAIL_SYMBOL
	object(
		object &&
	);

	SGE_CURSOR_DETAIL_SYMBOL
	object &
	operator=(
		object &&
	);

	SGE_CURSOR_DETAIL_SYMBOL
	~object();

	SGE_CURSOR_DETAIL_SYMBOL
	void
	draw(
		sge::renderer::context::ffp &
	);

	SGE_CURSOR_DETAIL_SYMBOL
	sge::cursor::hotspot
	hotspot() const;
private:
	fcppt::unique_ptr<
		sge::cursor::detail::object
	> impl_;
};

}
}

#endif
