#include "global.h"

inline double addT(double &newT);
inline double delT(double oldT);
inline double shiftT(double oldT, double &newT);

inline double addK(mom &newK);
inline double delK(const mom &oldK);
inline double shiftK(const mom &oldK, mom &newK);

inline double addIdx(int &);
inline double delIdx();
inline double shiftIdx(int &oldIdx, int &newIdx);