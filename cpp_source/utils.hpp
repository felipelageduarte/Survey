#ifndef RCPP_UTILS_H
#define RCPP_UTILS_H

#include <algorithm>
#include <Rcpp.h>

bool find_string(std::string str, Rcpp::List l);
double var(Rcpp::NumericVector x);
double stdev(Rcpp::NumericVector x);
double md_dist(Rcpp::NumericMatrix nm1, Rcpp::NumericMatrix nm2);
Rcpp::NumericMatrix embedd(Rcpp::NumericVector ts, int m, int d);
double dist(Rcpp::NumericVector x1, Rcpp::NumericVector x2);
Rcpp::NumericMatrix dist(Rcpp::NumericMatrix data);
Rcpp::NumericVector toTimeSpace(Rcpp::NumericMatrix sEmb, int m, int d);

#endif