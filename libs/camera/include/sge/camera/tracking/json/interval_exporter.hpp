//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CAMERA_TRACKING_JSON_INTERVAL_EXPORTER_HPP_INCLUDED
#define SGE_CAMERA_TRACKING_JSON_INTERVAL_EXPORTER_HPP_INCLUDED

#include <sge/camera/base.hpp>
#include <sge/camera/update_duration.hpp>
#include <sge/camera/detail/symbol.hpp>
#include <sge/camera/tracking/keyframe_sequence.hpp>
#include <sge/timer/basic.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace camera
{
namespace tracking
{
namespace json
{
class interval_exporter
{
FCPPT_NONCOPYABLE(
	interval_exporter);
public:
	SGE_CAMERA_DETAIL_SYMBOL
	interval_exporter(
		sge::camera::base const &,
		sge::camera::update_duration const &,
		boost::filesystem::path const &);

	SGE_CAMERA_DETAIL_SYMBOL
	void
	update();

	SGE_CAMERA_DETAIL_SYMBOL
	~interval_exporter()
	noexcept(
		false
	);
private:
	sge::camera::base const &camera_;
	sge::timer::basic<sge::timer::clocks::standard> update_timer_;
	boost::filesystem::path const export_file_path_;
	sge::camera::tracking::keyframe_sequence keyframes_;
};
}
}
}
}

#endif
