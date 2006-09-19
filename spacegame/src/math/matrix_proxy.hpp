#ifndef SGE_MATRIX_PROXY_HPP_INCLUDED
#define SGE_MATRIX_PROXY_HPP_INCLUDED

#include <cstddef>

namespace sge
{
namespace detail
{

template<typename Reference, typename Pointer, std::size_t Stride>
class matrix_proxy_impl {
public:
	typedef std::size_t size_type;
	Reference operator[](const size_type y) const { return p[y*Stride + x]; }
	matrix_proxy_impl(size_type x, const Pointer p) : x(x), p(p) {}
private:
	size_type x;
	Pointer p;

	matrix_proxy_impl& operator=(const matrix_proxy_impl&);
};
}

}

#endif
