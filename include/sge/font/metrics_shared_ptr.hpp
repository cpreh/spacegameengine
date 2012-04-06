#ifndef SGE_FONT_METRICS_SHARED_PTR_HPP_INCLUDED
#define SGE_FONT_METRICS_SHARED_PTR_HPP_INCLUDED

#include <sge/font/metrics_fwd.hpp>
#include <fcppt/shared_ptr_impl.hpp>

namespace sge
{
namespace font
{
typedef
fcppt::shared_ptr<
	sge::font::metrics
>
metrics_shared_ptr;
}
}

#endif

