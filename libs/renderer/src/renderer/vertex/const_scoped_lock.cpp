//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/impl/buffer/instantiate_const_scoped_lock.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vertex/const_buffer_ref.hpp>
#include <sge/renderer/vertex/const_scoped_lock.hpp>
#include <sge/renderer/vertex/tag.hpp>
#include <fcppt/reference_to_base.hpp>


sge::renderer::vertex::const_scoped_lock::const_scoped_lock(
	sge::renderer::vertex::const_buffer_ref const _buffer
)
:
	impl_{
		fcppt::reference_to_base<
			impl::buffer_type const
		>(
			_buffer
		)
	}
{
}

sge::renderer::vertex::const_scoped_lock::const_scoped_lock(
	sge::renderer::vertex::const_buffer_ref const _buffer,
	lock_area const &_area
)
:
	impl_{
		fcppt::reference_to_base<
			impl::buffer_type const
		>(
			_buffer
		),
		_area
	}
{
}

sge::renderer::vertex::const_scoped_lock::view
sge::renderer::vertex::const_scoped_lock::value() const
{
	return
		impl_.value();
}

sge::renderer::vertex::const_scoped_lock::~const_scoped_lock()
= default;

SGE_RENDERER_IMPL_BUFFER_INSTANTIATE_CONST_SCOPED_LOCK(
	sge::renderer::vertex::tag
);
