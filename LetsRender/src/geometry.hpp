#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

namespace city_sight {

struct ptVertex {
   Vector2 texCoord;
   Vector3 position;
};

class csGeometry {
public:
   enum mode { Points = 0, Tris, Quads, Lines};

   uint numVertices;
   uint maxVertices;
   vector<ptVertex> vertices;

   uint numIndices;
   uint maxIndices;
   vector<uint> indices;

   mode drawMode;

   csGeometry()
   {
      numVertices = 0;
      maxVertices = 10;

      numIndices = 0;
      maxIndices = 10;

      vertices.resize(maxVertices);
      indices.resize(maxIndices);

      drawMode = mode::Points;
   }

   void Clear() {
      vertices.clear();
      indices.clear();

      numVertices = 0;
      numIndices = 0;

      vertices.resize(maxVertices);
      indices.resize(maxIndices);
   }

   void addPoint(Vector3 vert)
   {
      drawMode = mode::Points;

      if ((numVertices + 1 < maxVertices) && (numIndices + 1 < maxIndices))
      {
         vertices[numVertices].position = vert;

         numVertices += 1;

         indices[numIndices] = numIndices;
         numIndices++;
      }
      else
      {
         maxVertices *= 2;
         maxIndices *= 2;

         vertices.resize(maxVertices);
         indices.resize(maxIndices);

         addPoint(vert);
      }
   }

   void addLine(uint a, uint b)
   {
      drawMode = mode::Lines;

      if (numIndices + 2 < maxIndices)
      {
         indices[numIndices] = a;
         indices[numIndices + 1] = b;

         numIndices += 2;
      }
      else
      {
         maxIndices *= 2;
         indices.resize(maxIndices);

         addLine(a, b);
      }
   }

   void setTexCoord(Vector2 texCoord)
   {
      vertices[numVertices].texCoord = texCoord;
   }

   void addVertex(Vector3 vert)
   {
      if (numVertices + 1 < maxVertices)
      {
         vertices[numVertices].position = vert;

         numVertices += 1;
      }
      else
      {
         maxVertices *= 2;
         vertices.resize(maxVertices);

         addVertex(vert);
      }
   }

   void addTri()
   {
      drawMode = mode::Tris;

      uint a = numVertices - 3;
      uint b = numVertices - 2;
      uint c = numVertices - 1;

      addTri(a, b, c);
   }

   void addTri(uint a, uint b, uint c)
   {
      drawMode = mode::Tris;

      if (numIndices + 3 < maxIndices)
      {
         indices[numIndices] = a;
         indices[numIndices + 1] = b;
         indices[numIndices + 2] = c;

         numIndices += 3;
      }
      else
      {
         maxIndices *= 2;
         indices.resize(maxIndices);

         addTri(a, b, c);
      }
   }

   void addQuad()
   {
      uint a = numVertices - 4;
      uint b = numVertices - 3;
      uint c = numVertices - 2;
      uint d = numVertices - 1;

      addQuad(a, b, c, d);
   }

   void addQuad(uint a, uint b, uint c, uint d)
   {
      drawMode = mode::Quads;

      if (numIndices + 4 < maxIndices)
      {
         indices[numIndices] = a;
         indices[numIndices + 1] = b;
         indices[numIndices + 2] = c;
         indices[numIndices + 3] = d;

         numIndices += 4;
      }
      else
      {
         maxIndices *= 2;
         indices.resize(maxIndices);

         addQuad(a, b, c, d);
      }

   }
};


}  // namespace city_sight

#endif
