/*
Implementation of Round Robin Scheduling by Labid
Space Complexity: O(n)
Time Complexity(avg): O(nlogn), [O(n^2) at worst]
*/

#include<bits/stdc++.h>

using namespace std;

class process{
	public:
		int id, at, bt, ct, tt, wt;			//processID, arrival time, brust time, completion time
};											//turn around time, waiting time

void RR(vector<process> &p, int timeQuantum){
	vector<process> waiting;

	sort(p.begin(),p.end(), [](const process &a, const process &b){return a.at<b.at;});
	
	int fa = p[0].at, prevCT = fa;
	while(p.size() and fa == p[0].at){
		waiting.push_back(p[0]);
		p.erase(p.begin());
	}

	while(p.size()!=0 or waiting.size()!=0){
		process cur;
		int time = timeQuantum, ck=0;
		
		if(waiting.size() == 0){
			waiting.push_back(p[0]);
			p.erase(p.begin());
		}

		cur = waiting[0];

		if(cur.at>prevCT){
			prevCT = cur.at;
		}

		if(cur.bt <= timeQuantum){
			waiting.erase(waiting.begin());
			time = cur.bt;
		}else{
			waiting[0].bt -= timeQuantum;
			cur = waiting[0];
			waiting.erase(waiting.begin());
			ck = 1;
		}

		cout<<prevCT<<"|P"<<cur.id+1<<"|"<<prevCT+time<<endl;
		prevCT += time;

		while(p.size() and prevCT >= p[0].at){
			waiting.push_back(p[0]);
			p.erase(p.begin());
		}

		if(ck == 1){
			waiting.push_back(cur);
		}
	}
}

int main(){
	int a[] = {0,5,1,6,8};					//arrival time[i]
	int b[] = {8,2,7,3,5}; 					//brust time a[i]
	int timeQuantum = 3;

	int n = sizeof(a) / sizeof(a[0]);
	vector<process> p(n);					//p = process, cp = scheduled process, waiting = waiting list

	for(int i=0;i<n;++i){					//initializing processid,arrival time and brust time
		p[i].id = i;
		p[i].at = a[i];
		p[i].bt = b[i];
	}

	RR(p,timeQuantum);									
	
	return 0;
}
