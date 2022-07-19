#include "PerssonPinefuncs.h"

class PerssonStand{
    public:
        double Latitude{0};
        double H100{0};
        double TotalAge{0};
        double BHAge{0};
        int regeneration{1};
        int Period{0};
        int StemsBeforeThinning{0};
        int StemsAfterThinning{0};
        int StemsThinned{0};
        double BABeforeThinningM2{0};
        double BAAfterThinningM2{0};
        double BAThinnedM2{0};
        double DominantHeight{0};
        double QMDBeforeThinning{0};
        double QMDAfterThinning{0};
        double QMDThinned{0};
        double VolumeBeforeThinningM3{0};
        double VolumeAfterThinningM3{0};
        double VolumeThinnedM3{0};
        double VOL_CAI{0};
        double BA_CAI{0};
        double VOL_MAI{0};
        double BA_MAI{0};
        double VOL_TOTAL{0};
        double BA_TOTAL{0};
        double MortN{0};
        double MortBA{0};
        double MortVOL{0};

        //Constructor
        PerssonStand(double bam2, int stems, int ageBh, double h100, double latitude);


}

PerssonStand::PerssonStand(double bam2, int stems, int bhAge, double h100, double latitude, regeneration = 1){
    BABeforeThinningM2 = bam2;
    StemsBeforeThinning = stems;
    BHAge = bhAge;
    H100 = h100;
    Latitude = latitude;
    Period = (int) ((200/h100)+0.5); //casting to integer, +0.5 to properly round.
    TotalAge = BHAge + HagglundTimeToBreastHeightPine(h100,);
}



int main()
{
    return 0;
}