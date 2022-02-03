#include "../agc.h"
#include "../car.h"
#include "../carfac.h"
#include "../ihc.h"
#include "../common.h"

#include "log_sql.h"

const float sample_rate = 48000.0;
const int ears = 3;
const int window_size = 2400;

int main() {
	log_init();

	CARParams car_params;
	IHCParams ihc_params;
	AGCParams agc_params;
	CARFAC carfac(ears, static_cast<float>(sample_rate), car_params, ihc_params, agc_params);
	CARFACOutput output(false, false, false, false);
	ArrayXX impulse(ears, 1024);
	impulse = 0;
	for (int ear = 0; ear < ears; ear++) {
		impulse(ear, ear) = 1.0;
	}
	carfac.RunSegment(impulse, false, &output);

	return 0;
}
