#include "charsort.hpp"


struct numb{
    int xa,xb,ya,yb;
    char cha;
};


bool inSameLine(numb a, numb b){
    return (a.xa + (a.xb - a.xa +1 ) / 5 * 4 >= b.xa) &&
        (b.xa + (b.xb - b.xa +1 ) / 5 * 4 >= a.xa);
}


bool operator<(numb a,numb b){
    if(!inSameLine(a,b)){
        if(a.xa + (a.xb - a.xa +1 ) / 5 * 4 < b.xa){
            return 1;
        }
        return 0;
    }
    if(a.ya + (a.yb - a.yb) /5 *4 < b.ya){
        return 1;
    }
    return 0;
}


std::string charasort(std::vector<std::vector<int> >vec){
    int n = vec.size();
    numb tmp;
    std::vector<numb> arr;
    for(int i = 0; i < n; i++){
        tmp.xa = vec[i][0];
        tmp.ya = vec[i][1];
        tmp.xb = vec[i][2];
        tmp.yb = vec[i][3];
        tmp.cha = vec[i][4];
        arr.push_back(tmp);
    }
    std::sort(arr.begin(),arr.end());
    std::string ans = "";
    for(int i = 0; i < n; i++){
        if(i){
            if(inSameLine(arr[i], arr[i-1])){
                int tmp = arr[i].ya - arr[i-1].yb;
                if(tmp >= arr[i-1].yb - arr[i-1].ya/5 * 4){
                    ans.push_back(' ');
                }
            }
            else{
                ans.push_back('\n');
            }
        }
        ans.push_back(arr[i].cha);
    }
    ans.push_back('\n');
    return ans;
}
