//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_BASIC_LOCKABLE_BUFFER_IMPL_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BASIC_LOCKABLE_BUFFER_IMPL_HPP_INCLUDED

#include <sge/image/algorithm/copy.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/traits/pixel/format_stride.hpp>
#include <sge/image/view/flipped.hpp>
#include <sge/image/view/make.hpp>
#include <sge/image/view/sub.hpp>
#include <sge/image/view/to_const.hpp>
#include <sge/opengl/range_check.hpp>
#include <sge/opengl/set_unpack_alignment.hpp>
#include <sge/opengl/stride_to_unpack_alignment.hpp>
#include <sge/opengl/texture/basic_buffer_parameters.hpp>
#include <sge/opengl/texture/basic_lockable_buffer.hpp>
#include <sge/opengl/texture/create_lock.hpp>
#include <sge/opengl/texture/is_render_target.hpp>
#include <sge/opengl/texture/scoped_work_binding.hpp>
#include <sge/opengl/texture/funcs/get_image.hpp>
#include <sge/opengl/texture/mipmap/create.hpp>
#include <sge/opengl/texture/mipmap/parameters.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/lock_flags/from_mode.hpp>
#include <sge/renderer/lock_flags/method.hpp>
#include <sge/renderer/lock_flags/read.hpp>
#include <sge/renderer/lock_flags/write.hpp>
#include <fcppt/const.hpp>
#include <fcppt/format.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/math/box/object_impl.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/math/dim/contents.hpp>
#include <fcppt/math/dim/null.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/optional/assign.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

template<
	typename Types
>
sge::opengl::texture::basic_lockable_buffer<
	Types
>::basic_lockable_buffer(
	format_type const _format,
	const_config_ref const _config,
	sge::opengl::texture::basic_buffer_parameters const &_parameters
)
:
	gl_base(
		_format,
		_config,
		_parameters
	),
	log_{
		_parameters.log()
	},
	context_(
		_parameters.context()
	),
	config_(
		_config
	),
	type_(
		_parameters.type()
	),
	resource_flags_(
		_parameters.resource_flags()
	),
	color_order_(
		_parameters.color_order()
	),
	color_base_type_(
		_parameters.color_base_type()
	),
	internal_color_format_(
		_parameters.internal_color_format()
	),
	stride_(
		sge::image::traits::pixel::format_stride<
			color_tag
		>(
			this->format()
		)
	),
	lock_(),
	lock_area_()
{
}

FCPPT_PP_POP_WARNING

template<
	typename Types
>
sge::opengl::texture::basic_lockable_buffer<
	Types
>::~basic_lockable_buffer()
= default;

template<
	typename Types
>
typename
sge::opengl::texture::basic_lockable_buffer<
	Types
>::view
sge::opengl::texture::basic_lockable_buffer<
	Types
>::lock(
	lock_area const &_area,
	sge::renderer::lock_mode const _mode
)
{
	this->lock_me(
		_area,
		sge::renderer::lock_flags::from_mode(
			_mode
		)
	);

	return
		this->lock_view();
}

template<
	typename Types
>
typename
sge::opengl::texture::basic_lockable_buffer<
	Types
>::const_view
sge::opengl::texture::basic_lockable_buffer<
	Types
>::lock_c(
	lock_area const &_area
) const
{
	this->lock_me(
		_area,
		sge::renderer::lock_flags::method::read
	);

	return
		this->lock_view();
}

template<
	typename Types
>
void
sge::opengl::texture::basic_lockable_buffer<
	Types
>::unlock() const
{
	lock_unique_ptr const &cur_lock(
		FCPPT_ASSERT_OPTIONAL_ERROR(
			lock_
		)
	);

	cur_lock->pre_unlock();

	if(
		sge::renderer::lock_flags::write(
			cur_lock->method()
		)
	)
	{
		// If this is also a read lock
		// we must copy the current view, which is
		// a slice into the whole texture retrieved,
		// to the destination buffer.
		if(
			sge::renderer::lock_flags::read(
				cur_lock->method()
			)
		)
		{
			// this will only copy, not convert!
			sge::image::algorithm::copy<
				image_tag
			>(
				this->lock_view(),
				sge::image::view::make<
					image_tag
				>(
					cur_lock->write_view_pointer(),
					this->lock_dim(),
					this->format(),
					fcppt::math::dim::null<
						pitch
					>()
				),
				sge::image::algorithm::may_overlap::no,
				sge::image::algorithm::uninitialized::yes
			);

			cur_lock->post_copy();
		}

		cur_lock->unlock();

		sge::opengl::texture::scoped_work_binding const binding(
			log_.get(),
			context_.get(),
			type_,
			this->id()
		);

		sge::opengl::set_unpack_alignment(
			context_.get(),
			sge::opengl::stride_to_unpack_alignment(
				stride_
			)
		);

		Types::dim_types::sub_function().get()(
			binding,
			context_.get(),
			config_.get(),
			this->buffer_type(),
			color_order_,
			color_base_type_,
			this->level(),
			this->size(),
			fcppt::optional::from(
				lock_area_,
				[
					this
				]{
					return
						lock_area(
							fcppt::math::vector::null<
								typename
								lock_area::vector
							>(),
							this->size()
						);
				}
			),
			cur_lock->write_pointer()
		);
	}

	lock_ =
		optional_lock_unique_ptr();
}

