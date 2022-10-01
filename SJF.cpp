/*
Implementation of SJF Scheduling by Labid
Space Complexity: O(n)
Time Complexity(avg): O(nlogn), [O(n^2) at worst]
*/

#include<bits/stdc++.h>

using namespace std;

class process{
	public:
		int id, at, bt, ct, tt, wt;			//processID, arrival time, brust time, completion time
};											//turn around time, waiting time

void SJF(vector<process> &p){
	vector<process> cp,waiting;
	int n = p.size();

	sort(p.begin(), p.end(), [](const process &a, const process &b){ return (a.at < b.at);}); //sorting WRT arrival time

	while(p.size() and 0 == p[0].at){				//waiting list
			waiting.push_back(p[0]);
			sort(waiting.begin(), waiting.end(), [](const process &a, const process &b){ return (a.bt < b.bt);});
			p.erase(p.begin());
		}				//pop from the main list
	int prevCT = 0;

	for(int i=0;i<n*13+2;++i) 		//ignore
		cout<<"-";
	cout<<endl;
	while(cp.size() != n){			//while scheduling is not done
		process cur;
		if(waiting.size() == 0){	//check waiting list, if empty then take the next process
            cur = p[0];
            p.erase(p.begin());
		}
		else{
            cur = waiting[0];
            waiting.erase(waiting.begin());
		}
		if(cur.at >= prevCT) cur.ct = cur.at + cur.bt; 		//if waiting list is empty then
		else cur.ct = prevCT + cur.bt;							//complition time = arrival time + brust time

		cout<<"("<<cur.ct-cur.bt<<") P"<<cur.id+1<<" ("<<cur.ct<<") | ";	//ignore

		prevCT = cur.ct;
		cur.tt = cur.ct - cur.at;
		cur.wt = cur.tt - cur.bt;
		cp.push_back(cur);

		while(p.size() and cur.ct >= p[0].at){				//waiting list
			waiting.push_back(p[0]);
			sort(waiting.begin(), waiting.end(), [](const process &a, const process &b){ return (a.bt < b.bt);});
			p.erase(p.begin());
		}
	}
	cout<<endl;
	for(int i=0;i<n*13+2;++i) 		//ignore
		cout<<"-";

	float avg = 0;
	//printing the schedule
	cout<<"\n\nProcess ID\tArrival Time\tBurst Time\tCompletition Time\tTurn Around Time\tWaiting Time"<<endl;
	for(int i=0;i<n;++i){
		cout<<cp[i].id+1<<"\t\t"<<cp[i].at<<"\t\t"<<cp[i].bt<<"\t\t"<<cp[i].ct<<"\t\t\t"<<cp[i].tt<<"\t\t\t"<<cp[i].wt<<"\t\t\n"<<endl;
		avg += cp[i].wt;
	}

	cout<<"Average Waiting Time: "<<avg/n<<endl;
}

int main() {
	int a[] = {5,0,0,9,5,5};					//arrival time[i]
	int b[] = {2,2,1,1,2,2}; 					//brust time a[i]

	int n = sizeof(a) / sizeof(a[0]);
	vector<process> p(n);					//p = process, cp = scheduled process, waiting = waiting list

	for(int i=0;i<n;++i){					//initializing processid,arrival time and brust time
		p[i].id = i;
		p[i].at = a[i];
		p[i].bt = b[i];
	}

	SJF(p);									
	
	return 0;
}
