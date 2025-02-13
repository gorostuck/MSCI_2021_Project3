//
//    TransTessellate2D : A general Trans-dimensional Tessellation program
//    for 2D Cartesian problems.
//
//    Copyright (C) 2014 - 2019 Rhys Hawkins
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//

#pragma once
#ifndef ptexchange_hpp
#define ptexchange_hpp

#include "global.hpp"
#include <mpi.h>

class PTExchange {
public:

  PTExchange(global &state);
  ~PTExchange();

  int step(double &current_likelihood,
	   double &current_log_normalization);

  std::string write_short_stats();

  std::string write_long_stats();

  void initialize_mpi(MPI_Comm global_communicator,
		      MPI_Comm temperature_communicator,
		      MPI_Comm chain_communicator,
		      int ntemperatures);

  global &state;

  int propose;
  int accept;

  MPI_Comm global_communicator;
  int global_size;
  int global_rank;
  
  MPI_Comm temperature_communicator;
  int temperature_size;
  int temperature_rank;
  
  MPI_Comm chain_communicator;
  int chain_rank;

private:

  int ntotalchains;
  int processesperchain;
  int ntemperatures;
  int chainspertemperature;

  int *ptpairs;
  int *transposed_ptpairs;
  
  int partner;
  bool send;
  bool ptaccept;
  int send_length;
  int recv_length;
	
  double sendmsg[5];
  double recvmsg[5];
  
  double current_logprior;
  double partner_logprior;
  
  double partner_likelihood;
  double partner_log_normalization;
  double partner_temperature;
  double u;
  MPI_Status status;

  int exchanged;

  int send_buffer_size;
  char *send_buffer;

  int recv_buffer_size;
  char *recv_buffer;
  
  
};

#endif // ptexchange_hpp
