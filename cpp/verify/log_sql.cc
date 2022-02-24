#include "log_sql.h"

#include <sqlite/connection.hpp>
#include <sqlite/transaction.hpp>

std::unique_ptr<sqlite::connection> conn;
std::unique_ptr<sqlite::transaction> tx;

void log_init() {
	assert(conn.get() == nullptr);
	conn.reset(new sqlite::connection("verify.db"));
	sqlite::execute(*conn.get(), "drop table if exists log_values", true);
	sqlite::execute(*conn.get(), "create table log_values (step int, name varchar, value float)", true);
	sqlite::execute(*conn.get(), "create unique index log_values_index on log_values (step, name)", true);
	insert_value.reset(new sqlite::execute(*conn.get(), "insert into log_values (step, name, value) values (?, ?, ?)"));
}

void log_start_tx() {
	tx.reset(new sqlite::transaction(*conn.get()));
}

void log_end_tx() {
	tx->commit();
	tx.reset(nullptr);
}

void log_params(
		const CARParams& car_params,
		const IHCParams& ihc_params,
		const AGCParams& agc_params) {
	log_start_tx();
	LOG_VAL(car_params.velocity_scale);
	LOG_VAL(car_params.v_offset);
	LOG_VAL(car_params.min_zeta);
	LOG_VAL(car_params.max_zeta);
	LOG_VAL(car_params.first_pole_theta);
	LOG_VAL(car_params.zero_ratio);
	LOG_VAL(car_params.high_f_damping_compression);
	LOG_VAL(car_params.erb_per_step);
	LOG_VAL(car_params.min_pole_hz);
	LOG_VAL(car_params.erb_break_freq);
	LOG_VAL(car_params.erb_q);
	LOG_VAL(ihc_params.just_half_wave_rectify);
	LOG_VAL(ihc_params.one_capacitor);
	LOG_VAL(ihc_params.tau_lpf);
	LOG_VAL(ihc_params.tau1_out);
	LOG_VAL(ihc_params.tau1_in);
	LOG_VAL(ihc_params.tau2_out);
	LOG_VAL(ihc_params.tau2_in);
	LOG_VAL(ihc_params.ac_corner_hz);
	LOG_VAL(agc_params.num_stages);
	LOG_VAL(agc_params.agc_stage_gain);
	LOG_VAL(agc_params.agc_mix_coeff);
	LOG_VALS(agc_params.time_constants);
	LOG_VALS(agc_params.decimation);
	LOG_VALS(agc_params.agc1_scales);
	LOG_VALS(agc_params.agc2_scales);
	log_end_tx();
}

