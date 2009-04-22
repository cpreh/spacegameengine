#include <sge/renderer/texture_rw.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/exception.hpp>
#include <sge/renderer/scoped_texture_lock.hpp>
#include <sge/renderer/copy_and_convert_pixels.hpp>
#include <sge/renderer/make_const_image_view.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/assert.hpp>
#include <sge/text.hpp>
#include <sge/optional.hpp>
#include <typeinfo>

class sge::renderer::texture_rw::lock_data {
public:
	typedef optional<
		image_view
	> optional_image_view;

	lock_rect area;
	optional_image_view view;

	lock_data(
		lock_rect const &area,
		optional_image_view const &view = optional_image_view())
	:
		area(area),
		view(view)
	{}
};

sge::renderer::texture_rw::texture_rw(
	texture_ptr const _read,
	texture_ptr const _write)
:
	read_(_read),
	write_(_write)
{
	SGE_ASSERT_MESSAGE(
		read_->dim() == write_->dim(),
		SGE_TEXT("read dimension has to be the same as write dimension"));
}

sge::renderer::texture_rw::~texture_rw()
{}

sge::renderer::texture_rw::dim_type const sge::renderer::texture_rw::dim() const
{
	return read_->dim();
}

sge::renderer::image_view const sge::renderer::texture_rw::lock(lock_rect const &lr,lock_flag_t const lf)
{
	SGE_ASSERT_MESSAGE(!locked,SGE_TEXT("already locked texture_rw"));
	locked.reset(new lock_data(lr,read_->lock(lr,lf)));
	return *locked->view;
}

sge::renderer::const_image_view const sge::renderer::texture_rw::lock(lock_rect const &lr) const
{
	SGE_ASSERT_MESSAGE(!locked,SGE_TEXT("already locked texture_rw"));
	locked.reset(new lock_data(lr));
	return read_->lock(lr);
}

void sge::renderer::texture_rw::unlock() const
{
	SGE_ASSERT_MESSAGE(locked,SGE_TEXT("unlocking texture_rw without (proper) locking"));
	
	// we didn't just lock to read?
	if (locked->view)
	{
		scoped_texture_lock const lock_(
			write_,
			locked->area,
			lock_flags::writeonly);
		
		copy_and_convert_pixels(
			make_const_image_view(
				*locked->view),
			lock_.value());
	}

	read_->unlock();
	locked.reset();
}

sge::renderer::resource_flag_t
sge::renderer::texture_rw::flags() const
{
	return resource_flags::dynamic;
}

sge::renderer::texture_ptr const sge::renderer::texture_rw::read() const
{
	return read_;
}

sge::renderer::texture_ptr const sge::renderer::texture_rw::write() const
{
	return write_;
}
