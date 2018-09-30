
#include <algorithm>
    #include <Rcpp.h>
    #include <math.h>
    //#include "mddl.hpp"

    using namespace Rcpp;

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
        Rcerr << "Could not execute Multidimension Distance. Matrix's has different sizes.\n";
    }

    double dist = 0.0;
    for(int i=0; i<nm1.nrow(); ++i){
        dist += sqrt(sum(pow(nm1(i,_) - nm2(i,_), 2)));
    }

    return dist/nm1.nrow();
}

Rcpp::NumericMatrix embedd(Rcpp::NumericVector ts, int m, int d){
    int nrow = ts.size() - ((m-1)*d);
    int ncol = m;
    NumericMatrix at(nrow, ncol);
    for(int i=0; i<ncol; i++){
        for(int j=0; j<nrow; j++){
            at(j,i) = ts[j+(i*d)];
        }
    }
    return at;
}

// [[Rcpp::export]]
Rcpp::List mae(Rcpp::NumericVector ts1, Rcpp::NumericVector ts2){
    double val = 0;
    if(ts1.size() == ts2.size()){
        val = mean(abs(ts1 - ts2));
    } else {
        int delta = ts1.size() - ts2.size();
        for(int i=0; i < delta; ++i){
        }
    }
    return List::create(_["name"]="MAE", _["best"]="min", _["val"]=val);
}

// [[Rcpp::export]]
Rcpp::List rmse(Rcpp::NumericVector ts1, Rcpp::NumericVector ts2){
    double val = 0;
    if(ts1.size() == ts2.size()){
        val = sqrt(mean(pow(ts1 - ts2, 2)));
    } else {
        int delta = ts1.size() - ts2.size();
        for(int i=0; i < delta; ++i){
        }
    }
    return List::create(_["name"]="RMSE", _["best"]="min", _["val"]=val);
}

// [[Rcpp::export]]
Rcpp::List minkowski_p1(Rcpp::NumericVector ts1, Rcpp::NumericVector ts2){
    double val = sum(abs(ts1 - ts2));
    return List::create(_["name"] = "Minkowski_P1",
                        _["best"] = "min",
                        _["val"]  = val);
}

// [[Rcpp::export]]
Rcpp::List minkowski_p2(Rcpp::NumericVector ts1, Rcpp::NumericVector ts2){
    double val = sqrt(sum(pow(ts1 - ts2, 2)));
    return List::create(_["name"] = "Minkowski_P2",
                        _["best"] = "min",
                        _["val"]  =  val);
}

// [[Rcpp::export]]
Rcpp::List minkowski_p3(Rcpp::NumericVector ts1, Rcpp::NumericVector ts2){
    double val = cbrt( sum( pow( abs(ts1 - ts2), 3) ));
    return List::create(_["name"] = "Minkowski_P3",
                        _["best"] = "min",
                        _["val"]  = val);
}

// [[Rcpp::export]]
Rcpp::List mddl(Rcpp::NumericVector ts1, Rcpp::NumericVector ts2, Rcpp::Function dtw_f){

    Rcpp::List dtw = dtw_f(ts1, ts2);
    Rcpp::NumericVector x = dtw["index1"];
    Rcpp::NumericVector y = dtw["index2"];
    int sizeTS = ts1.size();
    int sizeMDDL = x.size();

    double result = 0;
    double step = ((double)sizeTS-1)/((double)sizeMDDL-1);
    double interval = 1;

    for(int i = 0; i < sizeMDDL; i++){
        result += sqrt(pow(x[i] - interval, 2) + pow(y[i] - interval,2));
        interval += step;
    }
    double val = result/sizeMDDL;
    return List::create(_["name"]="MDDL", _["best"]="min", _["val"]=val);
}

// [[Rcpp::export]]
Rcpp::List mda(Rcpp::NumericVector ts1, Rcpp::NumericVector ts2, int m, int d){
    NumericMatrix at1 = embedd(ts1, m, d);
    NumericMatrix at2 = embedd(ts2, m, d);
    double val = md_dist(at1, at2);
    return List::create(_["name"]="MDA", _["best"]="min", _["val"]=val);
}

// [[Rcpp::export]]
Rcpp::List pearsonCorrelation(Rcpp::NumericVector ts1, Rcpp::NumericVector ts2){
    double val = sum((ts1 - mean(ts1))*(ts2 - mean(ts2))) / (ts1.size()*stdev(ts1)* stdev(ts2));
    return List::create(_["name"]="Corr", _["best"]="max", _["val"]=val);
}

double ce(Rcpp::NumericVector x){
    double sum = 0.0;
    for(int i = 0; i < (x.size()-1); ++i)
        sum += pow(x[i] - x[i+1], 2);
    return sqrt(sum);
}

