#pragma once

#include <math.h>
#include <iostream>


//From Hagglund, B. 1974. 
//regeneration == 1 is cultured stands.
//regeneration == 2 is naturally regenerated stands.
//regeneration == 3 is for stands with unknown history.
double HagglundHeightPine(double heightm, double age, double age2, int regeneration, bool warningLoud=false)
{
    //Make sure that regeneration is one of 1, 2 or 3. Otherwise throw an error message.
    try{
        if(regeneration!=1|regeneration!=2|regeneration!=3)
    {
        throw(1);
    }

    }catch(int errorint){
        if(errorint==1) std::cout << "argument regeneration must be one of 1 , 2 or 3." << std::endl;
    }

    
    //Transform to dm and remove 1.3 m (breast height)
    double H1 = (heightm*10)-13;
    double AI1 = 10;
    double AI2 = 600;
    double RM , RM2, RK, A2, DIF, T26, T262, T13, H2;



    //throw warning if too old.
    if(warningLoud && age>120)
    {
        std::cout << "Too old stand, outside of the material." << std::endl;
    }


    while(abs(AI1-AI2)>1){

      double AI3 = (AI1+AI2)/2;
      RM = 0.066074+4.4189*pow(10,5)/pow(AI3,2.9134);
      
      if(RM>0.95)
      {
        RM = 0.95;
      }

      RM2 = 1.000/(1-RM);

      RK = 1.0002/pow(10,4)+9.5953*pow(AI3,1.3755)/pow(10,6);
      
      if(RK<0.0001)
      {
        RK = 0.0001;
      }

      A2 = 1.0075*AI3;



      DIF = H1-A2*pow((1-exp(-age*RK)),RM2);

      AI2 = (DIF<=0)?AI3:AI2;
      AI1 = (DIF>0)?AI3:AI1;


    }

    double T26 = (-1/RK)*pow(log(1-(13/A2)),(1/RM2));
    double T262 = T26*T26;

    switch(regeneration) {
        case 1:
        T13 = 7.4624+0.11672*T262-0.39276*T26;
        break;
        case 2:
        T13 = 7.4624+0.11672*T262;
        break;
        case 3:
        T13 = 6.8889+0.12405*T262;
        break;
    }

    if(T13>50){
      T13 = 50;
    }

    if(warningLoud){
        if(A2>311){
            std::cout << "Too high productivity, outside of the material." << std::endl;
        }

        if(A2<180){
            std::cout << "Too low productivity, outside of the material." << std::endl;
        }

        if(A2>250 && age>100){
            std::cout << "Too old stand, outside of the material" << std::endl;
        }
    }

    H2 = (13+A2*pow((1-exp(-age2*RK)),RM2))/10;

    return H2;

    
}

//Returns the number of years required for dominant height to reach 1.3 m.
double HagglundTimeToBreastHeightPine(double h100, int regeneration, bool warningLoud=false)
{
    //Make sure that regeneration is one of 1, 2 or 3. Otherwise throw an error message.
    try{
        if(regeneration!=1|regeneration!=2|regeneration!=3)
    {
        throw(1);
    }

    }catch(int errorint){
        if(errorint==1) std::cout << "argument regeneration must be one of 1 , 2 or 3." << std::endl;
    }

    
    //Transform to dm and remove 1.3 m (breast height)
    double H1 = (h100*10)-13;
    double AI1 = 10;
    double AI2 = 600;
    double RM , RM2, RK, A2, DIF, T26, T262, T13, H2;



    while(abs(AI1-AI2)>1){

      double AI3 = (AI1+AI2)/2;
      RM = 0.066074+4.4189*pow(10,5)/pow(AI3,2.9134);
      
      if(RM>0.95)
      {
        RM = 0.95;
      }

      RM2 = 1.000/(1-RM);

      RK = 1.0002/pow(10,4)+9.5953*pow(AI3,1.3755)/pow(10,6);
      
      if(RK<0.0001)
      {
        RK = 0.0001;
      }

      A2 = 1.0075*AI3;



      DIF = H1-A2*pow((1-exp(-100*RK)),RM2);

      AI2 = (DIF<=0)?AI3:AI2;
      AI1 = (DIF>0)?AI3:AI1;


    }

    double T26 = (-1/RK)*pow(log(1-(13/A2)),(1/RM2));
    double T262 = T26*T26;

    switch(regeneration) {
        case 1:
        T13 = 7.4624+0.11672*T262-0.39276*T26;
        break;
        case 2:
        T13 = 7.4624+0.11672*T262;
        break;
        case 3:
        T13 = 6.8889+0.12405*T262;
        break;
    }

    if(T13>50){
      T13 = 50;
    }

    return T13;

}

//Finds an estimate for the age at breast height of a tree.
double BHageFinder(double h100, int regeneration, double targetHeight){ 
    double AgeEstimate{1};
    double currentHeight{1.31}; //try 1.3 m (breast height).
    int HeightTest{1};
    
    do
        {
            try
            {
                currentHeight = HagglundHeightPine(h100,(100-HagglundTimeToBreastHeightPine(h100,regeneration,false)),AgeEstimate,regeneration,false);
                throw(1);
            }
            catch(int errorNum){
                //Nothing to be done.
            }
            
            HeightTest = (targetHeight > currentHeight)?1:0;
            AgeEstimate+=0.1;
        } while (HeightTest==1);

    return AgeEstimate-0.1;
}