#include "tsp_control.h"

namespace tsp
{
   Control::Control()
   {
      this->mPopulation.setLocations( &this->mLocations );
   }
}
