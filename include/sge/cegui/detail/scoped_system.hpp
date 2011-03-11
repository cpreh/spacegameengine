#ifndef SGE_CEGUI_DETAIL_SCOPED_SYSTEM_HPP_INCLUDED
#define SGE_CEGUI_DETAIL_SCOPED_SYSTEM_HPP_INCLUDED

#include <sge/cegui/detail/renderer_fwd.hpp>
#include <sge/cegui/detail/image_codec_fwd.hpp>
#include <sge/cegui/detail/resource_provider_fwd.hpp>

namespace sge
{
namespace cegui
{
namespace detail
{
class scoped_system
{
public:
	explicit
	scoped_system(
		renderer &,
		image_codec &,
		resource_provider &);

	~scoped_system();
};
}
}
}

#endif
