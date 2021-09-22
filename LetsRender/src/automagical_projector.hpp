// This is a projector class specifically for bing map related data.
#ifndef AUTOMAGICAL_PROJECTOR_HPP
#define AUTOMAGICAL_PROJECTOR_HPP

namespace city_sight {

class csAutomagicalProjector {
public:
   static double cleanProjectLat(double latitude) {
      double sinLatitude = sin(latitude * kPi / 180);
      double y = 0.5 - log((1 + sinLatitude) / (1 - sinLatitude)) / (4 * kPi);

      // Magic bing maps scaling.
      y *= 2097152;

      return y / 100.0;
   }

   static double cleanProjectLon(double longitude)
   {
      double x = (longitude + 180) / 360;

      x *= 2097152;

      return x / 100.0;
   }

   static double biasedProjectLat(double latitude)
   {
      // Negative is 'down'
      // Positive is 'up'
      latitude -= 0.0012f;

      double sinLatitude = sin((latitude * kPi) / 180);
      double y = 0.5 - log((1 + sinLatitude) / (1 - sinLatitude)) / (4 * kPi);

      // Magic bing maps scaling.
      y *= 2097152;

      return y / 100.0;
   }

   static double biasedProjectLon(double longitude)
   {
      // Negative is 'left'
      // Positive is 'right'
      longitude -= 0.0065f;

      double x = (longitude + 180) / 360;

      x *= 2097152;

      return x / 100.0;
   }
};

}  // namespace city_sight

#endif
