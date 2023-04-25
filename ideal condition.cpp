#include<iostream>
#include<fstream>
#include<sstream>
#include<math.h>
#include<string>
#include<set>
#include<vector>
#include<algorithm>
#define attend 15
#define total 50
using namespace std;
set<pair<int, pair<string, int>>> record;
int min(int a, int b)
{
    return (a<b) ? a : b;
}
int record_score[200] = {0};
string record_match[200][20];
string record_place[200][20];
int score_record[5][6] = {{12000, 10200, 8400, 6600, 4800, 3000},
                    {11000, 9350, 7700, 6050, 4320, 2660},
                    {9200, 7800, 6420, 5040, 3600, 2220},
                    {7000, 5950, 4900, 3850, 2750, 1670},
                    {5500, 4680, 3850, 3030, 2110, 1290}};
string match_name[5] = {"super1000", "super750", "super500", "super300", "super100"};
enum match_symbol{super1000, super750, super500, super300, super100};
string find_matchname_place(int score)
{
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 6; j++){
            if(score_record[i][j] == score){
                return match_name[i] + " " + to_string(int(pow(2, j)));
            }
        }
    }
    return "error";
}

int check_match(string match_name){
    if(match_name == "1000")
        return super1000;
    if(match_name == "750")
        return super750;
    if(match_name == "500")
        return super500;
    if(match_name == "300")
        return super300;
    if(match_name == "100")
        return super100;
    return -1;    
}
class Record
{
    public:
        Record(){
            
        }
        Record(string date, string match_name){
            this->freq = 1;
            for(int i = 0; i < 6; i++){
                this->record_freq[i] = pow(2, i);
                set_score(check_match(match_name), i);
            }
            set_date(date);
            set_match_name(match_name);
        }
        void set_date(string date){
            this->date = date;
        }
        void set_match_name(string match_name){
            this->match_name = match_name;
        }
        void set_score(int match_num, int place){
            this->score[place] = score_record[match_num][place];
        }
        int record_freq[5];
        string date;
        string match_name;
        int score[5];
        int freq;
};
const std::vector<std::string> split(const std::string &str, const char &delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string tok;

    while (std::getline(ss, tok, delimiter)) {
        result.push_back(tok);
    }
    return result;
}
void find_max(){
    //set<pair<int, string>> temp;  
    static int id; 
    int temp_score = 0;
    int temp_min9[21] = {0}, count_min9 = 0;
    vector<string> temp;
    vector<string> temp_place;
    for(int i = 0;  i < attend; i++){
        bool flag = false;
        for(auto j : temp){
            if(j == record.rbegin()->second.first){       // cheack nor repeat
                flag = true;
                break;
            } 
        }
        if(!flag){
            auto t = record.rbegin();
            temp.push_back(t->second.first);
            temp_place.push_back(find_matchname_place(t->first));
            //cout << t->first  << " " << t->second.first  << " " << t->second.second << endl;
            temp_min9[count_min9++] = t->first;
            //temp_score += t->first;
            if(t->second.second > 1){
                const_cast<pair<int, pair<string, int>>&>(*t) = make_pair(t->first, make_pair(t->second.first, t->second.second - 1));
            }else{
                record.erase(*t);
            }
        }else{
            auto t = record.rbegin();
            while(find(temp.begin(), temp.end(), t->second.first) != temp.end()){
                t++;
            }
            temp.push_back(t->second.first);
            temp_place.push_back(find_matchname_place(t->first));
            //cout << t->first  << " " << t->second.first  << " " << t->second.second << endl;
            temp_min9[count_min9++] = t->first;
            //temp_score += t->first;
            if(t->second.second > 1){
                const_cast<pair<int, pair<string, int>>&>(*t) = make_pair(t->first, make_pair(t->second.first, t->second.second - 1));
            }else{
                record.erase(*t);
            }            
        }
        
    }
    sort(temp_min9, temp_min9 + count_min9);
    for(int i = 0; i < count_min9 ; i++){
        if(i >= (count_min9 - 9))
        temp_score += temp_min9[i];
    }
    record_score[id] = (temp_score)*1.1;

    //cout << temp_score * 1.1 << "\t";
    //cout << record_score[id] << "\t";
    for(int j = 0; j < temp.size(); j++){
        record_match[id][j] = temp[j];
        //cout << record_match[id][j]  << "\t"; 
    }
    /*for(auto i : temp){
        //cout << i  << "\t";
        record_match[id][j++] = i;
        cout << record_match[id][j]  << "\t";
    }*/
    //cout << endl;
    //cout << "\t";
    for(int j = 0; j < temp_place.size(); j++){
        record_place[id][j] = temp_place[j];
        //cout << record_place[id][j]  << "\t";
    }
    /*for(auto i : temp_place){
        //cout << i  << "\t";
        record_place[id][k++] = i;
        cout << record_place[id][k] << "\t";
    }*/
    //cout << endl;
    id++;
    temp.clear();
}
void list_all()
{
    for(int i = 0; i < total; i++){
        cout << record_score[i] << '\t';
        for(int j = 0; j < attend; j++){
            cout << record_match[i][j] << '\t';
        }
        cout << '\n' << '\t';
        for(int j = 0; j < attend; j++){
            cout << record_place[i][j] << '\t';
        }
        cout << endl;
    }   
}
void find()
{
    int lb, ub;
    do{
        cout << "print -1 to quit" << endl;
        cout << "lower bound" << endl;
        cin >> lb;
        if(lb == -1) break;
        cout << "upper bound" << endl;
        cin >> ub;
        for(int i = 0; i < total; i++){
            if(record_score[i] >= lb && record_score[i] <= ub){
                cout << record_score[i] << '\t';
                for(int j = 0; j < attend; j++){
                    cout << record_match[i][j] << '\t';
                }
                cout << '\n' << '\t';
                for(int j = 0; j < attend; j++){
                    cout << record_place[i][j] << '\t';
                }
                cout << endl;
            }
        }
    }
    while(1);
}
int main()
{
    string line, cmd;
    ifstream fp("record.txt", ifstream::in);
    ofstream fp2;
    fp2.open("ideal15.txt");
    while(std::getline(fp, line)){
        std::vector<std::string> ret = split(line, '\t');
        /*for(auto& i : ret)
            cout << i << "\n";
        cout << endl;*/
        for(int i = 0; i < 6; i++){
            record.insert(make_pair(score_record[check_match(ret[0])][i], make_pair(ret[1], int(pow(2, i) - floor(pow(2, i-1))))));
        }
    }
    /*for(auto i=record.begin(); i!=record.end(); ++i){
        cout << i->first  << " " << i->second.first  << " " << i->second.second << endl;
    }*/

    //cout << (record.rbegin())->first << ' ' << record.rbegin()->second.first << " " << record.rbegin()->second.second << endl;
    for(int j = 0; j < total; j++){
        find_max();
    }
    for(int i = 0; i < total; i++){
        fp2 << record_score[i] << '\t';
        /*for(int j = 0; j < attend; j++){
            fp2 << record_match[i][j] << '\t';
        }
        fp2 << '\n' << '\t';
        for(int j = 0; j < attend; j++){
            fp2 << record_place[i][j] << '\t';
        }*/
        fp2 << endl;
    }   
    //cout << "------------" <<endl;
    fp.close();
    
    return 0;
}