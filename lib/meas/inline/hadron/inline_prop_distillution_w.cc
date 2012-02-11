/*! \file
 * \brief Compute the propagator from distillution
 *
 * Propagator calculation in distillution
 */

#include "fermact.h"
#include "meas/inline/hadron/inline_prop_distillution_w.h"
#include "meas/inline/abs_inline_measurement_factory.h"
#include "meas/glue/mesplq.h"
#include "util/ferm/distillution_noise.h"
#include "util/ferm/key_timeslice_colorvec.h"
#include "qdp_map_obj_disk.h"
#include "qdp_disk_map_slice.h"
#include "util/ferm/key_prop_distillution.h"
#include "util/ferm/transf.h"
#include "util/ferm/spin_rep.h"
#include "util/ferm/diractodr.h"
#include "util/ferm/twoquark_contract_ops.h"
#include "util/ft/time_slice_set.h"
#include "util/info/proginfo.h"
#include "actions/ferm/fermacts/fermact_factory_w.h"
#include "actions/ferm/fermacts/fermacts_aggregate_w.h"
#include "meas/inline/make_xml_file.h"

#include "meas/inline/io/named_objmap.h"

namespace Chroma 
{ 
  namespace InlinePropDistillutionEnv 
  {
    //! Propagator input
    void read(XMLReader& xml, const string& path, Params::NamedObject_t& input)
    {
      XMLReader inputtop(xml, path);

      read(inputtop, "gauge_id", input.gauge_id);
      read(inputtop, "distillution_id", input.distillution_id);
      read(inputtop, "colorvec_file", input.colorvec_file);
      read(inputtop, "prop_file", input.prop_file);
    }

    //! Propagator output
    void write(XMLWriter& xml, const string& path, const Params::NamedObject_t& input)
    {
      push(xml, path);

      write(xml, "gauge_id", input.gauge_id);
      write(xml, "distillution_id", input.distillution_id);
      write(xml, "colorvec_file", input.colorvec_file);
      write(xml, "prop_file", input.prop_file);

      pop(xml);
    }


    //! Propagator input
    void read(XMLReader& xml, const string& path, Params::Param_t::Contract_t& input)
    {
      XMLReader inputtop(xml, path);

      read(inputtop, "num_vecs", input.num_vecs);
      read(inputtop, "num_vec_dils", input.num_vec_dils);
      read(inputtop, "t_sources", input.t_sources);
      read(inputtop, "Nt_forward", input.Nt_forward);
      read(inputtop, "Nt_backward", input.Nt_backward);
      read(inputtop, "quark_line", input.quark_line);
      read(inputtop, "mass", input.mass);
    }

    //! Propagator output
    void write(XMLWriter& xml, const string& path, const Params::Param_t::Contract_t& input)
    {
      push(xml, path);

      write(xml, "num_vecs", input.num_vecs);
      write(xml, "num_vec_dils", input.num_vec_dils);
      write(xml, "t_sources", input.t_sources);
      write(xml, "Nt_forward", input.Nt_forward);
      write(xml, "Nt_backward", input.Nt_backward);
      write(xml, "quark_line", input.quark_line);
      write(xml, "mass", input.mass);

      pop(xml);
    }


    //! Propagator input
    void read(XMLReader& xml, const string& path, Params::Param_t& input)
    {
      XMLReader inputtop(xml, path);

      read(inputtop, "Propagator", input.prop);
      read(inputtop, "Contractions", input.contract);
    }

    //! Propagator output
    void write(XMLWriter& xml, const string& path, const Params::Param_t& input)
    {
      push(xml, path);

      write(xml, "Propagator", input.prop);
      write(xml, "Contractions", input.contract);

      pop(xml);
    }


    //! Propagator input
    void read(XMLReader& xml, const string& path, Params& input)
    {
      Params tmp(xml, path);
      input = tmp;
    }

    //! Propagator output
    void write(XMLWriter& xml, const string& path, const Params& input)
    {
      push(xml, path);
    
      write(xml, "Param", input.param);
      write(xml, "NamedObject", input.named_obj);

      pop(xml);
    }
  } // namespace InlinePropDistillutionEnv 


  namespace InlinePropDistillutionEnv 
  {
    namespace
    {
      AbsInlineMeasurement* createMeasurement(XMLReader& xml_in, 
					      const std::string& path) 
      {
	return new InlineMeas(Params(xml_in, path));
      }

      //! Local registration flag
      bool registered = false;
    }
      
    const std::string name = "PROP_DISTILLUTION";

