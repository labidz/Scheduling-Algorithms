/***
Implemetation of Bankers Algorithm by Labid
Space Complexity: O(n)

GitHub: labidzy
****/

#include<bits/stdc++.h>
using namespace std;

class process{
    private:
        vector<int> alloc, max, need;
    
    public:
        bool safe = false;
        //set methods
        void insert(vector<int> a, vector<int> m){
            for(int i=0;i<a.size();++i){
                alloc.push_back(a[i]);
                max.push_back(m[i]);
                need.push_back(m[i]-a[i]);  //curr need = max - alloc
            }
        }

        //get methods
        vector<int> getAlloc(){
            return alloc;
        }
        vector<int> getMax(){
            return max;
        }
        vector<int> getNeed(){
            return need;
        }

};

bool isSafe(vector<process> &processes, int n, vector<int> &need, vector<int> &available){
    //checking all if all the instances are allocatable per need
    for(int i=0;i<need.size();++i){
        if(need[i]>available[i])
            return false;
    }

    vector<int> alloc = processes[n].getAlloc();
    //updating the available resources
    for(int i=0;i<available.size();++i){
        available[i] += alloc[i];
    }
    return true;
}

void calculateSafeSequence(vector<process> &processes, vector<int> &available, int n){
    //store the safe sequence
    vector<int> seq;
    //loop untill all the process are in dafe sequence
    int count=0;
    while(seq.size() != n){
        //getting the compatible process
        for(int i=0;i<processes.size();++i){
            if(processes[i].safe != true){
                vector<int> need = processes[i].getNeed();
                //isSafe function returns the state of the current process
                if(isSafe(processes, i, need, available)){
                    seq.push_back(i);
                    processes[i].safe = true;
                }
            }
        }

        //checking if deadlock occured by counting all the sequences
        count++;
        if(count>(n*n)){
            cout<<"Deadlock"<<endl;
            return;
        }
    }
    //printing the sequence
    for(int i=0;i<seq.size();++i){
        cout<<"P"<<seq[i];
        if(i<seq.size()-1) cout<<"->";
    }
    //last aviable resource
    cout<<"\nAviable: ";
    for(auto elm : available) cout<<"("<<elm<<")";
}

//the print function
void print(vector<process> &processes){
    cout<<"Allocation \t Max \t Need"<<endl;
    for(int i=0;i<processes.size();++i){
        //getting all the values
        vector<int> alloc = processes[i].getAlloc();
        vector<int> max = processes[i].getMax();
        vector<int> need = processes[i].getNeed();

        cout<<"P"<<i<<": ";
        for(int j=0;j<alloc.size();++j){
            cout<<alloc[j]<<" ";
        }
        cout<<"\t";
        for(int j=0;j<max.size();++j){
            cout<<max[j]<<" ";
        }
        cout<<"\t";
        for(int j=0;j<need.size();++j){
            cout<<need[j]<<" ";
        }
        cout<<endl;
    }
    cout<<"\n\n"<<endl;
}

int main(){
    //setting all the values [MID Question]
    vector<vector<int>> allocation{
        {1,0,3},
        {2,1,1},
        {3,1,2},
        {4,0,2},
        {2,1,3}
    };
    vector<vector<int>> max{
        {6,4,4},
        {5,3,2},
        {4,4,3},
        {6,0,8},
        {4,3,4}
    };
    vector<int> available{3,4,2};

    //declaring the processes and essentials
    int n = allocation.size();
    vector<process> processes(n);


    //asigning the values to the processes
    for(int i=0;i<n;++i){
        processes[i].insert(allocation[i], max[i]);
    }

    //printing
    print(processes);
    //calculate the safe sequence
    calculateSafeSequence(processes, available, n);
    return 0;
}
