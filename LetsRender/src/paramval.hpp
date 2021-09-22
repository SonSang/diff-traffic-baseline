#ifndef PARAMVAL_HPP
#define PARAMVAL_HPP

namespace city_sight {

class csParamVal {
public:
   float rangeMax;
   float rangeMin;

   float paramVal(float val)
   {
      float _param = ((float)(val - rangeMin)) / (rangeMax - rangeMin);
      _param = std::max(0.0f, _param);
      _param = std::min(1.0f, _param);

      return _param;
   }
};

}  // namespace city_sight

#endif
