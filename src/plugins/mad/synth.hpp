#ifndef SGE_MAD_SYNTH_HPP_INCLUDED
#define SGE_MAD_SYNTH_HPP_INCLUDED

#include <mad.h>
#include <sge/audio/sample_count.hpp>
#include <boost/cstdint.hpp>
#include <utility>
#include <vector>

namespace sge
{
namespace mad
{
class frame;

class synth
{
	public:
	typedef boost::int16_t sample_type;
	typedef std::pair<sample_type,sample_type> channel_pair;
	typedef std::vector<channel_pair> synthed_sample_container;
	typedef synthed_sample_container::const_iterator const_iterator;

	explicit synth(frame &);
	const_iterator begin() const { return synthed_samples.begin(); }
	const_iterator end() const { return synthed_samples.end(); }
	void synthesize();
	audio::sample_count sample_count() const;
	~synth();

	private:
	mad_synth synth_;
	frame &f;
	synthed_sample_container synthed_samples;
};
}
}

#endif
