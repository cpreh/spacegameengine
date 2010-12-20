/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/renderer/texture_rw.hpp>
#include <sge/renderer/scoped_texture_lock.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/view/to_const.hpp>
#include <sge/exception.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/assert_message.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional_impl.hpp>
#include <typeinfo>

class sge::renderer::texture_rw::lock_data
{
public:
	typedef fcppt::optional<
		image2d::view::object
	> optional_image;

	lock_rect area_;

	optional_image view_;

	lock_data(
		lock_rect const &_area,
		optional_image const &_view = optional_image()
	)
	:
		area_(_area),
		view_(_view)
	{}
};

sge::renderer::texture_rw::texture_rw(
	texture_ptr const _read,
	texture_ptr const _write
)
:
	read_(_read),
	write_(_write)
{
	FCPPT_ASSERT_MESSAGE(
		read_->dim() == write_->dim(),
		FCPPT_TEXT("read dimension has to be the same as write dimension")
	);
}

sge::renderer::texture_rw::~texture_rw()
{}

sge::renderer::texture_rw::dim_type const
sge::renderer::texture_rw::dim() const
{
	return read_->dim();
}

sge::image2d::view::object const
sge::renderer::texture_rw::lock(
	lock_rect const &_rect,
	lock_mode::type const _mode
)
{
	FCPPT_ASSERT_MESSAGE(
		!locked_,
		FCPPT_TEXT("already locked texture_rw")
	);

	locked_.take(
		fcppt::make_unique_ptr<
			lock_data
		>(
			_rect,
			read_->lock(
				_rect,
				_mode
			)
		)
	);

	return *locked_->view_;
}

sge::image2d::view::const_object const
sge::renderer::texture_rw::lock(
	lock_rect const &_rect
) const
{
	FCPPT_ASSERT_MESSAGE(
		!locked_,
		FCPPT_TEXT("already locked texture_rw")
	);

	locked_.take(
		fcppt::make_unique_ptr<
			lock_data
		>(
			_rect
		)
	);

	return
		read_->lock(
			_rect
		);
}

void
sge::renderer::texture_rw::unlock() const
{
	FCPPT_ASSERT_MESSAGE(
		locked_,
		FCPPT_TEXT("unlocking texture_rw without (proper) locking")
	);

	// we didn't just lock to read?
	if (locked_->view_)
	{
		scoped_texture_lock const lock_(
			write_,
			locked_->area_,
			lock_mode::writeonly
		);

		image2d::algorithm::copy_and_convert(
			image2d::view::to_const(
				*locked_->view_
			),
			lock_.value());
	}

	read_->unlock();

	locked_.reset();
}

sge::renderer::resource_flags_field const
sge::renderer::texture_rw::flags() const
{
	return resource_flags::dynamic;
}

sge::renderer::texture_ptr const
sge::renderer::texture_rw::read() const
{
	return read_;
}

sge::renderer::texture_ptr const
sge::renderer::texture_rw::write() const
{
	return write_;
}
