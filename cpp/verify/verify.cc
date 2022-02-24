#include "../agc.h"
#include "../car.h"
#include "../carfac.h"
#include "../ihc.h"

#include "log_sql.h"

const float sample_rate = 48000.0;
const int channels = 1;
const int window_size = 2400;

int main() {
	log_init();

	CARParams car_params;
	IHCParams ihc_params;
	AGCParams agc_params;
	CARFAC carfac(channels, static_cast<float>(sample_rate), car_params, ihc_params, agc_params);
	CARFACOutput output(false, false, false, false);
	float impulse[window_size];
	impulse[0] = 1.0;
	carfac.RunSegment(ArrayXX::Map(impulse, 1, window_size), false, &output);

	return 0;
}
