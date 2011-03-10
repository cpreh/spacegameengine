#ifndef SGE_CEGUI_IMAGE_CODEC_HPP_INCLUDED
#define SGE_CEGUI_IMAGE_CODEC_HPP_INCLUDED

#include <sge/cegui/symbol.hpp>
#include <sge/class_symbol.hpp>
#include <sge/image2d/multi_loader_fwd.hpp>
#include <CEGUI/CEGUIImageCodec.h>

namespace sge
{
namespace cegui
{
class SGE_CLASS_SYMBOL image_codec
:
	public CEGUI::ImageCodec
{
public:
	SGE_CEGUI_SYMBOL explicit	
	image_codec(
		sge::image2d::multi_loader &);

	SGE_CEGUI_SYMBOL CEGUI::Texture *
	load(
		CEGUI::RawDataContainer const &,
		CEGUI::Texture *);

	SGE_CEGUI_SYMBOL sge::image2d::multi_loader &
	loader() const;
private:
	sge::image2d::multi_loader &image_loader_;
};
}
}

#endif
