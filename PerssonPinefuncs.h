#pragma once

#include "HagglundHeightPine.h"

double PineBAI( 
  double basal_area_after_thinning,
  double age_at_breast_height,
  double h100,
  double latitude
){

    return exp(
            +4.90697+
            +0.44683*log(basal_area_after_thinning)+
            -0.63272*log(age_at_breast_height)+
            +0.30834*log(h100)+
            -1.32323*log(latitude)
            );

}

double PineBAaverage(
  double h100,
  double dominantHeight
){
  return exp(
      -0.150317+ //including correction for logarithmic bias.
      +0.50463*log(dominantHeight)+
      +0.62033*log(h100)
    );
}

double bark_Pine(
  double basal_area_above_bark,
  double h100,
  int stems,
  double latitude
){
  return exp(
    8.43648+ //including correction for logarithmic bias.
    +0.94902*log(basal_area_above_bark)+
    -0.176223*log(h100)+
    +0.037108*log(stems)+
    -2.30456*log(latitude)
    );
}


double PineMortalityDiameterQuotient(
  double dominantHeight,
  int stems,
  bool thinned
){
  return exp(
      -1.06123+
      +0.38727*log(dominantHeight)+
      -0.080630*log(stems)+
      +0.140766*thinned
    );
}

double PineMortalityBAyr(
  double BAM2,
  double dominantHeight,
  double h100,
  int stems,
  double latitude
){

double BAMort{0};
double avgBA = PineBAaverage(h100,dominantHeight)*1.3;

  if(BAM2>=avgBA){
    BAMort = exp(
             -17.24908+ //including correction for logarithmic bias.
               +1.86053*log(BAM2)+
               +1.75182*log(dominantHeight)+
               +0.44001*log(stems)
           );
  } else {
    BAMort = exp(
             +15.3390+
             +1.01872*log(dominantHeight)+
             +0.69317*log(stems)+
             -6.38718*log(latitude)
           );
  }

  return BAMort;

}


double PineVolume(
  double BAM2,
  double dominantHeight,
  int stems,
  double latitude
){
  return exp(
    -0.58147+ //including correction for logarithmic bias.
      +1.11493*log(BAM2)+
      +0.73376*log(dominantHeight)+
      -0.072569*log(stems)+
      +0.160919*log(latitude)
    );
}