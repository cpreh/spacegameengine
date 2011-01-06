#include "texture_dimension_string.hpp"
#include <sge/renderer/texture_base.hpp>
#include <sge/renderer/cube_texture.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/renderer/volume_texture.hpp>
#include <sge/renderer/glsl/string.hpp>
#include <boost/mpl/map/map10.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/string.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/at.hpp>

namespace
{
typedef
boost::mpl::map3
<
	boost::mpl::pair<sge::renderer::cube_texture,boost::mpl::string<'C','u','b','e'> >,
	boost::mpl::pair<sge::renderer::volume_texture,boost::mpl::string<'3','D'> >,
	boost::mpl::pair<sge::renderer::texture,boost::mpl::string<'2','D'> >
>
texture_to_sampler;

class stringizer
{
public:
	explicit
	stringizer(
		sge::renderer::glsl::string &_result,
		sge::renderer::texture_base const &_base)
	:
		result_(
			_result),
		base_(
			_base)
	{
	}

	template<typename T>
	void 
	operator()(
		T const &)
	{
		typedef typename
		T::first
		key;
		
		if (dynamic_cast<key const *>(&base_) == 0)
			return;

		typedef typename
		boost::mpl::at<texture_to_sampler,key>::type
		derived;

		result_ = 
			boost::mpl::c_str<derived>::value;
	}
private:
	sge::renderer::glsl::string &result_;
	sge::renderer::texture_base const &base_;
};
}

sge::renderer::glsl::string const
sge::shader::texture_dimension_string(
	sge::renderer::texture_base const &b)
{
	sge::renderer::glsl::string result;
	boost::mpl::for_each<texture_to_sampler>(
		stringizer(
			result,
			b));
	return "sampler"+result;
}