    //! Register all the factories
    bool registerAll() 
    {
      bool success = true; 
      if (! registered)
      {
	success &= WilsonTypeFermActsEnv::registerAll();
	success &= TheInlineMeasurementFactory::Instance().registerObject(name, createMeasurement);
	registered = true;
      }
      return success;
    }


    //----------------------------------------------------------------------------
    // Param stuff
    Params::Params() { frequency = 0; }

    Params::Params(XMLReader& xml_in, const std::string& path) 
    {
      try 
      {
	XMLReader paramtop(xml_in, path);

	if (paramtop.count("Frequency") == 1)
	  read(paramtop, "Frequency", frequency);
	else
	  frequency = 1;

	// Parameters for source construction
	read(paramtop, "Param", param);

	// Read in the output propagator/source configuration info
	read(paramtop, "NamedObject", named_obj);

	// Possible alternate XML file pattern
	if (paramtop.count("xml_file") != 0) 
	{
	  read(paramtop, "xml_file", xml_file);
	}
      }
      catch(const std::string& e) 
      {
	QDPIO::cerr << __func__ << ": Caught Exception reading XML: " << e << endl;
	QDP_abort(1);
      }
    }



    // Function call
    void 
    InlineMeas::operator()(unsigned long update_no,
			   XMLWriter& xml_out) 
    {
      // If xml file not empty, then use alternate
      if (params.xml_file != "")
      {
	string xml_file = makeXMLFileName(params.xml_file, update_no);

	push(xml_out, "PropDistillution");
	write(xml_out, "update_no", update_no);
	write(xml_out, "xml_file", xml_file);
	pop(xml_out);

	XMLFileWriter xml(xml_file);
	func(update_no, xml);
      }
      else
      {
	func(update_no, xml_out);
      }
    }


