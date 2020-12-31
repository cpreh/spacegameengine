//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/lock_segment.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/lock_flags/method.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/renderer/vf/dynamic/locked_part.hpp>


sge::renderer::vf::dynamic::locked_part::locked_part(
	sge::renderer::raw_pointer const _data,
	sge::renderer::lock_segment const _segment,
	sge::renderer::lock_flags::method const _lock_flags
)
:
	data_(
		_data
	),
	segment_(
		_segment
	),
	lock_flags_(
		_lock_flags
	)
{
}

sge::renderer::raw_pointer
sge::renderer::vf::dynamic::locked_part::data() const
{
	return
		data_;
}

sge::renderer::vertex::first
sge::renderer::vf::dynamic::locked_part::pos() const
{
	return
		sge::renderer::vertex::first{
			segment_.pos().x()
		};
}

sge::renderer::vertex::count
sge::renderer::vf::dynamic::locked_part::count() const
{
	return
		sge::renderer::vertex::count{
			segment_.size().w()
		};
}

sge::renderer::lock_flags::method
sge::renderer::vf::dynamic::locked_part::lock_flags() const
{
	return
		lock_flags_;
}
