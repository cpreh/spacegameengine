//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_PIXEL_FORMAT_DEPTH_STENCIL_HPP_INCLUDED
#define SGE_RENDERER_PIXEL_FORMAT_DEPTH_STENCIL_HPP_INCLUDED

#include <sge/renderer/pixel_format/depth_stencil_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace pixel_format
{

enum class depth_stencil
{
	/**
	\brief No depth buffer and no stencil buffer
	*/
	off,
	/**
	\brief 16 bit depth buffer, no stencil buffer
	*/
	d16,
	/**
	\brief 24 bit depth buffer, no stencil buffer
	*/
	d24,
	/**
	\brief 32 bit depth buffer, no stencil buffer
	*/
	d32,
	/**
	\brief 24 bit depth buffer, 8 bit stencil buffer
	*/
	d24s8
};

}
}
}

#endif
