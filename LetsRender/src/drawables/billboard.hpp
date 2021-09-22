#ifndef BILLBOARD_HPP
#define BILLBOARD_HPP

namespace city_sight {

class csBillboard {
private:
   string filename_ = "Data/level13.png";
   int wParts = 1;
   int hParts = 1;
   vector<csSurface> surfaces;

   float world_size = 8;

public:

   void set_filename(string filename) {
      filename_ = filename;
   }

   string get_filename() {
      return filename_;
   }

   // Assigns a 2D position (on the xy plane) for the billboard and sets the
   // size of the billboard.
   void SetCenterAndDimensions(Vector2 center, float x_length, float y_length) {
      // TODO Hacky translation added.
      float trans_x = 950;
      float trans_y = 800;

      // TODO Hacky aspect ration = 1.0 fix.
      x_length = std::max(x_length, y_length);
      y_length = x_length;

      // TODO Hacky scaling.
      x_length *= 1.1;
      y_length *= 1.1;

      for (int i = 0; i < surfaces.size(); i++) {

         csSurface& surface = surfaces[i];

         surface.myGeometry.Clear();

         // Updates the geometry of the billboard.
         surface.myGeometry.setTexCoord(Vector2(0, 1));
         surface.myGeometry.addVertex(Vector3(center.x - (x_length * 0.5) + trans_x,
                                              center.y - (y_length * 0.5) + trans_y,
                                              0.0f));

         surface.myGeometry.setTexCoord(Vector2(0, 0));
         surface.myGeometry.addVertex(Vector3(center.x - (x_length * 0.5) + trans_x,
                                              center.y + (y_length * 0.5) + trans_y,
                                              0.0f));

         surface.myGeometry.setTexCoord(Vector2(1, 0));
         surface.myGeometry.addVertex(Vector3(center.x + (x_length * 0.5) + trans_x,
                                              center.y + (y_length * 0.5) + trans_y,
                                              0.0f));

         surface.myGeometry.setTexCoord(Vector2(1, 1));
         surface.myGeometry.addVertex(Vector3(center.x + (x_length * 0.5) + trans_x,
                                              center.y - (y_length * 0.5) + trans_y,
                                              0.0f));

         surface.myGeometry.addQuad(0, 1, 2, 3);

         // Update the surface with the new geometry.
         surfaces[i].update();
      }
   }

   void init() {
      Magick::Image image;
      image.read(filename_);

      for (int i = 0; i < wParts; i++)
      {
         for (int j = 0; j < hParts ; j++)
         {
            csSurface thisPart;

            int width = image.columns() / wParts;
            int height = image.rows() / hParts;

            int x = i * width;
            int y = j * height;

            thisPart.material.initTexture(image);

            // TODO This needs to be fixed for multi-part billboards.
            // Vector2 sizeVec = Vector2(world_size / wParts, world_size / hParts);
            // float xf = (x / (float) image.columns()) * world_size;
            // float yf = (y / (float) image.rows()) * world_size;

            // Sizes are 1/100 of image resolution.
            // Vector2 sizeVec = Vector2(23.98f / wParts, 25.82f / hParts);
            // float xf = (x / (float) image.columns()) * 23.98f;
            // float yf = (y / (float) image.rows()) * 25.82f;
            float off_x = 1080;
            float off_y = 1450;

            float size = 4000;
            Vector2 sizeVec = Vector2(size / wParts, size / hParts);
            float xf = -size; //(x / (float) image.columns()) * 20.0f;
            float yf = -size; //(y / (float) image.rows()) * 20.0f;

            thisPart.myGeometry.setTexCoord(Vector2(0, 1));
            thisPart.myGeometry.addVertex(Vector3(xf + off_x,
                                                  yf + off_y,
                                                  0.0f));

            thisPart.myGeometry.setTexCoord(Vector2(0, 0));
            thisPart.myGeometry.addVertex(Vector3(xf + off_x,
                                                  2*sizeVec.y + yf + off_y,
                                                  0.0f));

            thisPart.myGeometry.setTexCoord(Vector2(1, 0));
            thisPart.myGeometry.addVertex(Vector3(2*sizeVec.x + xf + off_x,
                                                  2*sizeVec.y + yf + off_y,
                                                  0.0f));

            thisPart.myGeometry.setTexCoord(Vector2(1, 1));
            thisPart.myGeometry.addVertex(Vector3(2*sizeVec.x + xf + off_x,
                                                  yf + off_y,
                                                  0.0f));

            thisPart.myGeometry.addQuad(0, 1, 2, 3);

            thisPart.init();

            surfaces.push_back(thisPart);
         }
      }
   }

   void draw()
   {
      for (csSurface& s : surfaces)
      {
         std::cout << "Drawing map\n";
         s.draw();
      }
   }
};

}  // namespace city_sight

#endif