template<
	typename Types
>
void
sge::opengl::texture::basic_lockable_buffer<
	Types
>::lock_me(
	lock_area const &_lock_area,
	sge::renderer::lock_flags::method const _method
) const
{
	if(
		!sge::opengl::range_check(
			this->size(),
			_lock_area
		)
	)
	{
		throw sge::renderer::exception(
			(
				fcppt::format(
					FCPPT_TEXT("ogl: lock (%1%) out of range! dim is %2%!")
				)
				% _lock_area
				% this->size()
			).str()
		);
	}

	lock_unique_ptr const &cur_lock(
		fcppt::optional::assign(
			lock_,
			sge::opengl::texture::create_lock(
				context_,
				_method,
				fcppt::math::dim::contents(
					this->size()
				),
				fcppt::math::dim::contents(
					_lock_area.size()
				),
				stride_,
				resource_flags_
			)
		)
	);

	if(
		sge::renderer::lock_flags::read(
			_method
		)
	)
	{
		sge::opengl::texture::scoped_work_binding const binding(
			log_.get(),
			context_.get(),
			type_,
			this->id()
		);

		sge::opengl::texture::funcs::get_image(
			binding,
			this->buffer_type(),
			color_order_,
			color_base_type_,
			cur_lock->read_pointer(),
			this->level()
		);
	}

	cur_lock->lock();

	lock_area_ =
		// TODO(philipp): Change this
		_lock_area.size()
		==
		this->size()
		?
			optional_lock_area()
		:
			optional_lock_area(
				_lock_area
			)
		;
}

template<
	typename Types
>
typename
sge::opengl::texture::basic_lockable_buffer<
	Types
>::view
sge::opengl::texture::basic_lockable_buffer<
	Types
>::lock_view()
{
	lock_unique_ptr const &cur_lock(
		FCPPT_ASSERT_OPTIONAL_ERROR(
			lock_
		)
	);

	// If we are currently reading a texture, we have mapped the whole
	// texture and have to take a sub view. Also, opengl reads the image
	// flipped, so we have to flip it too.

	bool const reading(
		sge::renderer::lock_flags::read(
			cur_lock->method()
		)
	);

	view const ret(
		sge::image::view::make<
			image_tag
		>(
			reading
			?
				cur_lock->read_view_pointer()
			:
				cur_lock->write_view_pointer(),
			reading
			?
				this->size()
			:
				this->lock_dim(),
			this->format(),
			fcppt::math::dim::null<
				pitch
			>()
		)
	);

	return
		reading
		?
			fcppt::optional::maybe(
				lock_area_,
				fcppt::const_(
					ret
				),
				[
					&ret
				](
					lock_area const &_area
				)
				{
					return
						sge::image::view::flipped<
							image_tag
						>(
							sge::image::view::sub<
								image_tag
							>(
								ret,
								_area
							)
						);
				}
			)
		:
			ret
		;
}

template<
	typename Types
>
typename sge::opengl::texture::basic_lockable_buffer<
	Types
>::const_view
sge::opengl::texture::basic_lockable_buffer<
	Types
>::lock_view() const
{
	return
		sge::image::view::to_const<
			image_tag
		>(
			// NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
			const_cast<
				sge::opengl::texture::basic_lockable_buffer<
					Types
				> *
			>(
				this
			)->lock_view()
		);
}

template<
	typename Types
>
typename sge::opengl::texture::basic_lockable_buffer<
	Types
>::dim
sge::opengl::texture::basic_lockable_buffer<
	Types
>::lock_dim() const
{
	return
		fcppt::optional::maybe(
			lock_area_,
			[
				this
			]{
				return
					this->size();
			},
			[](
				lock_area const &_area
			)
			{
				return
					_area.size();
			}
		);
}

#endif
