//
// Created by jharo on 6/24/2019.
//
#pragma once
#ifndef TP_PAA_MIS_H
#define TP_PAA_MIS_H
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <unordered_set>
#include <algorithm>
#include <chrono>
#include <cmath>


#define DEBUG

using namespace std;
using namespace chrono;

vector<pair<int,unordered_set<int>>> loadGraph(const string& arquivo="input.txt");
vector<pair<int,unordered_set<int>>> loadGraphComplemento(const string& arquivo="input.txt");
vector<pair<int,unordered_set<int>>> generateSat(const string& arquivo="input.txt");
int maximumIndependent(vector<unordered_set<int>>const&, unordered_set<int>, unordered_set<int>,int);
bool check(const vector<unordered_set<int>>& );
int greedy(vector<unordered_set<int>> );
int countEdge(vector<unordered_set<int>>const& , unordered_set<int>const& );
int teste(int n, int m);
int findMSI();


#endif //TP_PAA_MIS_H
