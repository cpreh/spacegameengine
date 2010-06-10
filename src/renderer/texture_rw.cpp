/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/image/algorithm/copy_and_convert.hpp>
#include <sge/image/view/make_const.hpp>
#include <sge/exception.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/assert_message.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional_impl.hpp>
#include <typeinfo>

class sge::renderer::texture_rw::lock_data {
public:
	typedef fcppt::optional<
		image::view::object
	> optional_image;

	lock_rect area;
	optional_image view;

	lock_data(
		lock_rect const &area,
		optional_image const &view = optional_image()
	)
	:
		area(area),
		view(view)
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

sge::image::view::object const
sge::renderer::texture_rw::lock(
	lock_rect const &lr,
	lock_mode::type const lf
)
{
	FCPPT_ASSERT_MESSAGE(
		!locked,
		FCPPT_TEXT("already locked texture_rw")
	);

	locked.reset(
		new lock_data(
			lr,
			read_->lock(
				lr,
				lf
			)
		)
	);

	return *locked->view;
}

sge::image::view::const_object const
sge::renderer::texture_rw::lock(
	lock_rect const &lr
) const
{
	FCPPT_ASSERT_MESSAGE(
		!locked,
		FCPPT_TEXT("already locked texture_rw")
	);

	locked.reset(
		new lock_data(
			lr
		)
	);

	return read_->lock(
		lr
	);
}

void
sge::renderer::texture_rw::unlock() const
{
	FCPPT_ASSERT_MESSAGE(
		locked,
		FCPPT_TEXT("unlocking texture_rw without (proper) locking")
	);

	// we didn't just lock to read?
	if (locked->view)
	{
		scoped_texture_lock const lock_(
			write_,
			locked->area,
			lock_mode::writeonly
		);

		image::algorithm::copy_and_convert(
			image::view::make_const(
				*locked->view
			),
			lock_.value());
	}

	read_->unlock();
	locked.reset();
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
