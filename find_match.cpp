#include<iostream>
#include<fstream>
#include<sstream>
#include<math.h>
#include<string>
#include<set>
#include<vector>
#include<algorithm>
using namespace std;
string record[550][25];
int BS_upperbound(int l, int r, string tar){
    while(l < r){
        int mid = (l+r)/2;
        if(record[mid][0] > tar) r = mid;
        else l = mid + 1;
    }
    return r;
}
int BS_lowerbound(int l, int r, string tar){
    while(l < r){
        int mid = (l+r)/2;
        if(record[mid][0] >= tar) r = mid;
        else l = mid + 1;
    }
    return r;
}
const std::vector<std::string> split(const std::string &str, const char &delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string tok;

    while (std::getline(ss, tok, delimiter)) {
        result.push_back(tok);
    }
    return result;
}
int main()
{
    int lb, ub;
    string line;
    ifstream fp("record.txt", ifstream::in);
    while(std::getline(fp, line)){
        int j = 0;
        cout << line << endl;
        std::vector<std::string> ret = split(line, '\t');
        for(auto& i : ret)
            cout << i << "\n";
        cout << endl;
        //record[j][0] = stoi(ret[0]);
        for(int i = 0; i < ret.size(); i++){
            record[j][i] = ret[i];
        }
        j++;
    }
    fp.close();
    do{
        cout << "key in -1 to quit" << endl;
        cout << "lower bound" << endl;
        cin >> lb;
        cout << "upper bound" << endl;
        cin >> ub;
        int lower_bound = BS_lowerbound(0, 502, to_string(lb));
        int upper_bound = BS_upperbound(0, 502, to_string(ub));
        for(int i = lower_bound; i < upper_bound; i++){
            for(int j = 0; j < 19; j++){
                if(j == 9)
                    cout << record[i][j] << endl;
                else
                    cout << record[i][j] << '\t';
            cout << endl;
            }
        }
    }
    while(lb != -1);
    return 0;
}