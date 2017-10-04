// -*- C++ -*-
/*! \file
 *  \QUDA MULTIGRID Clover solver.
 */

#ifndef __syssolver_linop_quda_multigrid_clover_h__
#define __syssolver_linop_quda_multigrid_clover_h__

#include "chroma_config.h"

#ifdef BUILD_QUDA
#include <quda.h>

#include "handle.h"
#include "state.h"
#include "syssolver.h"
#include "linearop.h"
#include "actions/ferm/fermbcs/simple_fermbc.h"
#include "actions/ferm/fermstates/periodic_fermstate.h"
#include "actions/ferm/invert/quda_solvers/syssolver_quda_multigrid_clover_params.h"
#include "actions/ferm/linop/clover_term_w.h"
#include "meas/gfix/temporal_gauge.h"
#include "io/aniso_io.h"
#include <string>

#include "util/gauge/reunit.h"
#ifdef QDP_IS_QDPJIT
#include "actions/ferm/invert/quda_solvers/qdpjit_memory_wrapper.h"
#endif

//#include <util_quda.h>

namespace Chroma
{

	//! Richardson system solver namespace
	namespace LinOpSysSolverQUDAMULTIGRIDCloverEnv
	{
		//! Register the syssolver
		bool registerAll();
	}

	//! Solve a Clover Fermion System using the QUDA inverter
	/*! \ingroup invert
	 *** WARNING THIS SOLVER WORKS FOR Clover FERMIONS ONLY ***
	 */

	class LinOpSysSolverQUDAMULTIGRIDClover : public LinOpSystemSolver<LatticeFermion>
	{
	public:
		typedef LatticeFermion T;
		typedef LatticeColorMatrix U;
		typedef multi1d<LatticeColorMatrix> Q;

		typedef LatticeFermionF TF;
		typedef LatticeColorMatrixF UF;
		typedef multi1d<LatticeColorMatrixF> QF;

		typedef LatticeFermionF TD;
		typedef LatticeColorMatrixF UD;
		typedef multi1d<LatticeColorMatrixF> QD;

