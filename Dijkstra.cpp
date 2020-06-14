//
// Created by Simon Aronsky on 4/27/20.
//
#include "Dijkstra.h"
#include <iostream>
#include <set>
#include <unordered_set>
using namespace std;

// returns iterator to map given value
multimap<int, string>::iterator Dijkstra::Node::edgeContains(string name) {

  for (auto i = edge.begin(); i != edge.end(); ++i) {
    // if node name = string name
    if (i->second.compare(name) == 0)
      return i;
  }
  return edge.end();
}

// adds edge between two nodes
void Dijkstra::add(string originString, string destinationString,
                   int distance) {
  // if originString is already a node
  if (findNode.find(originString) == findNode.end())
    findNode.insert(pair<string, Node *>(originString, new Node(originString)));
  // if destinatinString is already a node
  if (findNode.find(destinationString) == findNode.end())
    findNode.insert(
        pair<string, Node *>(destinationString, new Node(destinationString)));
  Node *origin = findNode.at(originString);
  Node *destination = findNode.at(destinationString);
  // add origin and destination to each edge map
  origin->edge.insert(pair<int, string>(distance, destinationString));
  destination->edge.insert(pair<int, string>(distance, originString));
}

// returns the shortest distance between two nodes using Dijkstra's Algorithm
string Dijkstra::shortestDistance(string originString,
                                  string destinationString) {
  unordered_set<string> unvisited;
  Node *origin = findNode.at(originString);
  // adds all unvisited nodes to unvisited set
  for (auto i = findNode.rbegin(); i != findNode.rend(); ++i) {
    if (i->first.compare(originString) != 0)
      unvisited.insert(i->first);
  }

  // while the destination is unvisited
  while (unvisited.find(destinationString) != unvisited.end()) {
    // i is each connection mapping
    auto i = origin->edge.begin();

    // closest unvisited node to origin
    Node *closestUnvisited = nullptr;
    int closestUnvisitedDist = 0;

    // while i is not at the end and the closest unvisited has not been found
    while (i != origin->edge.end() && closestUnvisited == nullptr) {
      if (unvisited.find(i->second) != unvisited.end()) {
        closestUnvisited = findNode.at(i->second);
        closestUnvisitedDist = i->first;
      } else
        ++i;
    }
    // if there are no more connected nodes from origin to visit
    if (closestUnvisited == NULL)
      return "These nodes are not connected";
    else
      unvisited.erase(closestUnvisited->name);

    // iterate through closestUnvisited's edges to add
    for (i = closestUnvisited->edge.begin(); i != closestUnvisited->edge.end();
         i++) {
      // iterator to origin edge of current edge
      auto it = origin->edgeContains(i->second);
      int currEdgeDist;

      // if origin edges dont already contain current edge
      if (it == origin->edge.end())
        origin->edge.insert(
            pair<int, string>(closestUnvisitedDist + i->first, i->second));

      // if origin edges contain current edge
      else {
        // previous path distance to i ClosestUnvisited edge node
        currEdgeDist = origin->edgeContains(i->second)->first;
        // if distance to closestUnvisited + i edge node < previous path
        // distance to i edge node
        if (closestUnvisitedDist + i->first < currEdgeDist) {
          int newDist = closestUnvisitedDist + i->first;
          string newName = i->second;
          origin->edge.erase(origin->edgeContains(i->second));
          origin->edge.insert(pair<int, string>(newDist, newName));
        }
      }
    }
  }
  return to_string(origin->edgeContains(destinationString)->first);
}