// [[Rcpp::export]]
double cf(Rcpp::NumericVector ts1, Rcpp::NumericVector ts2){
    double ce_x = ce(ts1);
    double ce_y = ce(ts2);

    if(ce_y > ce_x){
        double ce_aux = ce_x;
        ce_x = ce_y;
        ce_y = ce_aux;
    }

    return ce_x/ce_y;
}

// [[Rcpp::export]]
Rcpp::List euclidian_cid(Rcpp::NumericVector ts1, Rcpp::NumericVector ts2){
    Rcpp::List dist = minkowski_p2(ts1, ts2);
    double val = dist["val"];
    return List::create(_["name"]="Euclidian_CID", _["best"]="min", _["val"]= val * cf(ts1, ts2));
}

// [[Rcpp::export]]
Rcpp::List dtw_cid(Rcpp::NumericVector ts1, Rcpp::NumericVector ts2, Rcpp::Function dtw_f){
    Rcpp::List dtw_r = dtw_f(ts1,ts2);
    double val = dtw_r["distance"];
    return List::create(_["name"]="DTW_CID", _["best"]="min", _["val"] = val * cf(ts1, ts2));
}

// [[Rcpp::export]]
Rcpp::DataFrame evaluation_table_cpp(Rcpp::NumericVector ts1, Rcpp::NumericVector ts2, int m, int d, Rcpp::Function dtw_f){
    
    List eval_result(10);
    eval_result[0] = mae(ts1, ts2);
    eval_result[1] = rmse(ts1, ts2);
    eval_result[2] = minkowski_p1(ts1, ts2);
    eval_result[3] = minkowski_p2(ts1, ts2);
    eval_result[4] = minkowski_p3(ts1, ts2);
    eval_result[5] = pearsonCorrelation(ts1, ts2);
    eval_result[6] = mddl(ts1, ts2, dtw_f);
    eval_result[7] = mda(ts1, ts2, m, d);
    eval_result[8] = euclidian_cid(ts1, ts2);
    eval_result[9] = dtw_cid(ts1, ts2, dtw_f);

    //cria DataFrame to return
    StringVector  name(eval_result.size());
    StringVector  best(eval_result.size());
    NumericVector val(eval_result.size());
    for(int i=0; i < eval_result.size(); ++i){
        List er = eval_result[i];
        name[i] = Rcpp::as<std::string>(er["name"]);
        best[i] = Rcpp::as<std::string>(er["best"]);
        val[i]  = er["val"];
    }

    return DataFrame::create(_["name"]=name, _["best"]=best, _["val"]=val, _["stringsAsFactors"] = false );
}

// [[Rcpp::export]]
Rcpp::List whichBest(Rcpp::List evaluation){
    Rcpp::NumericMatrix tbl = evaluation["tbl"];
    Rcpp::CharacterVector scale = evaluation["scale"];
    Rcpp::IntegerVector best_map(tbl.nrow(), 0);
    Rcpp::IntegerVector best_idx(tbl.ncol());
    
    for(int i = 1; i < tbl.ncol(); ++i){
        if (strcmp("max", Rcpp::as<std::string>(scale[i-1]).c_str()) == 0) {
            best_map[Rcpp::which_max(tbl(_, i))]++;
        } else {
            best_map[Rcpp::which_min(tbl(_, i))]++;
        }
    }
    
    int idx = Rcpp::which_max(best_map);
    return Rcpp::List::create(_["metrics"] = Rcpp::colnames(tbl),
                              _["idx"]     = idx+1,
                              _["result"]  = tbl(idx,_)
                             );
}

// [[Rcpp::export]]
Rcpp::List evaluate_cpp(Rcpp::List result, Rcpp::Function dtw_f){
    Rcpp::List gs = result["gs"];
    Rcpp::List fgs = gs[0];
    Rcpp::List fgsp = fgs["params"];
    Rcpp::List series_obj = result["series_obj"];
    int m = series_obj["det.embDim"];
    int d = series_obj["det.sepDim"];
    Rcpp::NumericVector det = series_obj["det.series"];
    Rcpp::NumericMatrix tbl(gs.size(), 11);
    Rcpp::CharacterVector scale(2);
    for(int i = 0; i < gs.size(); ++i){
        List gs_i = gs[i];
        Rcpp::DataFrame df = evaluation_table_cpp(gs_i["det"], det, m, d, dtw_f);
        scale = df["best"];
        CharacterVector name = df["name"];
        name.push_front("test_id");
        colnames(tbl) = name;
        NumericVector laux = df["val"];
        tbl(i, 0) = i; //add test id
        for (int j = 1; j <= laux.size(); ++j){
            tbl(i, j) = laux[j-1];
        }
    }

    return Rcpp::List::create(_["tbl"] = tbl, _["scale"] = scale);
}

