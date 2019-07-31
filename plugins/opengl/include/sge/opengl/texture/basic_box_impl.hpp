//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_BASIC_BOX_IMPL_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BASIC_BOX_IMPL_HPP_INCLUDED

#include <sge/opengl/texture/basic_box.hpp>
#include <sge/opengl/texture/basic_parameters_fwd.hpp>
#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/opengl/texture/config_fwd.hpp>
#include <sge/opengl/texture/init.hpp>
#include <sge/opengl/texture/scoped_work_binding.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <sge/renderer/texture/mipmap/level_count.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

template<
	typename Types
>
sge::opengl::texture::basic_box<
	Types
>::basic_box(
	sge::opengl::texture::basic_parameters const &_basic_parameters,
	sge::opengl::texture::type const _type,
	parameters_type const &_parameters,
	sge::opengl::texture::config<
		Types::buffer_types::dim_types::num_dims
	> const &_config
)
:
	base_type(
		_basic_parameters,
		_type,
		_parameters
	),
	levels_(
		[
			&_basic_parameters,
			_type,
			&_parameters,
			&_config,
			this
		]{
			sge::opengl::texture::scoped_work_binding const binding(
				_basic_parameters.log(),
				_basic_parameters.context(),
				this->type(),
				this->id()
			);

			return
				sge::opengl::texture::init<
					Types
				>(
					binding,
					_basic_parameters,
					_parameters,
					_config,
					_type,
					sge::opengl::texture::buffer_type(
						_type.get()
					),
					this->id()
				);
		}()
	)
{
}

FCPPT_PP_POP_WARNING

template<
	typename Types
>
sge::opengl::texture::basic_box<
	Types
>::~basic_box()
{
}

template<
	typename Types
>
typename
sge::opengl::texture::basic_box<
	Types
>::nonconst_buffer &
sge::opengl::texture::basic_box<
	Types
>::level(
	sge::renderer::texture::mipmap::level const _level
)
{
	return
		*levels_[
			_level.get()
		];
}

template<
	typename Types
>
typename
sge::opengl::texture::basic_box<
	Types
>::const_buffer const &
sge::opengl::texture::basic_box<
	Types
>::level(
	sge::renderer::texture::mipmap::level const _level
) const
{
	return
		*levels_[
			_level.get()
		];
}

template<
	typename Types
>
sge::renderer::texture::mipmap::level_count
sge::opengl::texture::basic_box<
	Types
>::levels() const
{
	return
		fcppt::strong_typedef_construct_cast<
			sge::renderer::texture::mipmap::level_count,
			fcppt::cast::size_fun
		>(
			levels_.size()
		);
}

#endif
