// $Id: simple_gaugestate.cc,v 1.1 2006-09-19 18:21:38 edwards Exp $
/*! \file
 *  \brief Simple gauge state and a creator
 */

#include "actions/gauge/gaugestates/simple_gaugestate.h"
#include "actions/gauge/gaugestates/gauge_createstate_factory.h"
#include "actions/gauge/gaugestates/gauge_createstate_aggregate.h"
#include "actions/gauge/gaugebcs/gaugebc_aggregate.h"

namespace Chroma
{
 
  namespace CreateSimpleGaugeStateEnv 
  { 
    CreateGaugeState<multi1d<LatticeColorMatrix>, 
		     multi1d<LatticeColorMatrix> >* createCreator(XMLReader& xml, 
								  const std::string& path) 
    {
      return new CreateSimpleGaugeState<multi1d<LatticeColorMatrix>, 
	                                multi1d<LatticeColorMatrix> >(GaugeTypeGaugeBCEnv::reader(xml, 
												  path));
    }

    const std::string name = "SIMPLE_GAUGE_STATE";
    const bool registered = TheCreateGaugeStateFactory::Instance().registerObject(name, 
										  createCreator);
  }

}

