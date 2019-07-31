//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CEGUI_IMPL_IMAGE_CODEC_HPP_INCLUDED
#define SGE_CEGUI_IMPL_IMAGE_CODEC_HPP_INCLUDED

#include <sge/cegui/impl/image_codec_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/ImageCodec.h>
#include <fcppt/config/external_end.hpp>


namespace CEGUI
{
class RawDataContainer;
class Texture;
}

namespace sge
{
namespace cegui
{
namespace impl
{

class image_codec
:
	public CEGUI::ImageCodec
{
	FCPPT_NONCOPYABLE(
		image_codec
	);
public:
	explicit
	image_codec(
		sge::image2d::system &
	);

	~image_codec()
	override;
private:
	CEGUI::Texture *
	load(
		CEGUI::RawDataContainer const &,
		CEGUI::Texture *
	)
	override;
public:
	sge::image2d::system &
	image_system() const;
private:
	sge::image2d::system &image_system_;
};

}
}
}

#endif
