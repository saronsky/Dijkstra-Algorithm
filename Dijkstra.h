//
// Created by Simon Aronsky on 4/27/20.
//

#ifndef HOMEWORK2_DIJKSTRA_H
#define HOMEWORK2_DIJKSTRA_H
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_set>
#pragma once
using namespace std;

class Dijkstra {
public:
  // A parent node and each of their connections
  struct Node {
    Node(string name) : name{name} {};
    string name;
    // map from distance to name of node from current Node
    multimap<int, string> edge;

    // function that returns iterator to map given value
    multimap<int, string>::iterator edgeContains(string name);
  };

  // function adds edge between two nodes
  void add(string first, string second, int distance);

  // function that returns the shortest distance between two nodes using
  // Dijkstra's Algorithm
  string shortestDistance(string firstString, string secondString);

  // find the node pointer
  map<string, Node *> findNode;
};

#include "Dijkstra.cpp"
#endif // HOMEWORK2_DIJKSTRA_H
