////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Simple obj file parser

// STL
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class Vector2 {
  public:

    Vector2() : m_x{0.f}, m_y{0.f} {}

    friend istream& operator>>(istream& _is, Vector2& _v) {
      return _is >> _v.m_x >> _v.m_y;
    }

  private:
    float m_x, m_y;
};

class Vector3 {
  public:

    Vector3() : m_x{0.f}, m_y{0.f}, m_z{0.f} {}

    friend istream& operator>>(istream& _is, Vector3& _v) {
      return _is >> _v.m_x >> _v.m_y >> _v.m_z;
    }

    friend ostream& operator<<(ostream& _os, const Vector3& _v) {
      return _os << _v.m_x << " " << _v.m_y << " " << _v.m_z;
    }

  private:
    float m_x, m_y, m_z;
};

struct Vertex {
  size_t m_p, m_t, m_n;
};

struct Face {
  Vertex m_v[3];
};

class Model {
  public:
    Model(string _s) : m_filename{_s} {
      ifstream ifs{m_filename};
      string line;
      int i = 0;
      while(getline(ifs, line)) {
        string tag;
        istringstream iss{line};
        iss >> tag;

        if(tag == "v") {
          Vector3 v;
          iss >> v;
          m_points.emplace_back(v);
        }

        else if(tag == "vt") {
          Vector2 v;
          iss >> v;
          m_textures.emplace_back(v);
        }

        else if(tag == "vn") {
          Vector3 v;
          iss >> v;
          m_normals.emplace_back(v);
        }

        else if(tag == "f") {
          Face f;
          for(size_t i = 0; i < 3; ++i) {
            Vertex v;
            string vert;
            iss >> vert;
            sscanf(vert.c_str(), "%zu/%zu/%zu", &v.m_p, &v.m_t, &v.m_n);
            f.m_v[i] = v;
          }
          m_faces.emplace_back(f);
        }
        else {
        }
      }
    }

    void print_data() const {
      cout << "Model contains:" << endl
        << "\t" << m_points.size() << " points" << endl
        << "\t" << m_normals.size() << " normals" << endl
        << "\t" << m_textures.size() << " textures" << endl
        << "\t" << m_faces.size() << " faces" << endl;
    }
  private:
    string m_filename;

    vector<Vector3> m_points;
    vector<Vector3> m_normals;
    vector<Vector2> m_textures;

    vector<Face> m_faces;
};

int
main(int _argc, char** _argv) {
  if(_argc != 2) {
    cout << "Error: please provie a command line argument." << endl;
    exit(1);
  }

  string filename{_argv[1]};
  Model m{filename};
  m.print_data();
}
