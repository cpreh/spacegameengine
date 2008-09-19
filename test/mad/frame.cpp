#include "frame.hpp"
#include "synth.hpp"
#include <sge/sstream.hpp>

sge::mad::frame::frame()
{
	mad_frame_init(&frame_);
}

sge::audio::sample_type sge::mad::frame::sample_rate() const
{
	return static_cast<audio::sample_type>(frame_.header.samplerate);
}

sge::audio::channel_type sge::mad::frame::channels() const
{
	return static_cast<audio::channel_type>(MAD_NCHANNELS(&frame_.header));
}

sge::mad::frame::~frame()
{
	mad_frame_finish(&frame_);
}

sge::string const sge::mad::frame::info() const
{
	sge::ostringstream ss;
	ss << MAD_NCHANNELS(&frame_.header) << " channels\n";
	ss << frame_.header.samplerate << " sample rate\n";

	ss << "layer ";
  switch(frame_.header.layer)
  {
    case MAD_LAYER_I:
			ss << "I";
		break;
    case MAD_LAYER_II:
      ss << "II";
		break;
    case MAD_LAYER_III:
      ss << "III";
		break;
    default:
      ss << "(unexpected layer value)";
		break;
  }

	ss << "\n";
	ss << "mode ";

	switch(frame_.header.mode)
  {
    case MAD_MODE_SINGLE_CHANNEL:
      ss << "single channel";
      break;
    case MAD_MODE_DUAL_CHANNEL:
      ss << "dual channel";
      break;
    case MAD_MODE_JOINT_STEREO:
      ss << "joint (MS/intensity) stereo";
      break;
    case MAD_MODE_STEREO:
      ss << "normal LR stereo";
      break;
    default:
      ss << "(unexpected mode value)";
      break;
  }

	ss << "\n";
	ss << "bit rate " << frame_.header.bitrate;

	return ss.str();
}