    // Real work done here
    void 
    InlineMeas::func(unsigned long update_no,
		     XMLWriter& xml_out) 
    {
      START_CODE();

      StopWatch snoop;
      snoop.reset();
      snoop.start();

      // Test and grab a reference to the gauge field
      multi1d<LatticeColorMatrix> u;
      XMLBufferWriter gauge_xml;
      try
      {
	u = TheNamedObjMap::Instance().getData< multi1d<LatticeColorMatrix> >(params.named_obj.gauge_id);
	TheNamedObjMap::Instance().get(params.named_obj.gauge_id).getRecordXML(gauge_xml);
      }
      catch( std::bad_cast ) 
      {
	QDPIO::cerr << name << ": caught dynamic cast error" << endl;
	QDP_abort(1);
      }
      catch (const string& e) 
      {
	QDPIO::cerr << name << ": map call failed: " << e << endl;
	QDP_abort(1);
      }

      push(xml_out, "PropDistillution");
      write(xml_out, "update_no", update_no);

      QDPIO::cout << name << ": propagator calculation" << endl;

      proginfo(xml_out);    // Print out basic program info

      // Write out the input
      write(xml_out, "Input", params);

      // Write out the config header
      write(xml_out, "Config_info", gauge_xml);

      push(xml_out, "Output_version");
      write(xml_out, "out_version", 1);
      pop(xml_out);

      // Calculate some gauge invariant observables just for info.
      MesPlq(xml_out, "Observables", u);

      //
      // Read in the source along with relevant information.
      // 
      QDPIO::cout << "Snarf the distillution factory from a named buffer" << endl;
      try
      {
	TheNamedObjMap::Instance().getData< Handle< DistillutionNoise > >(params.named_obj.distillution_id);
      }    
      catch (std::bad_cast) {
	QDPIO::cerr << name << ": caught dynamic cast error" << endl;
	QDP_abort(1);
      }
      catch (const string& e) {
	QDPIO::cerr << name << ": error extracting source_header: " << e << endl;
	QDP_abort(1);
      }
      catch( const char* e) {
	QDPIO::cerr << name <<": Caught some char* exception:" << endl;
	QDPIO::cerr << e << endl;
	QDPIO::cerr << "Rethrowing" << endl;
	throw;
      }

      // Cast should be valid now
      const DistillutionNoise& dist_noise_obj =
	*(TheNamedObjMap::Instance().getData< Handle<DistillutionNoise> >(params.named_obj.distillution_id));

      // Some diagnostics
      QDPIO::cout << "Distillution factory: ensemble= XX" << dist_noise_obj.getEnsemble() << "XX  "
		  << "sequence= XX" << dist_noise_obj.getSequence() << "XX\n"
		  << "t_origin= " << dist_noise_obj.getOrigin() << "\n";


      // Will use TimeSliceSet-s a lot
      const int decay_dir = dist_noise_obj.getDecayDir();
      const int Lt        = Layout::lattSize()[decay_dir];

      // A sanity check
      if (decay_dir != Nd-1)
      {
	QDPIO::cerr << __func__ << ": TimeSliceIO only supports decay_dir= " << Nd-1 << "\n";
	QDP_abort(1);
      }

      // The time-slice set
      TimeSliceSet time_slice_set(decay_dir);


      //
      // Read in the source along with relevant information.
      // 
      QDPIO::cout << "Snarf the source from a map object disk file" << endl;

      QDP::MapObjectDisk<KeyTimeSliceColorVec_t,TimeSliceIO<LatticeColorVector> > eigen_source;
      eigen_source.setDebug(1);

      try
      {
	// Open
	QDPIO::cout << "Open file= " << params.named_obj.colorvec_file << endl;
//	eigen_source.open(params.named_obj.colorvec_file, std::ios_base::in);
	eigen_source.open(params.named_obj.colorvec_file);

	// Snarf the source info. 
	string user_str;
	QDPIO::cout << "Get user data" << endl;
	eigen_source.getUserdata(user_str);
	QDPIO::cout << "User data= " << user_str << endl;

	// Write it
	QDPIO::cout << "Write to an xml file" << endl;
	XMLBufferWriter xml_buf(user_str);
	write(xml_out, "Source_info", xml_buf);
      }    
      catch (std::bad_cast) {
	QDPIO::cerr << name << ": caught dynamic cast error" << endl;
	QDP_abort(1);
      }
      catch (const string& e) {
	QDPIO::cerr << name << ": error extracting source_header: " << e << endl;
	QDP_abort(1);
      }
      catch( const char* e) {
	QDPIO::cerr << name <<": Caught some char* exception:" << endl;
	QDPIO::cerr << e << endl;
	QDPIO::cerr << "Rethrowing" << endl;
	throw;
      }

      QDPIO::cout << "Set source mod file to read" << endl;

      QDPIO::cout << "Source successfully read and parsed" << endl;


      // Sanity check - write out the norm2 of the source in the decay_dir direction
      // Use this for any possible verification
      {
	QDPIO::cout << "Lookup source 0" << endl;
	LatticeColorVector tmpvec;

	for(int t=0; t < Lt; ++t)
	{
	  KeyTimeSliceColorVec_t key_vec;
	  key_vec.t_slice = t;
	  key_vec.colorvec = 0;

	  TimeSliceIO<LatticeColorVector> time_slice_io(tmpvec, t);
	  eigen_source.get(key_vec, time_slice_io);
	}

	multi1d<Double> source_corrs = sumMulti(localNorm2(tmpvec), time_slice_set.getSet());

	push(xml_out, "Source_correlators");
	write(xml_out, "source_corrs", source_corrs);
	pop(xml_out);
      }

      QDPIO::cout << "Source studied: do some other sanity checks" << endl;

      // Another sanity check
      if (params.param.contract.num_vecs > eigen_source.size())
      {
	QDPIO::cerr << __func__ << ": num_vecs= " << params.param.contract.num_vecs
		    << " is greater than the number of available colorvectors= "
		    << eigen_source.size() << endl;
	QDP_abort(1);
      }

      // Another sanity check
      if ((params.param.contract.num_vecs % params.param.contract.num_vec_dils) != 0)
      {
	QDPIO::cerr << __func__ << ": num_vecs= " << params.param.contract.num_vecs
		    << " is not a multiple of number of dilutions = "
		    << params.param.contract.num_vec_dils << endl;
	QDP_abort(1);
      }


      //
      // DB storage
      //
      // Open the file, and write the meta-data and the binary for this operator
      //
      QDP::MapObjectDisk<KeyPropDist_t, TimeSliceIO<LatticeColorVector> > prop_obj;
//      prop_obj.setDebug(1);

      if (! prop_obj.fileExists(params.named_obj.prop_file))
      {
	XMLBufferWriter file_xml;

	push(file_xml, "MODMetaData");
	write(file_xml, "id", string("propDist"));
	write(file_xml, "lattSize", QDP::Layout::lattSize());
	write(file_xml, "decay_dir", decay_dir);
	write(file_xml, "num_vecs", params.param.contract.num_vecs);
	write(file_xml, "num_vec_dils", params.param.contract.num_vec_dils);
	write(file_xml, "ensemble", dist_noise_obj.getEnsemble());
	write(file_xml, "sequence", dist_noise_obj.getSequence());
	write(file_xml, "t_origin", dist_noise_obj.getOrigin());
	write(file_xml, "quark_line", params.param.contract.quark_line);
	proginfo(file_xml);    // Print out basic program info
	write(file_xml, "Params", params.param);
	write(file_xml, "Config_info", gauge_xml);
	pop(file_xml);

	std::string file_str(file_xml.str());

	prop_obj.insertUserdata(file_xml.str());
	prop_obj.open(params.named_obj.prop_file, std::ios_base::in | std::ios_base::out | std::ios_base::trunc);
      }
      else
      {
	prop_obj.open(params.named_obj.prop_file);
      }


      //
      // The noise for this quark line.
      // NOTE: the noise is fixed for a type of source, but given for all time-slices
      // 
      // FIX ME: for the moment, hardwired for only single-ended sources
      multi2d<Complex> eta;
      {
	DistQuarkLines_t info;
	info.num_vecs   = params.param.contract.num_vecs;
	info.quark_line = params.param.contract.quark_line;
	info.annih      = false;

	eta = dist_noise_obj.getRNG(info);

	for(int i=0; i < eta.size1(); ++i)
	  for(int j=0; j < eta.size2(); ++j)
	  {
	    if (i == j)
	      eta(i,j) = 1.0;
	    else
	      eta(i,j) = zero;

	    QDPIO::cout << name << ": line= " << info.quark_line << "  eta("<<i<<","<<j<<")= "<< eta(i,j) << std::endl;
	  }
      }


      // Total number of iterations
      int ncg_had = 0;


      // Rotation from DR to DP
      SpinMatrix diracToDRMat(DiracToDRMat());
      std::vector<MatrixSpinRep_t> diracToDrMatPlus = convertTwoQuarkSpin(diracToDRMat);
      std::vector<MatrixSpinRep_t> diracToDrMatMinus = convertTwoQuarkSpin(adj(diracToDRMat));


      //
      // Try the factories
      //
      try
      {
	StopWatch swatch;
	swatch.reset();
	QDPIO::cout << "Try the various factories" << endl;

	// Typedefs to save typing
	typedef LatticeFermion               T;
	typedef multi1d<LatticeColorMatrix>  P;
	typedef multi1d<LatticeColorMatrix>  Q;

	//
	// Initialize fermion action
	//
	std::istringstream  xml_s(params.param.prop.fermact.xml);
	XMLReader  fermacttop(xml_s);
	QDPIO::cout << "FermAct = " << params.param.prop.fermact.id << endl;

	// Generic Wilson-Type stuff
	Handle< FermionAction<T,P,Q> >
	  S_f(TheFermionActionFactory::Instance().createObject(params.param.prop.fermact.id,
							       fermacttop,
							       params.param.prop.fermact.path));

	Handle< FermState<T,P,Q> > state(S_f->createState(u));

	Handle< SystemSolver<LatticeFermion> > PP = S_f->qprop(state,
							       params.param.prop.invParam);
      
	QDPIO::cout << "Suitable factory found: compute all the quark props" << endl;
	swatch.start();

	//
	// Loop over the source color and spin, creating the source
	// and calling the relevant propagator routines.
	//
	const int num_vecs            = params.param.contract.num_vecs;
	const int num_vec_dils        = params.param.contract.num_vec_dils;
	const multi1d<int>& t_sources = params.param.contract.t_sources;


	// Loop over each time-source
	for(int tt=0; tt < t_sources.size(); ++tt)
	{
	  int t_source = t_sources[tt];  // This is the pretend time-slice. The actual value is shifted.
	  QDPIO::cout << "t_source = " << t_source << endl; 

	  // Find the active time-slices to save
	  std::vector<bool> active_t_slices(Lt);
	  for(int t=0; t < Lt; ++t)
	  {
	    active_t_slices[t] = false;
	  }

	  // Forward
	  for(int dt=0; dt < params.param.contract.Nt_forward; ++dt)
	  {
	    int t = t_source + dt;
	    active_t_slices[t % Lt] = true;
	  }

	  // Backward
	  for(int dt=0; dt < params.param.contract.Nt_backward; ++dt)
	  {
	    int t = t_source - dt;
	    while (t < 0) {t += Lt;} 

	    active_t_slices[t % Lt] = true;
	  }


	  // All the loops
	  for(int dist_src=0; dist_src < num_vec_dils; ++dist_src)
	  {
	    QDPIO::cout << "dist_src = " << dist_src << endl; 

	    // Prepare a distilluted source
	    // Pull out a time-slice of the color vector source, and add it in a crystal fashion
	    // with other vectors
	    LatticeColorVector vec_srce = zero;

	    for(int colorvec_source=dist_src; colorvec_source < num_vecs; colorvec_source += num_vec_dils)
	    {
	      QDPIO::cout << "colorvec_source = " << colorvec_source << endl;

	      // Get the actual time slice
	      int t_actual = dist_noise_obj.getTime(t_source);

	      KeyTimeSliceColorVec_t key_vec;
	      key_vec.t_slice = t_actual;
	      key_vec.colorvec = colorvec_source;

	      LatticeColorVector tmpvec = zero;
	      TimeSliceIO<LatticeColorVector> time_slice_io(tmpvec, t_actual);

	      eigen_source.get(key_vec, time_slice_io);

//	      vec_srce[time_slice_set.getSet()[t_actual]] += eta(t_source, colorvec_source) * tmpvec;
	      vec_srce[time_slice_set.getSet()[t_actual]] += tmpvec;
	    }
	
	    // Insert this source
	    {
	      KeyPropDist_t key;

	      key.prop_type    = "SRC";
	      key.t_source     = t_source;
	      key.t_slice      = t_source;
	      key.dist_src     = dist_src;
	      key.spin_src     = -1;
	      key.spin_snk     = -1;
	      key.quark_line   = params.param.contract.quark_line;
	      key.mass         = params.param.contract.mass;

	      prop_obj.insert(key, TimeSliceIO<LatticeColorVector>(vec_srce, dist_noise_obj.getTime(t_source)));
	    }


	    //
	    // Loop over each spin source and invert. 
	    // Use the same colorvector source. No spin dilution will be used.
	    //
	    multi2d<LatticeColorVector> ferm_out(Ns,Ns);

	    for(int spin_source=0; spin_source < Ns; ++spin_source)
	    {
	      QDPIO::cout << "spin_source = " << spin_source << endl; 

	      // Insert a ColorVector into spin index spin_source
	      // This only overwrites sections, so need to initialize first
	      LatticeFermion chi = zero;
	      CvToFerm(vec_srce, chi, spin_source);

	      LatticeFermion quark_soln = zero;

	      // Do the propagator inversion
	      SystemSolverResults_t res = (*PP)(quark_soln, chi);
	      ncg_had = res.n_count;

	      // Extract into the temporary output array
	      for(int spin_sink=0; spin_sink < Ns; ++spin_sink)
	      {
		ferm_out(spin_sink,spin_source) = peekSpin(quark_soln, spin_sink);
	      }
	    } // for spin_source


	    // Rotate from DeGrand-Rossi (DR) to Dirac-Pauli (DP)
	    {
	      multi2d<LatticeColorVector> ferm_tmp;

	      multiplyRep(ferm_tmp, diracToDrMatMinus, ferm_out);
	      multiplyRep(ferm_out, ferm_tmp, diracToDrMatPlus);
	    }


	    // Write out each time-slice chunk of a lattice colorvec soln to disk
	    for(int spin_source=0; spin_source < Ns; ++spin_source)
	    {
	      for(int spin_sink=0; spin_sink < Ns; ++spin_sink)
	      {
		for(int t=0; t < Lt; ++t)
		{
		  if (! active_t_slices[t]) {continue;}

		  KeyPropDist_t key;

		  key.prop_type    = "SNK";
		  key.t_source     = t_source;
		  key.t_slice      = t;
		  key.dist_src     = dist_src;
		  key.spin_src     = spin_source;
		  key.spin_snk     = spin_sink;
		  key.quark_line   = params.param.contract.quark_line;
		  key.mass         = params.param.contract.mass;

		  prop_obj.insert(key, TimeSliceIO<LatticeColorVector>(ferm_out(spin_sink,spin_source), 
								       dist_noise_obj.getTime(t)));

		} // for t
	      } // for spin_sink
	    } // for spin_source
	  } // for dist_source
	} // for tt

	prop_obj.flush();
	swatch.stop();
	QDPIO::cout << "Propagators computed: time= " 
		    << swatch.getTimeInSeconds() 
		    << " secs" << endl;
      }
      catch (const std::string& e) 
      {
	QDPIO::cout << name << ": caught exception around qprop: " << e << endl;
	QDP_abort(1);
      }

      push(xml_out,"Relaxation_Iterations");
      write(xml_out, "ncg_had", ncg_had);
      pop(xml_out);

      pop(xml_out);  // prop_dist

      snoop.stop();
      QDPIO::cout << name << ": total time = "
		  << snoop.getTimeInSeconds() 
		  << " secs" << endl;

      QDPIO::cout << name << ": ran successfully" << endl;

      END_CODE();
    } 

  }

} // namespace Chroma
