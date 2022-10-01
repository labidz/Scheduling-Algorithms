/*
Implementation of FCFS Scheduling by Labid
Space Complexity: O(n)
Time Complexity(avg): O(nlogn), [O(n^2) at worst]
*/

#include<bits/stdc++.h>

using namespace std;

class process{
	public:
		int id, at, bt, wt, tt, ct;
};

void FCFS(vector<process> &p){
	vector<process> cp,waiting;
	int n = p.size();
	sort(p.begin(),p.end(), [](const process &a, const process &b){return (a.at < b.at);});

	int firstAT = p[0].at, prevCT = p[0].at;

	while(p.size() and p[0].at == firstAT){
		waiting.push_back(p[0]);
		p.erase(p.begin());
	}

	while(cp.size() != n){
		process cur;

		if(waiting.size() == 0){
			cur = p[0];
			p.erase(p.begin());
		}else{
			cur = waiting[0];
			waiting.erase(waiting.begin());
		}

		if(cur.at > prevCT) cur.ct = cur.at + cur.bt;
		else cur.ct = prevCT + cur.bt;

		prevCT = cur.ct;
		cur.tt = cur.ct - cur.at;
		cur.wt = cur.tt - cur.bt;
		cp.push_back(cur);

		while(p.size() and cur.ct >= p[0].at){
			waiting.push_back(p[0]);
			p.erase(p.begin());
		}
	}

	float avg = 0;
	cout<<"\n\nProcess ID\tArrival Time\tBurst Time\tCompletition Time\tTurn Around Time\tWaiting Time"<<endl;
	for(int i=0;i<n;++i){
		cout<<cp[i].id+1<<"\t\t"<<cp[i].at<<"\t\t"<<cp[i].bt<<"\t\t"<<cp[i].ct<<"\t\t\t"<<cp[i].tt<<"\t\t\t"<<cp[i].wt<<"\t\t\n"<<endl;
		avg += cp[i].wt;
	}

	cout<<"Average Waiting Time: "<<avg/n<<endl;

}

int main() {
	int a[] = {2,0,2,3,4};
	int b[] = {2,1,3,5,4};

	int n = sizeof(a)/sizeof(a[0]);
	vector<process> p(n);


	for(int i=0;i<n;++i){
		p[i].id = i;
		p[i].at = a[i];
		p[i].bt = b[i];
	}

	FCFS(p);
	return 0;
}


