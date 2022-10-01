/*
Implementation of Priority Scheduling by Labid
Space Complexity: O(n)
Time Complexity(avg): O(nlogn), [O(n^2) at worst]
*/

#include<bits/stdc++.h>

using namespace std;

class process{
	public:
		int id, at, bt, pr, ct, tt, wt;		//processID, arrival time, brust time, priority
};											//completion time, turn around time, waiting time

void priorityScheduling(vector<process> &p){
	vector<process> cp,waiting;				//cp = scheduled process, waiting = waiting list
	int n = p.size();

	sort(p.begin(), p.end(), [](const process &a, const process &b){ return (a.at < b.at);}); //sorting WRT arrival time

	int firstArrival = p[0].at;
	while(p.size() and firstArrival == p[0].at){				//waiting list
			waiting.push_back(p[0]);
			sort(waiting.begin(), waiting.end(), [](const process &a, const process &b){ return (a.pr < b.pr);});
			p.erase(p.begin());
		}					//pop from the main list
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

		while(p.size() and cur.ct >= p[0].at){				//waiting list refresh
			waiting.push_back(p[0]);
			sort(waiting.begin(), waiting.end(), [](const process &a, const process &b){ return (a.pr < b.pr);});
			p.erase(p.begin());
		}
	}
	cout<<endl;
	for(int i=0;i<n*13+2;++i) 		//ignore
		cout<<"-";

	float avg = 0;
	//printing the schedule
	cout<<"\n\nProcess ID\tArrival Time\tBurst Time\tCompletition Time\tTurn Around Time\tWaiting Time\tPriority"<<endl;
	for(int i=0;i<n;++i){
		cout<<cp[i].id<<"\t\t"<<cp[i].at<<"\t\t"<<cp[i].bt<<"\t\t"<<cp[i].ct<<"\t\t\t"<<cp[i].tt<<"\t\t\t"<<cp[i].wt<<"\t\t"<<cp[i].pr<<endl;
		avg += cp[i].wt;
	}

	cout<<"Average Waiting Time: "<<avg/n<<endl;
}

int main() {
	int a[] = {0,5,12,2,9};					//arrival time[i]
	int b[] = {11,28,2,10,16};				//brust time a[i]
	int pr[] = {2,0,3,1,4};					//priority					

	int n = sizeof(a) / sizeof(a[0]);
	vector<process> p(n);					//p = process

	for(int i=0;i<n;++i){					//initializing processid,arrival time and brust time
		p[i].id = i;
		p[i].at = a[i];
		p[i].bt = b[i];
		p[i].pr = pr[i];
	}

	priorityScheduling(p);
	
	return 0;
}
