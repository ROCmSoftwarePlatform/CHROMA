// -*- C++ -*-
// $Id: hyp_smear.h,v 1.2 2003-10-10 03:46:47 edwards Exp $

#ifndef __hyp_smear_h__
#define __hyp_smear_h__

//! Construct the "hyp-smeared" links of Anna Hasenfratz, with
//! staple coefficients alpha1, alpha2 and alpha3

/*!
 * Arguments:
 *
 *  \param u		gauge field (Read)
 *  \param u_hyp	"hyp-smeared" gauge field (Write)
 *  \param alpha1	staple coefficient "1" (Read)
 *  \param alpha2	staple coefficient "2" (Read)
 *  \param alpha3	staple coefficient "3" (Read)
 *  \param BlkAccu	accuracy in SU(Nc) projection (Read)
 *  \param BlkMax	max number of iterations in SU(Nc) projection (Read)
 */

void Hyp_Smear(const multi1d<LatticeColorMatrix>& u,
	       multi1d<LatticeColorMatrix>& u_hyp,
	       const Real& alpha1, const Real& alpha2, const Real& alpha3,
	       const Real& BlkAccu, int BlkMax);

#endif
