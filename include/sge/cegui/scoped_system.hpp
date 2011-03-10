#ifndef SGE_CEGUI_SCOPED_SYSTEM_HPP_INCLUDED
#define SGE_CEGUI_SCOPED_SYSTEM_HPP_INCLUDED

#include <sge/cegui/symbol.hpp>
#include <sge/cegui/renderer_fwd.hpp>
#include <sge/cegui/image_codec_fwd.hpp>
#include <sge/cegui/resource_provider_fwd.hpp>

namespace sge
{
namespace cegui
{
class scoped_system
{
public:
	SGE_CEGUI_SYMBOL explicit
	scoped_system(
		renderer &,
		image_codec &,
		resource_provider &);

	SGE_CEGUI_SYMBOL ~scoped_system();
};
}
}

#endif
