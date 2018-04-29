#ifndef SNTKURSACH_AKIMASPLINE_H
#define SNTKURSACH_AKIMASPLINE_H

#include "CubicSpline.h"

class AkimaSpline : public CubicSpline{
    public:
        AkimaSpline(); //конструктор
        ~AkimaSpline() override;
        AkimaSpline(double *x, double *y, int n);
        explicit AkimaSpline(char* f);

        void buildSpline(double *x, double *y, int cnt) override;
};


#endif //SNTKURSACH_AKIMASPLINE_H
