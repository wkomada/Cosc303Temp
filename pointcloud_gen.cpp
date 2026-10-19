// pointcloud_gen.cpp
// Jake Atwood
// COSC303, 10/18/2026
//
// Generates random 3D points and connects every pair that is within a given radius. 
// Output will (hopefully) be used by future A* / Dijkstra programs.
//
// Build:   g++ -std=c++17 -O2 -o pointcloud_gen pointcloud_gen.cpp (or whatever c++ version after 11 u want ig)
// Run:     ./pointcloud_gen [numPoints] [radius] [seed]
// Example: ./pointcloud_gen 2000 10 42
//
// Outputs:
// points.csv : id,x,y,z
// edges.csv  : from,to,weight (each pair stored once, from < to)

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <cmath>
using namespace std;

// A point's ID is its index in the pts vector, so it isn't stored here
// Just a basic 3 dimensional coordinate
struct Point { double x, y, z; };

const double SIZE = 100.0;  // the side length of the cube the points live in, so points are in [0,SIZE]^3

// Straight-line distance between two points
double dist(const Point& a, const Point& b) {
  double dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z; // Intermediate difference steps
  return sqrt(dx * dx + dy * dy + dz * dz); // Take square root of differences
}

int main(int argc, char** argv) {
  int n = 2000;              // number of points to generate
  double radius = 10.0;      // max distance in order for two points to be connected
  int seed = 12345;          // random seed (same seed means same data every run)
  mt19937 rng;               // random number generator (seeded below) [using this because it is apparently the best rng for c++]
  uniform_real_distribution<double> U(0.0, SIZE); // turns the random numbers into random doubles in [0,SIZE]
  vector<Point> pts;         // all the points, pts[i] is point i
  int edgeCount = 0;         // number of edges written
  int i, j;                  // point indexes for the for loops
  double d;                  // distance between the current pair of points
  ofstream pf("points.csv"); // output file for points
  ofstream ef("edges.csv");  // output file for edges

  // Defaults can be changed in the command line by user
  if (argc > 1) n = stoi(argv[1]);
  if (argc > 2) radius = stod(argv[2]);
  if (argc > 3) seed = stoi(argv[3]);

  // Generate random points using the mt19937 rng variable declared earlier
  rng.seed(seed);
  for (i = 0; i < n; i++) {
    pts.push_back({U(rng), U(rng), U(rng)}); // Add to the uniform real distribution to get them into [0,SIZE]
  }

  // Write points
  pf << "id,x,y,z\n";
  for (i = 0; i < n; i++) { 
    pf << i << ',' << pts[i].x << ',' << pts[i].y << ',' << pts[i].z << '\n';
  }

  // Write edges by connecting every pair within radius.
  // j starts at i + 1 so each pair is only checked once (no self-pairs, no duplicates).
  ef << "from,to,weight\n";
  for (i = 0; i < n; i++) {
    for (j = i + 1; j < n; j++) {
      d = dist(pts[i], pts[j]); // Find the distance between the two points
      if (d <= radius) { // Has to be within the selected radius to be connected
        ef << i << ',' << j << ',' << d << '\n';
        edgeCount++;
      }
    }
  }

  cout << "Points: " << n << "  Edges: " << edgeCount << "\n"; // Output data both for the information and to show everything worked
  return 0;
}
