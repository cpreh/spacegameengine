#ifndef SGE_CEGUI_DETAIL_IMAGE_CODEC_HPP_INCLUDED
#define SGE_CEGUI_DETAIL_IMAGE_CODEC_HPP_INCLUDED

#include <sge/image2d/multi_loader_fwd.hpp>
#include <CEGUI/CEGUIImageCodec.h>

namespace CEGUI
{
class RawDataContainer;
class Texture;
}

namespace sge
{
namespace cegui
{
namespace detail
{
class image_codec
:
	public CEGUI::ImageCodec
{
public:
	explicit	
	image_codec(
		sge::image2d::multi_loader &);

	CEGUI::Texture *
	load(
		CEGUI::RawDataContainer const &,
		CEGUI::Texture *);

	sge::image2d::multi_loader &
	loader() const;
private:
	sge::image2d::multi_loader &image_loader_;
};
}
}
}

#endif
