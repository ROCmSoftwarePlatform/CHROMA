// $Id: inline_gfix_aggregate.cc,v 1.1 2006-02-23 20:58:00 edwards Exp $
/*! \file
 *  \brief Inline gauge fixing measurement aggregator
 */

#include "meas/inline/gfix/inline_gfix_aggregate.h"
#include "meas/inline/gfix/inline_coulgauge.h"

namespace Chroma
{

  //! Name and registration
  namespace InlineGFixAggregateEnv
  {
    bool registerAll() 
    {
      bool success = true; 
      success &= InlineCoulGaugeEnv::registered;

      return success;
    }

    const bool registered = registerAll();
  }

}
