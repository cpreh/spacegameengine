#ifndef SGE_REND_RENDERER_EXCEPTION_HPP_INCLUDED
#define SGE_REND_RENDERER_EXCEPTION_HPP_INCLUDED

#include <string>
#include <stdexcept>

namespace sge
{
	struct renderer_parameters;

	class device_reset : public std::runtime_error {
	public:
		device_reset(const renderer_parameters* const param = 0)
			: exception("device reset"), param(param) {}
		const renderer_parameters* get_param() const { return param; }
	private:
		const renderer_parameters* param;
	};
}

#endif
