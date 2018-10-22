#include <bits/stdc++.h> 
using namespace std; 

/* Variaveis Globais */
vector<int> nxt; 
int i = 0; 
int j = 0; 
int n = 0; 
int m = 0; 

void init_next(string pattern){
    i = 1; 
    j = 0;
    m = pattern.size(); 
    nxt.resize(m+1); 
    fill(nxt.begin(), nxt.end(), -1);  
    if(m == 1 || pattern[0] != pattern[1]){
        nxt[1] = 0;
    }

    while(i<m){
        while(i+j<m && pattern[i+j]==pattern[j]){
            j++;
            if(i+j == m || pattern[i+j] != pattern[j]){
                nxt[i+j] = j; 
            }else{
                nxt[i+j] = nxt[j]; 
            }
        }
        if(j == 0 && (i==m-1 || pattern[0] != pattern[i+1])){
            nxt[i+1] = 0; 
        }
        i += j - nxt[j]; 
        j = max(0, nxt[j]); 
    }
    
    //return nxt; 
}

vector<int> kmp (string pattern, string text){
    vector<int> occ; 
    int patt_init = 0; 
    n = text.size(); 
    m = pattern.size(); 
    i = 0; 
    j = 0; 
    while(i<=n-m){
       while(j<m && text[i+j]==pattern[j]){
           j++; 
       } 
       if(j == m){
           occ.push_back(i); 
       }
       i += max(1, j-nxt[j]); 
       j = max(0, nxt[j]);  
    }
    return occ; 
}

int main(){
    vector<int> occ; 
    ifstream f;
    string line;
    f.open("shakespeare.txt");
    init_next("unworthiness"); 
    
    vector<char>alphabet(128); 
    while (!f.eof()){
        getline(f, line); 
        occ = kmp("unworthiness", line); 
        for(int i = 0; i<occ.size();i++){
            cout<<occ[i]<<" ";
        }
        if(occ.size()>0) cout<<line<<endl;
       
    }
    return 0; 
}