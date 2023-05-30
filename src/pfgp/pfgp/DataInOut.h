#pragma once
#ifndef _DATAINOUT_H_
#define _DATAINOUT_H_
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<unordered_set>
#include<unordered_map>
#include<iomanip>
#include<iostream>
#include "mine.h"
#include "cppmine.h"
using namespace std;

extern int TerminalNumber;
extern int SampleNumber;
extern int record_gap;
extern vector<double>Y_train;
extern vector<vector<double>> X_train;
extern double  r2train;
extern double  r2test;
extern vector<pair<string, double>>expressions;

void Read(string filename);

void output();

void WeightByMIC(double* probability);
#endif // !_DATAINOUT_H
