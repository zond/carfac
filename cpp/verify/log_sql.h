#ifndef CARFAC_SQL_LOG_H
#define CARFAC_SQL_LOG_H

#include <Eigen/Core>
#include <fmt/format.h>
#include <memory>
#include <sqlite/execute.hpp>

#include "../car.h"
#include "../ihc.h"
#include "../agc.h"
#include "../ear.h"

#define LOG_VAL(valuename) log_val(#valuename, valuename)

#define LOG_VALS(valuename) \
	for (int i = 0; i < valuename.size(); i++) { \
		log_val(fmt::format(std::string(#valuename) + "[{}]", i), valuename[i]); \
	}

#define LOG_VAL_IN_PTRARY(ary, value) \
	for (int i = 0; i < ary.size(); i++) { \
		log_val(fmt::format(std::string(#ary) + "[{}]->" + std::string(#value), i), ary[i]->value); \
	}

#define LOG_VALS_IN_PTRARY(ary, value) \
	for (int i = 0; i < ary.size(); i++) { \
		for (int j = 0; j < ary[i]->value.size(); j++) { \
			log_val(fmt::format(std::string(#ary) + "[{}]->" + std::string(#value) + "[{}]", i, j), ary[i]->value[j]); \
		} \
	}

#define LOG_VAL_IN_ARY_IN_PTRARY(ary, inner_ary, value) \
	for (int i = 0; i < ary.size(); i++) { \
		for (int j = 0; j < ary[i]->inner_ary.size(); j++) { \
			log_val(fmt::format(std::string(#ary) + "[{}]->" + std::string(#inner_ary) + "[{}]." + std::string(#value), i, j), ary[i]->inner_ary[j].value); \
		} \
	}

#define LOG_VALS_IN_ARY_IN_PTRARY(ary, inner_ary, value) \
	for (int i = 0; i < ary.size(); i++) { \
		for (int j = 0; j < ary[i]->inner_ary.size(); j++) { \
			for (int k = 0; k < ary[i]->inner_ary[j].value.size(); k++) { \
					log_val(fmt::format(std::string(#ary) + "[{}]->" + std::string(#inner_ary) + "[{}]." + std::string(#value) + "[{}]", i, j, k), ary[i]->inner_ary[j].value[k]); \
			} \
		} \
	}

extern std::unique_ptr<sqlite::execute> insert_value;
extern int log_sql_step;
extern int log_sql_ear;
extern bool log_sql_enabled;

void log_init();

void log_start_tx();

void log_end_tx();

template<typename T>
void log_val(const std::string& name, const T value) {
	if (log_sql_enabled) {
		insert_value->clear();
		(*insert_value.get() % log_sql_step % log_sql_ear % name % static_cast<float>(value))();
	}
}

template<typename T>
void log_vals_in_ary(const std::string& name, const T ary) {
	for (int i = 0; i < ary.size(); i++) {
		log_val(fmt::format(name + "[{}]", i), ary[i]);
	}
}

void log_params(
		const CARParams& car_params, 
		const IHCParams& ihc_params,
		const AGCParams& agc_params);

void log_coeffs(const std::vector<Ear*> ears);


void log_state(const std::vector<Ear*> ears);

#endif
