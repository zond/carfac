// Copyright 2013 The CARFAC Authors. All Rights Reserved.
// Author: Alex Brandmeyer
//
// This file is part of an implementation of Lyon's cochlear model:
// "Cascade of Asymmetric Resonators with Fast-Acting Compression"
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef CARFAC_AGC_H
#define CARFAC_AGC_H

#include <vector>

#include "common.h"

// Automatic gain control (AGC) parameters, which are used to design the AGC
// filters.
struct AGCParams {
  AGCParams() {
    num_stages = 4;
    agc_stage_gain = 2.0;
    agc1_scale0 = 1.0;
    agc1_scale_mul = sqrt(2.0);
    agc2_scale0 = 1.65;
    agc2_scale_mul = sqrt(2);
    time_constant0 = 0.002;
    time_constant_mul = 4.0;
    decimation = {8, 2, 2, 2};
    agc_mix_coeff = 0.5;
  }
  int num_stages;
  FPType agc_stage_gain;
  FPType agc_mix_coeff;
  FPType agc1_scale0;
  FPType agc1_scale_mul;
  FPType agc2_scale0;
  FPType agc2_scale_mul;
  FPType time_constant0;
  FPType time_constant_mul;
  std::vector<int> decimation;
};

// Automatic gain control filter coefficients, which are derived from a set of
// AGCParams.
struct AGCCoeffs {
  FPType agc_stage_gain;
  FPType agc_epsilon;
  int decimation;
  FPType agc_pole_z1;
  FPType agc_pole_z2;
  int agc_spatial_iterations;
  FPType agc_spatial_fir_left;
  FPType agc_spatial_fir_mid;
  FPType agc_spatial_fir_right;
  int agc_spatial_n_taps;
  FPType agc_mix_coeffs;
  FPType agc_gain;
  FPType detect_scale;
  FPType decim;
};

// Automatic gain control filter state.
struct AGCState {
  ArrayX agc_memory;
  ArrayX input_accum;
  int decim_phase;
};

#endif  // CARFAC_AGC_H
