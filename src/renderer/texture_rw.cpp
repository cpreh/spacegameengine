#include <sge/renderer/texture_rw.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/iostream.hpp>
#include <sge/exception.hpp>
#include <sge/renderer/scoped_texture_lock.hpp>
#include <sge/renderer/copy_and_convert_pixels.hpp>
#include <sge/renderer/image_view_hack.hpp>
#include <sge/renderer/image_view_impl.hpp>
#include <sge/assert.hpp>
#include <typeinfo>

sge::renderer::texture_rw::texture_rw(texture_ptr const read,texture_ptr const write)
	: read(read),
	  write(write)
{
	SGE_ASSERT_MESSAGE(
		read->dim() == write->dim(),
		SGE_TEXT("read dimension has to be the same as write dimension"));
}

sge::renderer::texture_rw::dim_type const sge::renderer::texture_rw::dim() const
{
	return read->dim();
}

sge::renderer::image_view const sge::renderer::texture_rw::lock(lock_rect const &lr,lock_flag_t const lf)
{
	SGE_ASSERT_MESSAGE(!locked,SGE_TEXT("already locked texture_rw"));
	locked.reset(new lock_data(lr,read->lock(lr,lf)));
	return *locked->view;
}

sge::renderer::const_image_view const sge::renderer::texture_rw::lock(lock_rect const &lr) const
{
	SGE_ASSERT_MESSAGE(!locked,SGE_TEXT("already locked texture_rw"));
	locked.reset(new lock_data(lr));
	return read->lock(lr);
}

void sge::renderer::texture_rw::unlock() const
{
	SGE_ASSERT_MESSAGE(locked,SGE_TEXT("unlocking texture_rw without (proper) locking"));
	
	// we didn't just lock to read?
	if (locked->view)
	{
		scoped_texture_lock lock_(
			make_scoped_lock(write,locked->area,lock_flags::writeonly));
		copy_and_convert_pixels(make_const_view(*locked->view),lock_.value());
	}

	read->unlock();
	locked.reset();
}
