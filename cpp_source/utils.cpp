#include "utils.hpp"

bool find_string(std::string str, Rcpp::List l){
	for(int i = 0; i < l.size(); ++i){
		if(str.compare(Rcpp::as<std::string>(l[i])) == 0){ 
			return true;
		}
	}
	return false;
}

double var(Rcpp::NumericVector x){
	return (sum(pow(x - mean(x),2)))/x.size();
}

double stdev(Rcpp::NumericVector x){
	return sqrt(var(x));
}

double md_dist(Rcpp::NumericMatrix nm1, Rcpp::NumericMatrix nm2){
	if(nm1.size() != nm2.size()) {
		Rcpp::Rcerr << "Could not execute Multidimension Distance. Matrix's has different sizes.\n";
	}

	double dist = 0.0;
	for(int i=0; i<nm1.nrow(); ++i){
		dist += sqrt(sum(pow(nm1(i,Rcpp::_) - nm2(i,Rcpp::_), 2)));
	}

	return dist/nm1.nrow();
}

Rcpp::NumericVector orderVec(Rcpp::NumericVector vec){                                  
    double tmp = 0;
    int n = vec.size();
    Rcpp::NumericVector outvec = clone(vec);
    for (int i = 0; i <n; ++i){
        outvec[i]=static_cast<double>(i)+1.0;
    }

    int no_swaps;
    int passes;
    passes = 0;
    while(true) {
        no_swaps = 0;
        for (int i = 0; i < n - 1 - passes; ++i) {
            if(vec[i] > vec[i+1]) {
                no_swaps++;
                tmp = vec[i];
                vec[i] = vec[i+1];
                vec[i+1] = tmp;
                tmp = outvec[i]; 
                outvec[i] = outvec[i+1];  
                outvec[i+1] = tmp; 
            };
        };
        if(no_swaps == 0) break;
        passes++;
    };       
    return(outvec);
}

Rcpp::NumericMatrix embedd(Rcpp::NumericVector ts, int m, int d){
	int nrow = ts.size() - ((m-1)*d);
	int ncol = m;
	Rcpp::NumericMatrix at(nrow, ncol);
	for(int i=0; i<ncol; i++){
		for(int j=0; j<nrow; j++){
			at(j,i) = ts[j+(i*d)];
		}
	}
	return at;
}

double dist(Rcpp::NumericVector x1, Rcpp::NumericVector x2){
    double d = 0.0;
    for(int i = 0; i < x1.size(); ++i){
        d += pow(x1(i) - x2(i), 2);
    }
    return sqrt(d);
}

Rcpp::NumericMatrix dist(Rcpp::NumericMatrix data){
	int nrow = data.nrow();
    double d  = 0.0;
	Rcpp::NumericMatrix d_mat(nrow, nrow);
	for(int i=0; i<nrow; i++){
		for(int j=i; j<nrow; j++){
            d = dist(data(i,Rcpp::_), data(j,Rcpp::_));
			d_mat(j,i) = d;
            d_mat(i,j) = d;
		}
	}
	return d_mat;
}

Rcpp::NumericVector toTimeSpace(Rcpp::NumericMatrix sEmb, int m, int d){
    if(m <= 1 | sEmb.ncol() != m){ 
        Rcpp::Rcerr << 'Erro'; 
        return R_NilValue;
    }
    /*
    int n  = sEmb.nrow();
    int k  = ceil(m/2);

    Rcpp::NumericVector ts = c();
    if(m == 2){
        ts = c(s.emb[,1], s.emb[(n-d+1):n,2])
    } else {
        for(i in 1:max(c(1,k-1))) ts = c(ts, s.emb[1:d, i])
        ts = c(ts, s.emb[, k])
        for(i in (k+1):m) ts = c(ts, s.emb[(n-d+1):n,i])
    }
    return(ts)
    */
    return R_NilValue;
}