		typedef WordType<T>::Type_t REALT;
		//! Constructor
		/*!
		 * \param M_        Linear operator ( Read )
		 * \param invParam  inverter parameters ( Read )
		 */
		LinOpSysSolverQUDAMULTIGRIDClover(Handle< LinearOperator<T> > A_,
				Handle< FermState<T,Q,Q> > state_,
				const SysSolverQUDAMULTIGRIDCloverParams& invParam_) :
		A(A_), invParam(invParam_), clov(new CloverTermT<T, U>() ), invclov(new CloverTermT<T, U>())
		{
		  StopWatch init_swatch;
		  init_swatch.reset(); init_swatch.start();
		   // Set the solver string
		    {
		      ostringstream solver_string_stream;
		      solver_string_stream << "QUDA_MULTIGRID_CLOVER_LINOP_SOLVER( "
		          << invParam.SaveSubspaceID << " ): ";
		      solver_string = solver_string_stream.str();

		    }
		    QDPIO::cout << solver_string << "Initializing" << std::endl;

			// FOLLOWING INITIALIZATION in test QUDA program

			// 1) work out cpu_prec, cuda_prec, cuda_prec_sloppy
			int s = sizeof( WordType<T>::Type_t );
			if (s == 4) {
				cpu_prec = QUDA_SINGLE_PRECISION;
			}
			else {
				cpu_prec = QUDA_DOUBLE_PRECISION;
			}

			// Work out GPU precision
			switch( invParam.cudaPrecision ) {
				case HALF:
				gpu_prec = QUDA_HALF_PRECISION;
				break;
				case SINGLE:
				gpu_prec = QUDA_SINGLE_PRECISION;
				break;
				case DOUBLE:
				gpu_prec = QUDA_DOUBLE_PRECISION;
				break;
				default:
				gpu_prec = cpu_prec;
				break;
			}

			// Work out GPU Sloppy precision
			// Default: No Sloppy
			switch( invParam.cudaSloppyPrecision ) {
				case HALF:
				gpu_half_prec = QUDA_HALF_PRECISION;
				break;
				case SINGLE:
				gpu_half_prec = QUDA_SINGLE_PRECISION;
				break;
				case DOUBLE:
				gpu_half_prec = QUDA_DOUBLE_PRECISION;
				break;
				default:
				gpu_half_prec = gpu_prec;
				break;
			}

			// 2) pull 'new; GAUGE and Invert params
			q_gauge_param = newQudaGaugeParam();
			quda_inv_param = newQudaInvertParam();
			mg_inv_param = newQudaInvertParam();
			mg_param = newQudaMultigridParam();

			// 3) set lattice size
			const multi1d<int>& latdims = Layout::subgridLattSize();

			q_gauge_param.X[0] = latdims[0];
			q_gauge_param.X[1] = latdims[1];
			q_gauge_param.X[2] = latdims[2];
			q_gauge_param.X[3] = latdims[3];

			// 4) - deferred (anisotropy)

			// 5) - set QUDA_WILSON_LINKS, QUDA_GAUGE_ORDER
			q_gauge_param.type = QUDA_WILSON_LINKS;
#ifndef BUILD_QUDA_DEVIFACE_GAUGE
			q_gauge_param.gauge_order = QUDA_QDP_GAUGE_ORDER; // gauge[mu], p
#else
			q_gauge_param.location = QUDA_CUDA_FIELD_LOCATION;
			q_gauge_param.gauge_order = QUDA_QDPJIT_GAUGE_ORDER;
#endif

			// 6) - set t_boundary
			// Convention: BC has to be applied already
			// This flag just tells QUDA that this is so,
			// so that QUDA can take care in the reconstruct
			if( invParam.AntiPeriodicT ) {
				q_gauge_param.t_boundary = QUDA_ANTI_PERIODIC_T;
			}
			else {
				q_gauge_param.t_boundary = QUDA_PERIODIC_T;
			}

			// Set cpu_prec, cuda_prec, reconstruct and sloppy versions
			q_gauge_param.cpu_prec = cpu_prec;
			q_gauge_param.cuda_prec = gpu_prec;

			switch( invParam.cudaReconstruct ) {
				case RECONS_NONE:
				q_gauge_param.reconstruct = QUDA_RECONSTRUCT_NO;
				break;
				case RECONS_8:
				q_gauge_param.reconstruct = QUDA_RECONSTRUCT_8;
				break;
				case RECONS_12:
				q_gauge_param.reconstruct = QUDA_RECONSTRUCT_12;
				break;
				default:
				q_gauge_param.reconstruct = QUDA_RECONSTRUCT_12;
				break;
			};

			q_gauge_param.cuda_prec_sloppy = gpu_half_prec;

			switch( invParam.cudaSloppyReconstruct ) {
				case RECONS_NONE:
				q_gauge_param.reconstruct_sloppy = QUDA_RECONSTRUCT_NO;
				break;
				case RECONS_8:
				q_gauge_param.reconstruct_sloppy = QUDA_RECONSTRUCT_8;
				break;
				case RECONS_12:
				q_gauge_param.reconstruct_sloppy = QUDA_RECONSTRUCT_12;
				break;
				default:
				q_gauge_param.reconstruct_sloppy = QUDA_RECONSTRUCT_12;
				break;
			};

			// Gauge fixing:

			// These are the links
			// They may be smeared and the BC's may be applied
			Q links_single(Nd);

			// Now downcast to single prec fields.
			for(int mu=0; mu < Nd; mu++) {
				links_single[mu] = (state_->getLinks())[mu];
			}

			// GaugeFix
			if( invParam.axialGaugeP ) {
				temporalGauge(links_single, GFixMat, Nd-1);
				for(int mu=0; mu < Nd; mu++) {
					links_single[mu] = GFixMat*(state_->getLinks())[mu]*adj(shift(GFixMat, FORWARD, mu));
				}
				q_gauge_param.gauge_fix = QUDA_GAUGE_FIXED_YES;
			}
			else {
				// No GaugeFix
				q_gauge_param.gauge_fix = QUDA_GAUGE_FIXED_NO;// No Gfix yet
			}

			// deferred 4) Gauge Anisotropy
			const AnisoParam_t& aniso = invParam.CloverParams.anisoParam;
			if( aniso.anisoP ) {                     // Anisotropic case
				Real gamma_f = aniso.xi_0 / aniso.nu;
				q_gauge_param.anisotropy = toDouble(gamma_f);
			}
			else {
				q_gauge_param.anisotropy = 1.0;
			}

			// MAKE FSTATE BEFORE RESCALING links_single
			// Because the clover term expects the unrescaled links...
			Handle<FermState<T,Q,Q> > fstate( new PeriodicFermState<T,Q,Q>(links_single));

			if( aniso.anisoP ) {                     // Anisotropic case
				multi1d<Real> cf=makeFermCoeffs(aniso);
				for(int mu=0; mu < Nd; mu++) {
					links_single[mu] *= cf[mu];
				}
			}

			// Now onto the inv param:
			// Dslash type
			quda_inv_param.dslash_type = QUDA_CLOVER_WILSON_DSLASH;
			mg_inv_param.dslash_type = QUDA_CLOVER_WILSON_DSLASH;

			// Hardwire to GCR
			quda_inv_param.inv_type = QUDA_GCR_INVERTER;


			//Params added for now to get this to initialize.
			mg_inv_param.inv_type = QUDA_GCR_INVERTER;
			mg_inv_param.tol = 1e-10;
			mg_inv_param.maxiter = 10000;
			mg_inv_param.reliable_delta = 1e-10;

			quda_inv_param.kappa = 0.5;
			quda_inv_param.clover_coeff = 1.0; // Dummy, not used
			quda_inv_param.Ls = 1;

			quda_inv_param.tol = toDouble(invParam.RsdTarget);
			quda_inv_param.maxiter = invParam.MaxIter;
			quda_inv_param.reliable_delta = toDouble(invParam.Delta);

			// Solution type
			//quda_inv_param.solution_type = QUDA_MATPC_SOLUTION;
			//Taken from invert test.
			quda_inv_param.solution_type = QUDA_MATPC_SOLUTION;
			quda_inv_param.solve_type = QUDA_DIRECT_PC_SOLVE;

			// Solve type
			/*switch( invParam.solverType ) {
			 case CG:
			 quda_inv_param.solve_type = QUDA_NORMOP_PC_SOLVE;
			 break;
			 case BICGSTAB:
			 quda_inv_param.solve_type = QUDA_DIRECT_PC_SOLVE;
			 break;
			 case GCR:
			 quda_inv_param.solve_type = QUDA_DIRECT_PC_SOLVE;
			 break;

			 case MR:
			 quda_inv_param.solve_type = QUDA_DIRECT_PC_SOLVE;
			 break;

			 default:
			 quda_inv_param.solve_type = QUDA_NORMOP_PC_SOLVE;

			 break;
			 }*/

			quda_inv_param.matpc_type = QUDA_MATPC_ODD_ODD;

			quda_inv_param.dagger = QUDA_DAG_NO;
			quda_inv_param.mass_normalization = QUDA_KAPPA_NORMALIZATION;

			quda_inv_param.cpu_prec = cpu_prec;
			quda_inv_param.cuda_prec = gpu_prec;
			quda_inv_param.cuda_prec_sloppy = gpu_half_prec;
			//Add some lines for mg_inv_param.
			mg_inv_param.cpu_prec = cpu_prec;
			mg_inv_param.cuda_prec = gpu_prec;
			mg_inv_param.cuda_prec_sloppy = gpu_half_prec;
			//Clover stuff
			mg_inv_param.clover_cpu_prec = cpu_prec;
			mg_inv_param.clover_cuda_prec = gpu_prec;
			mg_inv_param.clover_cuda_prec_precondition = gpu_prec;
			mg_inv_param.clover_cuda_prec_sloppy = gpu_half_prec;
			mg_inv_param.clover_order = QUDA_PACKED_CLOVER_ORDER;
			//
			//Done...
			quda_inv_param.preserve_source = QUDA_PRESERVE_SOURCE_NO;
			quda_inv_param.gamma_basis = QUDA_DEGRAND_ROSSI_GAMMA_BASIS;

#ifndef BUILD_QUDA_DEVIFACE_SPINOR
			quda_inv_param.dirac_order = QUDA_DIRAC_ORDER;
			quda_inv_param.input_location = QUDA_CPU_FIELD_LOCATION;
			quda_inv_param.output_location = QUDA_CPU_FIELD_LOCATION;

#else
			quda_inv_param.dirac_order = QUDA_QDPJIT_DIRAC_ORDER;
			quda_inv_param.input_location = QUDA_CUDA_FIELD_LOCATION;
			quda_inv_param.output_location = QUDA_CUDA_FIELD_LOCATION;
#endif

			// Autotuning
			if( invParam.tuneDslashP ) {
				quda_inv_param.tune = QUDA_TUNE_YES;
				mg_inv_param.tune = QUDA_TUNE_YES;
			}
			else {
				quda_inv_param.tune = QUDA_TUNE_NO;
				mg_inv_param.tune = QUDA_TUNE_NO;
			}

			// Setup padding

			multi1d<int> face_size(4);
			face_size[0] = latdims[1]*latdims[2]*latdims[3]/2;
			face_size[1] = latdims[0]*latdims[2]*latdims[3]/2;
			face_size[2] = latdims[0]*latdims[1]*latdims[3]/2;
			face_size[3] = latdims[0]*latdims[1]*latdims[2]/2;

			int max_face = face_size[0];
			for(int i=1; i <=3; i++) {
				if ( face_size[i] > max_face ) {
					max_face = face_size[i];
				}
			}

			q_gauge_param.ga_pad = max_face;
			// PADDING
			quda_inv_param.sp_pad = 0;
			quda_inv_param.cl_pad = 0;

			// Clover precision and order
			quda_inv_param.clover_cpu_prec = cpu_prec;
			quda_inv_param.clover_cuda_prec = gpu_prec;
			quda_inv_param.clover_cuda_prec_sloppy = gpu_half_prec;

			if( invParam.MULTIGRIDParamsP ) {
				MULTIGRIDSolverParams ip = *(invParam.MULTIGRIDParams);

				// Set preconditioner precision
				switch( ip.prec ) {
					case HALF:
					mg_inv_param.cuda_prec_precondition = QUDA_HALF_PRECISION;
					quda_inv_param.cuda_prec_precondition = QUDA_HALF_PRECISION;
					mg_inv_param.clover_cuda_prec_precondition = QUDA_HALF_PRECISION;
					quda_inv_param.clover_cuda_prec_precondition = QUDA_HALF_PRECISION;
					q_gauge_param.cuda_prec_precondition = QUDA_HALF_PRECISION;
					break;

					case SINGLE:
					mg_inv_param.cuda_prec_precondition = QUDA_SINGLE_PRECISION;
					mg_inv_param.clover_cuda_prec_precondition = QUDA_SINGLE_PRECISION;
					quda_inv_param.cuda_prec_precondition = QUDA_SINGLE_PRECISION;
					quda_inv_param.clover_cuda_prec_precondition = QUDA_SINGLE_PRECISION;
					q_gauge_param.cuda_prec_precondition = QUDA_SINGLE_PRECISION;
					break;

					case DOUBLE:
					mg_inv_param.cuda_prec_precondition = QUDA_DOUBLE_PRECISION;
					mg_inv_param.clover_cuda_prec_precondition = QUDA_DOUBLE_PRECISION;
					quda_inv_param.cuda_prec_precondition = QUDA_DOUBLE_PRECISION;
					quda_inv_param.clover_cuda_prec_precondition = QUDA_DOUBLE_PRECISION;
					q_gauge_param.cuda_prec_precondition = QUDA_DOUBLE_PRECISION;
					break;
					default:
					mg_inv_param.cuda_prec_precondition = QUDA_HALF_PRECISION;
					mg_inv_param.clover_cuda_prec_precondition = QUDA_HALF_PRECISION;
					quda_inv_param.cuda_prec_precondition = QUDA_HALF_PRECISION;
					quda_inv_param.clover_cuda_prec_precondition = QUDA_HALF_PRECISION;
					q_gauge_param.cuda_prec_precondition = QUDA_HALF_PRECISION;
					break;
				}

				switch( ip.reconstruct ) {
					case RECONS_NONE:
					q_gauge_param.reconstruct_precondition = QUDA_RECONSTRUCT_NO;
					break;
					case RECONS_8:
					q_gauge_param.reconstruct_precondition = QUDA_RECONSTRUCT_8;
					break;
					case RECONS_12:
					q_gauge_param.reconstruct_precondition = QUDA_RECONSTRUCT_12;
					break;
					default:
					q_gauge_param.reconstruct_precondition = QUDA_RECONSTRUCT_12;
					break;
				};
			}
			// Set up the links
			void* gauge[4];

			for(int mu=0; mu < Nd; mu++) {
#ifndef BUILD_QUDA_DEVIFACE_GAUGE
				gauge[mu] = (void *)&(links_single[mu].elem(all.start()).elem().elem(0,0).real());
#else
				gauge[mu] = GetMemoryPtr( links_single[mu].getId() );
#endif
			}

			loadGaugeQuda((void *)gauge, &q_gauge_param);

			MULTIGRIDSolverParams ip = *(invParam.MULTIGRIDParams);
			//
			quda_inv_param.tol_precondition = toDouble(ip.tol);
			quda_inv_param.maxiter_precondition = ip.maxIterations;
			quda_inv_param.gcrNkrylov = ip.outer_gcr_nkrylov;
			mg_inv_param.gcrNkrylov = ip.precond_gcr_nkrylov; 
			quda_inv_param.residual_type = static_cast<QudaResidualType>(QUDA_L2_RELATIVE_RESIDUAL);

			if( ip.verbosity == true ) {
				mg_inv_param.verbosity = QUDA_VERBOSE;
			}
			else {
				mg_inv_param.verbosity = QUDA_SUMMARIZE;
			}
			mg_inv_param.verbosity_precondition = QUDA_SILENT;


			//Replacing above with what's in the invert test.
			switch( ip.schwarzType ) {
				case ADDITIVE_SCHWARZ :
				quda_inv_param.schwarz_type = QUDA_ADDITIVE_SCHWARZ;
				break;
				case MULTIPLICATIVE_SCHWARZ :
				quda_inv_param.schwarz_type = QUDA_MULTIPLICATIVE_SCHWARZ;
				break;
				default:
				quda_inv_param.schwarz_type = QUDA_ADDITIVE_SCHWARZ;
				break;
			}
			quda_inv_param.precondition_cycle = 1;
			//Invert test always sets this to 1.


			if( invParam.verboseP ) {
				quda_inv_param.verbosity = QUDA_VERBOSE;
			}
			else {
				quda_inv_param.verbosity = QUDA_SUMMARIZE;
			}

			quda_inv_param.verbosity_precondition = QUDA_SILENT;

			quda_inv_param.inv_type_precondition = QUDA_MG_INVERTER;

			mg_inv_param.sp_pad = 0;
			mg_inv_param.cl_pad = 0;

			//mg_inv_param.cpu_prec = cpu_prec;
			//mg_inv_param.cuda_prec = cuda_prec;
			//mg_inv_param.cuda_prec_sloppy = cuda_prec_sloppy;
			//mg_inv_param.cuda_prec_precondition = cuda_prec_precondition;
			mg_inv_param.preserve_source = QUDA_PRESERVE_SOURCE_NO;
			mg_inv_param.gamma_basis = QUDA_DEGRAND_ROSSI_GAMMA_BASIS;
			mg_inv_param.dirac_order = QUDA_DIRAC_ORDER;


			mg_inv_param.input_location = QUDA_CPU_FIELD_LOCATION;
			mg_inv_param.output_location = QUDA_CPU_FIELD_LOCATION;

			mg_inv_param.kappa = quda_inv_param.kappa;

			mg_inv_param.dagger = QUDA_DAG_NO;
		//	mg_inv_param.mass = -3.0; // Not for aniso
			mg_inv_param.kappa = 0.5;
			mg_inv_param.mass_normalization = QUDA_KAPPA_NORMALIZATION;
			mg_inv_param.clover_coeff = 1.0;
			mg_inv_param.matpc_type = QUDA_MATPC_ODD_ODD;
			mg_inv_param.solution_type = QUDA_MAT_SOLUTION;
			mg_inv_param.solve_type = QUDA_DIRECT_SOLVE;

			//mg_param.invert_param = &quda_inv_param;
			mg_param.invert_param = &mg_inv_param;

			mg_inv_param.Ls = 1;

			mg_param.n_level = ip.mg_levels;

			if( ip.check_multigrid_setup ) {
			  mg_param.run_verify = QUDA_BOOLEAN_YES;
			}
			else {
			  mg_param.run_verify = QUDA_BOOLEAN_NO;
			}
			for (int i=0; i<mg_param.n_level; i++) {
			  for (int j=0; j<QUDA_MAX_DIM; j++) {
			    if( i < mg_param.n_level-1 ) {
			      mg_param.geo_block_size[i][j] = ip.blocking[i][j];
			    }
			    else {
			      mg_param.geo_block_size[i][j] = 4;
			    }
			  }
			  mg_param.spin_block_size[i] = 1;
				

			  if ( i < mg_param.n_level-1) { 
			    mg_param.n_vec[i] = ip.nvec[i];
			    mg_param.nu_pre[i] = ip.nu_pre[i];
			    mg_param.nu_post[i] = ip.nu_post[i];
			  }
			  mg_param.smoother_tol[i] = toDouble(ip.tol);

			  
			  mg_param.mu_factor[i] = 1.0; // default in quda test program

			  // Hardwire setup solver now.
			  mg_param.setup_inv_type[i] = QUDA_BICGSTAB_INVERTER;
			  mg_param.setup_tol[i] = 5.0e-6;
			  mg_param.num_setup_iter[i] = 1; // 1 refine for now.. like before
			  mg_param.precision_null[i] = mg_inv_param.cuda_prec_precondition; 

			  // Hardwire Coarse solver now
			  mg_param.coarse_solver[i] = QUDA_GCR_INVERTER;
			  mg_param.coarse_solver_tol[i] = toDouble(ip.tol);
			  mg_param.coarse_solver_maxiter[i] = ip.maxIterations;

			  switch( ip.smootherType ) {
			  case MR:
			    mg_param.smoother[i] = QUDA_MR_INVERTER;
			    mg_param.smoother_tol[i] = 0.25;
			    mg_param.smoother_solve_type[i] = QUDA_DIRECT_PC_SOLVE;
			    mg_param.omega[i] = toDouble(ip.relaxationOmegaMG);
			    mg_param.smoother_schwarz_type[i] = QUDA_INVALID_SCHWARZ;
			    mg_param.smoother_schwarz_cycle[i] = 1;
			    break;
			  default:
			    QDPIO::cout << solver_string << "Unknown or no smother type specified, no smoothing inverter will be used." << std::endl;
			    mg_param.smoother[i] = QUDA_INVALID_INVERTER;
			    QDP_abort(1);
			    break;
			  }
	
			  mg_param.global_reduction[i] =  (mg_param.smoother_schwarz_type[i] == QUDA_INVALID_SCHWARZ) ? QUDA_BOOLEAN_YES : QUDA_BOOLEAN_NO;		
			  mg_param.location[i] = QUDA_CUDA_FIELD_LOCATION;
			  
			  if ( ip.cycle_type == "MG_VCYCLE" ) {
			    mg_param.cycle_type[i] = QUDA_MG_CYCLE_VCYCLE;
			  } else if (ip.cycle_type == "MG_RECURSIVE" ) { 
			    mg_param.cycle_type[i] = QUDA_MG_CYCLE_RECURSIVE;
			  } else {
			    QDPIO::cout << solver_string << "Unknown Cycle Type" << ip.cycle_type << std::endl;
			    QDP_abort(1);
			  }
			  
			  switch( mg_param.cycle_type[i] ) { 
			  case QUDA_MG_CYCLE_RECURSIVE : 
			    mg_param.coarse_grid_solution_type[i] = QUDA_MATPC_SOLUTION;	
			    break;
			  case QUDA_MG_CYCLE_VCYCLE :
			    mg_param.coarse_grid_solution_type[i] = QUDA_MAT_SOLUTION; 
			    break;
			  default:
			    QDPIO::cerr << solver_string << "Should never get here" << std::endl;
			    QDP_abort(1);
			    break;
			  }
			}

			mg_param.setup_type = QUDA_NULL_VECTOR_SETUP;
			mg_param.pre_orthonormalize = QUDA_BOOLEAN_NO;
			mg_param.post_orthonormalize = QUDA_BOOLEAN_YES;

     			// LEvel 0 must always be matpc 
			mg_param.coarse_grid_solution_type[0] = QUDA_MATPC_SOLUTION;

			// only coarsen the spin on the first restriction
			mg_param.spin_block_size[0] = 2;

			// coarse grid solver is GCR
			mg_param.smoother[ip.mg_levels-1] = QUDA_GCR_INVERTER;

			mg_param.compute_null_vector = ip.generate_nullspace ? QUDA_COMPUTE_NULL_VECTOR_YES
			: QUDA_COMPUTE_NULL_VECTOR_NO;

			mg_param.generate_all_levels = ip.generate_all_levels ? QUDA_BOOLEAN_YES 
                        : QUDA_BOOLEAN_NO;

			// set file i/o parameters
			//strcpy(mg_param.vec_infile, vec_infile);
			//strcpy(mg_param.vec_outfile, vec_outfile);
			//Ignoring this for now.

			mg_param.vec_infile[0] = '\0';
			mg_param.vec_outfile[0] = '\0';

			QDPIO::cout<< solver_string << "Basic MULTIGRID params copied."<<std::endl;

			//      Setup the clover term...
			QDPIO::cout << solver_string << "Creating CloverTerm" << std::endl;
			clov->create(fstate, invParam_.CloverParams);

			// Don't recompute, just copy
			invclov->create(fstate, invParam_.CloverParams);

			QDPIO::cout << solver_string << "Inverting CloverTerm" << std::endl;
			invclov->choles(0);
			invclov->choles(1);

#ifndef BUILD_QUDA_DEVIFACE_CLOVER
#warning "NOT USING QUDA DEVICE IFACE"
			quda_inv_param.clover_order = QUDA_PACKED_CLOVER_ORDER;

			multi1d<QUDAPackedClovSite<REALT> > packed_clov;

			// Only compute clover if we're using asymmetric preconditioner
			if( invParam.asymmetricP ) {
				packed_clov.resize(all.siteTable().size());

				clov->packForQUDA(packed_clov, 0);
				clov->packForQUDA(packed_clov, 1);
			}

			// Always need inverse
			multi1d<QUDAPackedClovSite<REALT> > packed_invclov(all.siteTable().size());
			invclov->packForQUDA(packed_invclov, 0);
			invclov->packForQUDA(packed_invclov, 1);

			if( invParam.asymmetricP ) {
				loadCloverQuda(&(packed_clov[0]), &(packed_invclov[0]), &quda_inv_param);

			}
			else {
				loadCloverQuda(&(packed_clov[0]), &(packed_invclov[0]), &quda_inv_param);
			}
#else

#warning "USING QUDA DEVICE IFACE"
			quda_inv_param.clover_location = QUDA_CUDA_FIELD_LOCATION;
			quda_inv_param.clover_order = QUDA_QDPJIT_CLOVER_ORDER;

			void *clover[2];
			void *cloverInv[2];

			clover[0] = GetMemoryPtr( clov->getOffId() );
			clover[1] = GetMemoryPtr( clov->getDiaId() );

			cloverInv[0] = GetMemoryPtr( invclov->getOffId() );
			cloverInv[1] = GetMemoryPtr( invclov->getDiaId() );


			if( invParam.asymmetricP ) {
				loadCloverQuda( (void*)(clover), (void *)(cloverInv), &quda_inv_param);
			}
			else {
				loadCloverQuda( (void*)(clover), (void *)(cloverInv), &quda_inv_param);
			}
#endif

			quda_inv_param.omega = toDouble(ip.relaxationOmegaOuter);

			// setup the multigrid solver
			void *mg_preconditioner = newMultigridQuda(&mg_param);
			quda_inv_param.preconditioner = mg_preconditioner;

#if 0
			// This is purely for debug diagnostics.
			QDPIO::cout << solver_string <<"MULTIGrid Param Dump" << std::endl;
			printQudaMultigridParam(&mg_param);
#endif

			init_swatch.stop();
			QDPIO::cout << solver_string << "init_time = "
			            << init_swatch.getTimeInSeconds() << " sec. " << std::endl;

		}