void log_coeffs(const std::vector<Ear*> ears) {
	log_start_tx();
	LOG_VAL_IN_PTRARY(ears, car_coeffs_.velocity_scale);
	LOG_VAL_IN_PTRARY(ears, car_coeffs_.v_offset);
	LOG_VALS_IN_PTRARY(ears, car_coeffs_.r1_coeffs);
	LOG_VALS_IN_PTRARY(ears, car_coeffs_.a0_coeffs);
	LOG_VALS_IN_PTRARY(ears, car_coeffs_.c0_coeffs);
	LOG_VALS_IN_PTRARY(ears, car_coeffs_.h_coeffs);
	LOG_VALS_IN_PTRARY(ears, car_coeffs_.g0_coeffs);
	LOG_VALS_IN_PTRARY(ears, car_coeffs_.zr_coeffs);
	LOG_VAL_IN_PTRARY(ears, ihc_coeffs_.just_half_wave_rectify);
	LOG_VAL_IN_PTRARY(ears, ihc_coeffs_.one_capacitor);
	LOG_VAL_IN_PTRARY(ears, ihc_coeffs_.lpf_coeff);
	LOG_VAL_IN_PTRARY(ears, ihc_coeffs_.out1_rate);
	LOG_VAL_IN_PTRARY(ears, ihc_coeffs_.in1_rate);
	LOG_VAL_IN_PTRARY(ears, ihc_coeffs_.out2_rate);
	LOG_VAL_IN_PTRARY(ears, ihc_coeffs_.in2_rate);
	LOG_VAL_IN_PTRARY(ears, ihc_coeffs_.output_gain);
	LOG_VAL_IN_PTRARY(ears, ihc_coeffs_.rest_output);
	LOG_VAL_IN_PTRARY(ears, ihc_coeffs_.rest_cap1);
	LOG_VAL_IN_PTRARY(ears, ihc_coeffs_.rest_cap2);
	LOG_VAL_IN_PTRARY(ears, ihc_coeffs_.ac_coeff);
	LOG_VAL_IN_PTRARY(ears, ihc_coeffs_.cap1_voltage);
	LOG_VAL_IN_PTRARY(ears, ihc_coeffs_.cap2_voltage);
	LOG_VAL_IN_ARY_IN_PTRARY(ears, agc_coeffs_, agc_stage_gain);
	LOG_VAL_IN_ARY_IN_PTRARY(ears, agc_coeffs_, agc_epsilon);
	LOG_VAL_IN_ARY_IN_PTRARY(ears, agc_coeffs_, decimation);
	LOG_VAL_IN_ARY_IN_PTRARY(ears, agc_coeffs_, agc_pole_z1);
	LOG_VAL_IN_ARY_IN_PTRARY(ears, agc_coeffs_, agc_pole_z2);
	LOG_VAL_IN_ARY_IN_PTRARY(ears, agc_coeffs_, agc_spatial_iterations);
	LOG_VAL_IN_ARY_IN_PTRARY(ears, agc_coeffs_, agc_spatial_fir_left);
	LOG_VAL_IN_ARY_IN_PTRARY(ears, agc_coeffs_, agc_spatial_fir_mid);
	LOG_VAL_IN_ARY_IN_PTRARY(ears, agc_coeffs_, agc_spatial_fir_right);
	LOG_VAL_IN_ARY_IN_PTRARY(ears, agc_coeffs_, agc_spatial_n_taps);
	LOG_VAL_IN_ARY_IN_PTRARY(ears, agc_coeffs_, agc_mix_coeffs);
	LOG_VAL_IN_ARY_IN_PTRARY(ears, agc_coeffs_, agc_gain);
	LOG_VAL_IN_ARY_IN_PTRARY(ears, agc_coeffs_, detect_scale);
	LOG_VAL_IN_ARY_IN_PTRARY(ears, agc_coeffs_, decim);
	log_end_tx();
}

void log_state(const std::vector<Ear*> ears) {
	log_start_tx();
	LOG_VALS_IN_PTRARY(ears, car_state_.z1_memory);
	LOG_VALS_IN_PTRARY(ears, car_state_.z2_memory);
	LOG_VALS_IN_PTRARY(ears, car_state_.za_memory);
	LOG_VALS_IN_PTRARY(ears, car_state_.zb_memory);
	LOG_VALS_IN_PTRARY(ears, car_state_.dzb_memory);
	LOG_VALS_IN_PTRARY(ears, car_state_.zy_memory);
	LOG_VALS_IN_PTRARY(ears, car_state_.g_memory);
	LOG_VALS_IN_PTRARY(ears, car_state_.dg_memory);
	LOG_VALS_IN_PTRARY(ears, ihc_state_.ihc_out);
	LOG_VALS_IN_PTRARY(ears, ihc_state_.cap1_voltage);
	LOG_VALS_IN_PTRARY(ears, ihc_state_.cap2_voltage);
	LOG_VALS_IN_PTRARY(ears, ihc_state_.lpf1_state);
	LOG_VALS_IN_PTRARY(ears, ihc_state_.lpf2_state);
	LOG_VALS_IN_PTRARY(ears, ihc_state_.ac_coupler);
	LOG_VALS_IN_ARY_IN_PTRARY(ears, agc_state_, agc_memory);
	LOG_VALS_IN_ARY_IN_PTRARY(ears, agc_state_, input_accum);
	LOG_VAL_IN_ARY_IN_PTRARY(ears, agc_state_, decim_phase);
	log_end_tx();
}

