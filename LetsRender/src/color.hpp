#ifndef COLOR_HPP
#define COLOR_HPP

namespace city_sight {

class csColor {
public:
   // States are 0 = RGB, 1 = HSL, 2 = HSV.
   // TODO Make private.
   int colorState;

   float R;
   float G;
   float B;

   float H;
   float S;
   float L;
   float V;

   float A;

   csColor() {
      colorState = 0;

      R = 1;
      G = 0;
      B = 0;

      H = 0;
      S = 0;
      L = 0;
      V = 0;

      A = 1.0f;
   }

   int getState()
   {
      return colorState;
   }

   void setState(int colorState_)
   {
      colorState = colorState_;
   }

   void setHSL(float H_, float S_, float L_)
   {
      H = H_;
      S = S_;
      L = L_;

      setState(1);
      calcRGB();
   }

   void setHSV(float H_, float S_, float V_)
   {
      H = H_;
      S = S_;
      V = V_;

      setState(2);
      calcRGB();
   }

   void calcRGB()
   {
      if (getState() == 1)
      {
         calcHSLtoRGB();
      }
      else if (getState() == 2)
      {
         calcHSVtoRGB();
      }
   }

   void calcHSLtoRGB()
   {
      float H_prime = H / 60.0f;

      float C = 0.0f;
      if ((S != 0.0f) && (L != 0.0f))
      {
         C = S * (1 - abs(2 * L - 1));
      }

      float M = (C + 2 * L) / 2;
      float m = 2 * L - M;

      // Red case.
      if (((H >= 0.0f) && (H <= 60.0f)) || ((H < 0.0f) && (H > -60.0f)))
      {
         R = M;
         if (H > 0.0f) // Blue is least.
         {
            B = m;
            G = (H_prime * C) + B;
         }
         else // Green is least.
         {
            G = m;
            B = -1.0f * ((H_prime * C) - G);
         }

      }
      else if ((H > 60.0f) && (H <= 180.0f)) // Green case.
      {
         G = M;
         if (H > 120.0f) // Red is least.
         {
            R = m;
            B = (H_prime - 2) * C + R;
         }
         else // Blue is least.
         {
            B = m;
            R = -1.0f * ((H_prime - 2) * C - B);
         }
      }
      else // Blue case.
      {
         B = M;
         if (H > 240) // Green is least.
         {
            G = m;
            R = (H_prime - 4) * C + G;
         }
         else // Red is least.
         {
            R = m;
            G = -1.0f * ((H_prime - 4) * C - R);
         }
      }
   }

   void calcHSVtoRGB()
   {
      float H_prime = H / 60.0f;

      float C = 0.0f;
      if (S != 0.0f)
      {
         C = S * V;
      }

      float M = V;
      float m = -1 * (C - M);

      // Red case.
      if (((H >= 0.0f) && (H <= 60.0f)) || ((H < 0.0f) && (H > -60.0f)))
      {
         R = M;
         if (H > 0.0f) // Blue is least.
         {
            B = m;
            G = (H_prime * C) + B;
         }
         else // Green is least.
         {
            G = m;
            B = -1.0f * ((H_prime * C) - G);
         }

      }
      else if ((H > 60.0f) && (H <= 180.0f)) // Green case.
      {
         G = M;
         if (H > 120.0f) // Red is least.
         {
            R = m;
            B = (H_prime - 2) * C + R;
         }
         else // Blue is least.
         {
            B = m;
            R = -1.0f * ((H_prime - 2) * C - B);
         }
      }
      else // Blue case.
      {
         B = M;
         if (H > 240) // Green is least.
         {
            G = m;
            R = (H_prime - 4) * C + G;
         }
         else // Red is least.
         {
            R = m;
            G = -1.0f * ((H_prime - 4) * C - R);
         }
      }
   }
};

}  // namespace city_sight

#endif
