//
// Created by Simon Aronsky on 4/27/20.
//

#include "Dijkstra.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>

int main() {
  fstream fin;
  fin.open("AirportDistances.csv",
           ios::in);
  Dijkstra *graph = new Dijkstra();
  while (fin.good()) {
    string line;
    std::getline(fin, line);
    graph->add(line.substr(0, 3), line.substr(4, 3), stoi(line.substr(8)));
  }
  string origin;
  string destination;
  cout << "What are the two airport codes you would like to calculate the "
          "distance between?\nOrigin: ";
  cin >> origin;
  cout << "Destination: ";
  cin >> destination;
  cout << graph->shortestDistance(origin, destination) << endl << endl;
  return 0;
}
