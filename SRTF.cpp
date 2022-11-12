/*
Implementation of SRTF Scheduling by Labid
Space Complexity: O(n)
Time Complexity(avg): O(nlogn), [O(n^2) at worst]
*/

#include<bits/stdc++.h>

using namespace std;

class process{
	public:
		int id, at, bt, ct, tt, wt;			//processID, arrival time, brust time, completion time
};											//turn around time, waiting time

void SRTF(vector<process> &p){
	vector<process> waiting;

	sort(p.begin(),p.end(), [](const process &a, const process &b){return a.at<b.at;});
	
	int fa = p[0].at,count=0;
	while(p.size() and fa == p[0].at){
		waiting.push_back(p[0]);
		p.erase(p.begin());
	}
	sort(waiting.begin(),waiting.end(), [](const process &a, const process &b){return a.bt<b.bt;});

	while(p.size()!=0 or waiting.size()!=0){
		process cur;
		if(waiting.size() == 0){
			waiting.push_back(p[0]);
			p.erase(p.begin());
		}

		cur = waiting[0];

		if(count<cur.at) count = cur.at;

		if(cur.bt == 1){
			waiting.erase(waiting.begin());
		}else{
			waiting[0].bt -= 1;
		}

		cout<<count<<"-|P"<<cur.id+1<<"|-"<<++count<<endl;

		while(p.size() and count >= p[0].at){
			waiting.push_back(p[0]);
			p.erase(p.begin());
		}

		sort(waiting.begin(),waiting.end(), [](const process &a, const process &b){return a.bt<b.bt;});
	}
}

int main(){
	int a[] = {3,0,9,1,5};					//arrival time[i]
	int b[] = {7,2,9,5,4}; 					//brust time a[i]

	int n = sizeof(a) / sizeof(a[0]);
	vector<process> p(n);					//p = process, cp = scheduled process, waiting = waiting list

	for(int i=0;i<n;++i){					//initializing processid,arrival time and brust time
		p[i].id = i;
		p[i].at = a[i];
		p[i].bt = b[i];
	}

	SRTF(p);									
	
	return 0;
}

