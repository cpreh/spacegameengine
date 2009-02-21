#include "../frame.hpp"
#include "../synth.hpp"
#include <sge/sstream.hpp>
#include <sge/audio/exception.hpp>
#include <sge/container/raw_vector_impl.hpp>
#include <sge/log/headers.hpp>

sge::mad::frame::frame()
	: syn(*this)
{
	mad_frame_init(&frame_);
}

sge::audio::sample_count sge::mad::frame::sample_rate() const
{
	return static_cast<audio::sample_count>(frame_.header.samplerate);
}

sge::audio::channel_type sge::mad::frame::channels() const
{
	return static_cast<audio::channel_type>(MAD_NCHANNELS(&frame_.header));
}

unsigned sge::mad::frame::layer() const
{
	switch(frame_.header.layer)
	{
		case MAD_LAYER_I:
			return 1;
		case MAD_LAYER_II:
			return 2;
		case MAD_LAYER_III:
			return 3;
		default:
			throw audio::exception(
				SGE_TEXT("invalid mad layer"));
	}
}

sge::string const sge::mad::frame::info() const
{
	sge::ostringstream ss;
	ss << MAD_NCHANNELS(&frame_.header) << SGE_TEXT(" channels\n");
	ss << frame_.header.samplerate << SGE_TEXT(" sample rate\n");

	ss << SGE_TEXT("layer ");
	switch(frame_.header.layer)
	{
	 case MAD_LAYER_I:
		ss << SGE_TEXT('I');
		break;
	 case MAD_LAYER_II:
		ss << SGE_TEXT("II");
		break;
	 case MAD_LAYER_III:
		 ss << SGE_TEXT("III");
		break;
	 default:
		ss << SGE_TEXT("(unexpected layer value)");
		break;
	}

	ss << SGE_TEXT("\nmode ");

	switch(frame_.header.mode)
	{
	case MAD_MODE_SINGLE_CHANNEL:
		 ss << SGE_TEXT("single channel");
		 break;
	case MAD_MODE_DUAL_CHANNEL:
		ss << SGE_TEXT("dual channel");
		break;
	case MAD_MODE_JOINT_STEREO:
		ss << SGE_TEXT("joint (MS/intensity) stereo");
		 break;
	case MAD_MODE_STEREO:
		ss << SGE_TEXT("normal LR stereo");
		break;
	default:
		ss << SGE_TEXT("(unexpected mode value)");
		break;
	}

	ss << SGE_TEXT("\nbit rate ") << frame_.header.bitrate;

	return ss.str();
}

sge::audio::sample_container const sge::mad::frame::synthesize()
{
	syn.synthesize();

	// multiply by two because each sample is always 2 byte
	audio::sample_container dest(
		static_cast<audio::sample_container::size_type>(
			syn.sample_count()*2*2));

	audio::sample_container::iterator ptr = dest.begin();
	for (synth::const_iterator i = syn.begin(); i != syn.end(); ++i)
	{
		synth::sample_type sample = i->first;

		*ptr++ = static_cast<audio::sample_container::value_type>(sample & 0xff);
		*ptr++ = static_cast<audio::sample_container::value_type>(sample >> 8);

		if (channels() == static_cast<sge::audio::channel_type>(2))
			sample = i->second;

		*ptr++ = static_cast<audio::sample_container::value_type>(sample & 0xff);
		*ptr++ = static_cast<audio::sample_container::value_type>(sample >> 8);
	}

	return dest;
}

sge::mad::frame::~frame()
{
	mad_frame_finish(&frame_);
}

mad_frame &sge::mad::frame::madframe()
{
	return frame_;
}