		//! Destructor is automatic
		~LinOpSysSolverQUDAMULTIGRIDClover()
		{
			QDPIO::cout << solver_string << "Destructing" << std::endl;
			freeGaugeQuda();
			freeCloverQuda();
			destroyMultigridQuda(quda_inv_param.preconditioner);
		}

		//! Return the subset on which the operator acts
		const Subset& subset() const {return A->subset();}

		//! Solver the linear system
		/*!
		 * \param psi      solution ( Modify )
		 * \param chi      source ( Read )
		 * \return syssolver results
		 */
		SystemSolverResults_t operator() (T& psi, const T& chi) const
		{
			SystemSolverResults_t res;

			START_CODE();
			StopWatch swatch;
			swatch.start();

			psi = zero; // Zero initial guess
			//    T MdagChi;

			// This is a CGNE. So create new RHS
			//      (*A)(MdagChi, chi, MINUS);
			// Handle< LinearOperator<T> > MM(new MdagMLinOp<T>(A));
			if ( invParam.axialGaugeP ) {
				T g_chi,g_psi;

				// Gauge Fix source and initial guess
				g_chi[ rb[1] ] = GFixMat * chi;
				g_psi[ rb[1] ] = GFixMat * psi;
				res = qudaInvert(*clov,
						*invclov,
						g_chi,
						g_psi);
				psi[ rb[1]] = adj(GFixMat)*g_psi;

			}
			else {
				res = qudaInvert(*clov,
						*invclov,
						chi,
						psi);
			}

			swatch.stop();
			double time = swatch.getTimeInSeconds();

			{
				T r;
				r[A->subset()]=chi;
				T tmp;
				(*A)(tmp, psi, PLUS);
				r[A->subset()] -= tmp;
				res.resid = sqrt(norm2(r, A->subset()));
			}

			Double rel_resid = res.resid/sqrt(norm2(chi,A->subset()));

			QDPIO::cout << solver_string  << res.n_count << " iterations. Rsd = " << res.resid << " Relative Rsd = " << rel_resid << std::endl;

			// Convergence Check/Blow Up
			if ( ! invParam.SilentFailP ) {
				if ( toBool( rel_resid > invParam.RsdToleranceFactor*invParam.RsdTarget) ) {
					QDPIO::cerr << solver_string << "ERROR:   Solver residuum is outside tolerance: QUDA resid="<< rel_resid << " Desired =" << invParam.RsdTarget << " Max Tolerated = " << invParam.RsdToleranceFactor*invParam.RsdTarget << std::endl;
					QDP_abort(1);
				}
			}

			END_CODE();
			return res;
		}

	private:
		// Hide default constructor
		LinOpSysSolverQUDAMULTIGRIDClover() {}

#if 1
		Q links_orig;
#endif

		U GFixMat;
		QudaPrecision_s cpu_prec;
		QudaPrecision_s gpu_prec;
		QudaPrecision_s gpu_half_prec;

		Handle< LinearOperator<T> > A;
		const SysSolverQUDAMULTIGRIDCloverParams invParam;
		QudaGaugeParam q_gauge_param;
		QudaInvertParam quda_inv_param;
		QudaInvertParam mg_inv_param;
		QudaMultigridParam mg_param;

		Handle< CloverTermT<T, U> > clov;
		Handle< CloverTermT<T, U> > invclov;

		SystemSolverResults_t qudaInvert(const CloverTermT<T, U>& clover,
				const CloverTermT<T, U>& inv_clov,
				const T& chi_s,
				T& psi_s
		)const;

		std::string solver_string;
	};

} // End namespace

#endif // BUILD_QUDA
#endif 
