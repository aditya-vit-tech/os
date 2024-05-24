//bankers algorithm
#include<stdio.h>

int process[5]={0,1,2,3,4};
int allocated[5][3]={
    {0,1,0},
    {2,0,0},
    {3,0,2},
    {2,1,2},
    {0,0,2}
};

int max[5][3]={
    {7,5,3},
    {3,2,2},
    {9,0,2},
    {2,2,2},
    {4,3,3}
};
int work[3]={3,3,2};
int need[5][3];
int finish[5];
int squence[5];
int ind = 0;

void bankers(int m, int n){
    for(int s=0;s<n;s++){
        for(int i=0;i<m;i++){

            if(finish[i]==0){
                if(need[i][0] <= work[0] && need[i][1] <= work[1] && need[i][2] <= work[2]){
                    finish[i] = 1;
                    squence[ind++] = i;
                    for(int k=0;k<n;k++){
                        work[k] =work[k]+allocated[i][k];
                    }
                }
            }
        }
    }
}

int main(){
    int m = 5;
    int n = 3;
    for (int i = 0; i < m; i++){
        finish[i]=0;
    }
    
    // finding need matrix
    for (int i = 0; i < m; i++){
        for(int j=0;j<n;j++){
            need[i][j]=max[i][j] - allocated[i][j];
        }
    }

    bankers( m, n);

    int flag=0;
    // finding if all processes executed succefully by checking flag
    for (int i = 0; i < m; i++){
        if(finish[i] == 0){
            flag = 1;
            break;
        }
    }
    
    if(flag==0){
        printf("Safe state sequence for processes is: \n");
        for (int i = 0; i < m; i++){
            printf("%d -> ", squence[i]);
        }
    }
    else
        printf("System is not safe.");
    
    return 0;
}


//deadlock detection
#include <stdio.h>
int main()
{
	int n, m, i, j, k;
	n = 5; 
	m = 3; 
	int alloc[5][3] = { { 0, 0, 1 }, 
						{ 1, 3, 6 }, 
						{ 9, 5, 1 }, 
						{ 2, 1, 1 }, 
						{ 0, 0, 2 } }; 

	int request[5][3] = { { 0, 0, 0 }, 
					 	  { 0, 0, 0 }, 
						  { 9, 5, 1 }, 
						  { 1, 0, 0 }, 
						  { 0, 0, 2 } }; 
	int avail[3] = { 0, 0, 0 }; 

	int finish[n], ans[n], ind = 0;
	for (k = 0; k < n; k++) {
		if(request[k][0] == 0 && request[k][1] == 0 && request[k][2] == 0){
			finish[k] = 1;
			for(j = 0; j<m; j++)
				avail[j] += alloc[k][j];
		}
		else{
			finish[k] = 0;
		}
	}

	int y = 0;
	for (k = 0; k < 5; k++) {
        int flagie = 1;
		for (i = 0; i < n; i++) {

			 if(finish[i]==0){
                if(request[i][0] <= avail[0] && request[i][1] <= avail[1] && request[i][2] <= avail[2]){
                    finish[i] = 1;
					for(int k=0;k<n;k++){
                        avail[k] =avail[k]+alloc[i][k];
                    }
				}
			 }
		}
        if(flagie == 1)
            break;
	}

	int flag = 1;
	for(int i=0;i<n;i++){
        if(finish[i]==0){
            flag=0;
            printf("The following system causes deadlock\n");           
            break;
        }
	}
    
	if(flag==1){
        printf("System is deadlock free.");
	}

    printf("Processes which causing deadlock are: ");
    for (int i = 0; i < n; i++){
        if(finish[i]==0)
           printf("P%d  ", i);
    }

	return (0);
}

//memory allocation best fit, first fit, next fit, worst fit
#include<stdio.h>

int partitions, processes;


void firstFit(int memory[partitions],int pSize[processes], int allo[partitions], int unallo[partitions]){
    int ind1=0, ind2=0;
    
    for(int i=0;i<processes;i++){
        int flag = 0;
        for(int j=0;j<partitions;j++){
            
            if(pSize[i]<=memory[j]){
                memory[j] = memory[j] - pSize[i];
                allo[ind1++] = i;
                flag=1;
                break;
            }
        }
        if(flag==0){
            unallo[ind2++]=i;
        }
    }

    printf("Processes allocated memory are: \n");
    for(int i=0;i<ind1;i++){
        printf(" P%d ", allo[i]);
    }

    printf("\nProcesses remain unallocated memory are:");
    for(int i=0;i<ind2;i++){
        printf(" P%d ", unallo[i]);
    }
    printf("\n");
}

void nextFit(int memory[partitions], int pSize[processes], int allo[partitions], int unallo[partitions]) {
    int ind1 = 0, ind2 = 0;
    int n = 0, m = 0;
    int lastAllocated = 0; 

    for (int i = 0; i < processes; i++) {
        int start = lastAllocated; // Start searching for the next fit from the last allocated partition
        while (n <= m) {
            if (memory[m] >= pSize[i]) {
                allo[ind1++] = i;
                memory[m] -= pSize[i];
                lastAllocated = m; // Update last allocated partition
                break; // Exit the loop once allocation is done
            }
            m = (m + 1) % partitions;
            // If we have searched all partitions and didn't find a fit, break the loop
            if (m == start) 
                break;
        }
    }

    printf("Processes allocated memory are: \n");
    for (int i = 0; i < ind1; i++) {
        printf(" P%d ", allo[i]);
    }
    printf("\n");
}



void bestFit(int memory[], int pSize[], int allo[], int unallo[]) {
    int ind1 = 0, ind2 = 0;

    for (int i = 0; i < processes; i++) {
        int minSub = 1000; // Initialize the minimum difference to a very large value
        int minIndex = -1; // Initialize the index of the partition with the minimum difference
        
        for (int j = 0; j < partitions; j++) {
            if (memory[j] >= pSize[i]) { // Check if the partition has enough space for the process
                int sub = memory[j] - pSize[i]; // Calculate the difference in memory size
                
                if (sub < minSub) { // Check if this partition has the minimum difference so far
                    minSub = sub;
                    minIndex = j;
                }
            }
        }

        if (minIndex != -1) { // If a suitable partition was found
            memory[minIndex] -= pSize[i]; // Allocate memory for the process
            allo[ind1++] = i; // Update the allocated processes array
        } else {
            unallo[ind2++] = i; // Store unallocated processes
        }
    }

    printf("Processes allocated memory are: \n");
    for (int i = 0; i < ind1; i++) {
        printf(" P%d ", allo[i]);
    }
    printf("\n");

    printf("Unallocated processes are: \n");
    for (int i = 0; i < ind2; i++) {
        printf(" P%d ", unallo[i]);
    }
    printf("\n");
}

void worstFit(int memory[], int pSize[], int allo[], int unallo[]) {
    int ind1=0, ind2=0;
    int max=0;

    for(int i=0;i<processes;i++){
        max=0;
        for(int j=0;j<partitions;j++){
           
            if(memory[j]>memory[max]){
                max = j;
            }
        }
        if(memory[max]>=pSize[i]){
            allo[ind1++] = i;
            memory[max] -=pSize[i];
        }else{
            unallo[ind2++] = i;
        }
    }

    printf("\nMemory allocated to following processes: \n");
    for (int i = 0; i < ind1; i++)
    {
        printf("P%d ", allo[i]);
    }

    printf("\nMemory not allocated to following processes: \n");
    for (int i = 0; i < ind2; i++)
    {
        printf("P%d ", unallo[i]);
    }
    
    printf("\n");
}

int main(){
    
    printf("Enter no. of partitions: ");
    scanf("%d", &partitions);

    int fM[partitions];
    int nM[partitions];
    int bM[partitions];
    int wM[partitions];


    int ffA[partitions], ffUn[partitions];
    int nfA[partitions], nfUn[partitions];
    int bfA[partitions], bfUn[partitions];
    int wfA[partitions], wfUn[partitions];

    
    printf("Enter size of each partition: ");
    for (int i = 0; i < partitions; i++)
    {
        printf("Partition %d", i+1);
        scanf("%d", &fM[i]);
        nM[i] = fM[i];
        bM[i] = fM[i];
        wM[i] = fM[i];
    }

    printf("Enter no. of processes: ");
    scanf("%d", &processes);
    int pSize[processes];

    printf("Enter size of each process: ");
    for (int i = 0; i < processes; i++)
    {
        printf("Size of process %d", i+1);
        scanf("%d", &pSize[i]);
    }    

    printf("\nFirst Fit Memory Allocation Technique: \n");
    firstFit(fM, pSize, ffA, ffUn);

    printf("\nNext fit Memory Allocation Technique: \n");
    nextFit(nM, pSize, nfA, nfUn);

    printf("\nBest First Memory Allocation Technique: \n");
    bestFit(bM, pSize, bfA, bfUn);

    printf("\nWorst First Memory Allocation Technique: \n");
    worstFit(wM, pSize, wfA, wfUn);

    return 0;
}

//page replacement FIFO
#include<stdio.h>

void fifo(int totalPages, int pages[], int frameNo){
    int pointer=0;
    int pageMiss=0, pageHit=0;
    int pageFrame[frameNo];

        
    for (int i = 0; i < frameNo; i++)
    {    
        pageFrame[i] = 999;
    }

    for (int i = 0; i < totalPages; i++){
        int flag =0;

        //check if current item is already in pageframe or not.
        for (int j = 0; j < frameNo; j++){
            if (pageFrame[j]==pages[i]){
                pageHit++;
                flag=1;
                break;
            }
        }
        // if item is not in page frame then take to pageframe and increment page miss.
        if (flag==0)
        {
            pageFrame[pointer]=pages[i];
            pageMiss++;
            pointer= (pointer+1) % frameNo;
        }
    }

    printf("Pagemiss: %d\n", pageMiss);
    printf("PageHit: %d\n", pageHit);
    
}

int main(){
    int total_pages;
    int pages[20];
    int pageFrame;
    printf("Enter total no. of pages: ");
    scanf("%d", &total_pages);

    printf("Enter %d pages: \n",total_pages);
    for (int i = 0; i < total_pages; i++){
        scanf("%d", &pages[i]);
    }    

    printf("Enter size of page frame: ");
    scanf("%d", &pageFrame);

    fifo(total_pages, pages, pageFrame);

    return 0;
}

//LRU
#include<stdio.h>

int findNotRecent(int pageFrame[], int pages[], int index, int total_frames){
  int tempFrame[total_frames];
  int lruind = 0;
  int count = total_frames;
  
  for(int i = 0; i < total_frames; i++){
    tempFrame[i] = pageFrame[i];
  }
  
  for(int i = index; i >= 0; i--){
    for(int k = 0; k < total_frames; k++){
      if(tempFrame[k] == pages[i] && count > 1){
        tempFrame[k] = -1;
        count--;
        break;
      }
    }
  }
  
  for(int i = 0; i < total_frames; i++){
    if(tempFrame[i] >= 0){
      lruind = i;
      break;
    }
  }
  
  return lruind;
}

void optimal(int total_pages, int pages[], int total_frames){
    int pagemiss = 0, pagehit = 0;
    int pageFrame[total_frames];
    int flag;
    
    for (int i = 0; i < total_frames; i++){    
        pageFrame[i] = 999;
    }

    for (int i = 0; i < total_pages; i++){
        flag = 0;

        // page hit if page is already in pageframe
        for (int j = 0; j < total_frames; j++){
            if(pageFrame[j] == pages[i]){
                pagehit++;
                flag = 1;
                break;
            }
        }
        
        // check if page frame is not filled
        if(flag == 0){
            for(int k = 0; k < total_frames; k++){
                if(pageFrame[k] == 999){
                    pageFrame[k] = pages[i];
                    pagemiss++;
                    flag = 1;
                    break;
                }
            }
        }
        
        // find index of not least recently used page and replace it.
        if(flag == 0){
            int pageIndex = findNotRecent(pageFrame, pages, i - 1, total_frames);
            pageFrame[pageIndex] = pages[i];
            pagemiss++;
        }
    }
    
    printf("Page Miss: %d\n", pagemiss);
    printf("Page Hits: %d\n", pagehit);
}

int main(){
    int total_pages;
    int pages[20];
    int pageFrameSize;
    
    printf("Enter total no. of pages: ");
    scanf("%d", &total_pages);

    printf("Enter %d pages: \n", total_pages);
    for (int i = 0; i < total_pages; i++){
        scanf("%d", &pages[i]);
    }    

    printf("Enter size of page frame: ");
    scanf("%d", &pageFrameSize);

    optimal(total_pages, pages, pageFrameSize);

    return 0;
}

//optimal
#include<stdio.h>

int findNotRecent(int pageFrame[], int pages[], int index, int totalPages, int total_frames){
  int tempFrame[total_frames];
  int optind = 0;
  int count = total_frames;
  
  for(int i = 0; i < total_frames; i++){
    tempFrame[i] = pageFrame[i];
  }
  
  // checking which page is being not used in near future.
  for(int i = index; i < totalPages; i++){
    for(int k = 0; k < total_frames; k++){
      if(tempFrame[k] == pages[i] && count > 1){
        tempFrame[k] = -1;
        count--;
        break;
      }
    }
  }
  
  // checking index of which 1 page is remaining in page frame
  for(int i = 0; i < total_frames; i++){
    if(tempFrame[i] >= 0){
      optind = i;
      break;
    }
  }
  
  return optind;
}

void optimal(int total_pages, int pages[], int total_frames){
    int pagemiss = 0, pagehit = 0;
    int pageFrame[total_frames];
    int flag;
    
    for (int i = 0; i < total_frames; i++){    
        pageFrame[i] = 999;
    }

    for (int i = 0; i < total_pages; i++){
        flag = 0;

        // page hit if page is already in pageframe
        for (int j = 0; j < total_frames; j++){
            if(pageFrame[j] == pages[i]){
                pagehit++;
                flag = 1;
                break;
            }
        }
        
        // check if page frame is not filled
        if(flag == 0){
            for(int k = 0; k < total_frames; k++){
                if(pageFrame[k] == 999){
                    pageFrame[k] = pages[i];
                    pagemiss++;
                    flag = 1;
                    break;
                }
            }
        }
        
        // find index of not least recently used page and replace it.
        if(flag == 0){
            int pageIndex = findNotRecent(pageFrame, pages, i - 1, total_pages, total_frames);
            pageFrame[pageIndex] = pages[i];
            pagemiss++;
        }
    }
    
    printf("Page Miss: %d\n", pagemiss);
    printf("Page Hits: %d\n", pagehit);
}

int main(){
    int total_pages;
    int pages[20];
    int pageFrameSize;
    
    printf("Enter total no. of pages: ");
    scanf("%d", &total_pages);

    printf("Enter %d pages: \n", total_pages);
    for (int i = 0; i < total_pages; i++){
        scanf("%d", &pages[i]);
    }    

    printf("Enter size of page frame: ");
    scanf("%d", &pageFrameSize);

    optimal(total_pages, pages, pageFrameSize);

    return 0;
}

//scheduling FCFS
#include<stdio.h>

struct process
{
    int id;
    int AT;
    int BT;
    int FT;
    int TT;
    int WT;
    int burstRemaining;
};

int processes[]={0,1,2,3,4};
int AT[]={0,2,4,6,8};
int BT[]={3,6,4,5,2};

int ready[10];
int time_c=0;
int gantt[20] = {0};
int top=0;
int gt=0;
int total_burst;
int rear=-1, front=-1;
int curr=-1;

struct process p[4];

void enque(int q[], int *f, int *r, int p){

    if((*f) ==-1 && (*r) == -1 ){
        (*f)=0;
        (*r)=0;
    }

    q[(*r)] = p;
    (*r)++;

}

int deque(int q[], int *f, int *r){

    if((*f) > (*r) ){
        printf("Empty Queue.");
        return -1;
    }

    return q[(*f)++];
}

void fcfs(){

    while (time_c!=total_burst){

        for (int i = 0; i < 5; i++)
        {
            if( p[i].AT == time_c ){
                enque(ready, &front, &rear, p[i].id);
            }
        }

        if(p[curr].burstRemaining == 0 || curr==-1){
            curr = deque(ready, &front, &rear);
        }

        gantt[time_c] = curr;
        p[curr].burstRemaining--;

        if (p[curr].burstRemaining == 0) {
            p[curr].FT = time_c + 1; // Add 1 to account for the current time unit
        }

        time_c++;
    }
}

void calculate_waiting_time() {
  for (int i = 0; i < 5; i++) {
    p[i].WT = p[i].FT - p[i].AT - p[i].BT;
  }
}

void calculate_turnaround_time() {
  for (int i = 0; i < 5; i++) {
    p[i].TT = p[i].WT + p[i].BT;
  }
}

int main(){

    int total_wt=0 ,total_tt=0;

    for(int i=0;i<5;i++){
        p[i].id=processes[i];
        p[i].AT = AT[i];
        p[i].burstRemaining = BT[i];
        p[i].BT = BT[i];
    }

    printf("Id  AT  BT \n");
    for (int i = 0; i <= 4; i++){
        printf("%d %3d %3d\n", p[i].id, p[i].AT, p[i].BT);
        total_burst+=p[i].BT;
    }

    fcfs();

    printf("\nReady Queue:\n");
    for (int i = 0; i < 5; i++){
        printf("%d ", ready[i]);
    }

    printf("\nGantt Chart:\n");
    for (int i = 0; i < 20; i++){
        printf("%d ", gantt[i]);
    }

     calculate_turnaround_time();
    calculate_waiting_time();

      printf("\nId  AT  BT  FT  TT  WT \n");
  for (int i = 0; i <= 4; i++) {
    printf("%d %3d %3d %3d %3d %3d\n", p[i].id, p[i].AT, p[i].burstRemaining, p[i].FT, p[i].TT, p[i].WT);
    total_wt+=p[i].WT;
    total_tt += p[i].TT;
  }

  printf("Average waiting time: %d\n", total_wt/5);
  printf("Average turnaround time: %d\n", total_tt/5);

    return 0;
}

//priority non preempt
#include<stdio.h>

struct process
{
    int id;
    int AT;
    int burstRemaining;
    int BT;
    int p;
    int FT;
    int WT;
    int TT;
};

int processes[]={0,1,2,3,4};
int AT[]={0,2,8,6,4};
int BT[]={3,6,4,5,2};
int pri[]={5,4,3,2,1};

int ready[10];
int time_c=0;
int gantt[20] = {0};
int top=0;
int gt=0;
int total_burst;

struct process p[4];

void insert_ready(int id){
    if (p[id].burstRemaining == 0)
        return;
    ready[top]= id;
    top++;
}

void delete_ready(int hi_id){
    for (int i = 0; i < top; i++){
        if (ready[i] == hi_id) {
            for (int j = i; j < top - 1; j++)
                ready[j] = ready[j + 1];
            top--;
            break;
        }
    }
}

int high_priority(){
    int min_pri = 999; 
    int pid = -1; 
    for(int i=0;i<top;i++){
        if (p[ready[i]].AT <= time_c && p[ready[i]].p < min_pri && p[ready[i]].burstRemaining!=0){
            min_pri = p[ready[i]].p;
            pid = ready[i];
        }
    }
    return pid;
}

void pr_nonpreempt(){
    while (1){
        if(time_c == total_burst)
            break;

        for(int i=0;i<5;i++){
            if(time_c == p[i].AT && p[i].burstRemaining!=0){
                insert_ready(p[i].id);
            }
        }

        int hi_id = high_priority();

        for (int i = p[hi_id].burstRemaining; i > 0; i--)
        {
            gantt[time_c]=hi_id;
            time_c++;
            p[hi_id].burstRemaining--;

            if (p[hi_id].burstRemaining == 0) {
                p[hi_id].FT = time_c;
            }
         
            for(int i=0;i<5;i++){
                if(time_c == p[i].AT && p[i].burstRemaining!=0){
                    insert_ready(p[i].id);
                }
            }
        }
    }
}

void calculate_waiting_time() {
  for (int i = 0; i < 5; i++) {
    p[i].WT = p[i].FT - p[i].AT - p[i].BT;
  }
}

void calculate_turnaround_time() {
  for (int i = 0; i < 5; i++) {
    p[i].TT = p[i].WT + p[i].BT;
  }
}

int main(){

    int total_wt=0 ,total_tt=0;

    for(int i=0;i<5;i++){
        p[i].id=processes[i];
        p[i].AT = AT[i];
        p[i].burstRemaining = BT[i];
        p[i].p = pri[i];
        p[i].BT = BT[i];
    }

    printf("Id  AT  BT  Pri\n");
    for (int i = 0; i <= 4; i++){
        printf("%d %2d %2d %2d\n", p[i].id, p[i].AT, p[i].burstRemaining, p[i].p);
        total_burst+=p[i].burstRemaining;
    }

    pr_nonpreempt();

    printf("\nGantt Chart:\n");
    for (int i = 0; i < 20; i++){
        printf("%d ", gantt[i]);
    }

     calculate_turnaround_time();
    calculate_waiting_time();

    printf("\nId  AT  BT  FT  TT  WT \n");
    
    for (int i = 0; i <= 4; i++) {
        printf("%d %3d %3d %3d %3d %3d\n", p[i].id, p[i].AT, p[i].BT, p[i].FT, p[i].TT, p[i].WT);
        total_wt+=p[i].WT;
        total_tt += p[i].TT;
  }

  printf("Average waiting time: %d\n", total_wt/5);
  printf("Average turnaround time: %d\n", total_tt/5);

    return 0;
}

// priority preemptive
#include<stdio.h>

struct process
{
    int id;
    int AT;
    int burstRemaining;
    int p;
    int BT;
    int FT;
    int TT;
    int WT;
};

int processes[]={0,1,2,3,4};
int AT[]={0,2,4,6,8};
int BT[]={3,6,4,5,2};
int pri[]={5,4,3,2,1};

int ready[10];
int time_c=0;
int gantt[20] = {0};
int top=0;
int gt=0;

struct process p[4];

void insert_ready(int id){
    if (p[id].burstRemaining == 0)
        return;
    ready[top]= id;
    top++;
}

void delete_ready(int hi_id){
    for (int i = 0; i < top; i++){
        if (ready[i] == hi_id) {
            for (int j = i; j < top - 1; j++)
                ready[j] = ready[j + 1];
            top--;
            break;
        }
    }
}

int high_priority(){
    int min_pri = 999; 
    int pid = -1; 
    for(int i=0;i<top;i++){
        if (p[ready[i]].AT <= time_c && p[ready[i]].p < min_pri){
            min_pri = p[ready[i]].p;
            pid = ready[i];
        }
    }
    return pid;
}

void pr_preempt(){
    while (1){
        if(time_c > 21)
            break;

// insert new process into ready queue
        for(int i=0;i<5;i++){
            if(time_c == p[i].AT)
                insert_ready(p[i].id);
        }

// find out the process with highest priority from read queue
        int hi_id = high_priority();
        if (hi_id != -1)
            delete_ready(hi_id);

        gantt[time_c] = hi_id;
        if (hi_id != -1)
            p[hi_id].burstRemaining--;

        if (p[hi_id].burstRemaining == 0) {
                p[hi_id].FT = time_c+1; // Update finish time
            }

        time_c++;
        if (hi_id != -1)
            insert_ready(hi_id);
    }
}

void calculate_waiting_time() {
  for (int i = 0; i < 5; i++) {
    p[i].WT = p[i].FT - p[i].AT - p[i].BT;
  }
}

void calculate_turnaround_time() {
  for (int i = 0; i < 5; i++) {
    p[i].TT = p[i].WT + p[i].BT;
  }
}

int main(){

    int total_wt=0 ,total_tt=0;

    for(int i=0;i<5;i++){
        p[i].id=processes[i];
        p[i].AT = AT[i];
        p[i].burstRemaining = BT[i];
        p[i].p = pri[i];
        p[i].BT = BT[i];
    }

    printf("Id  AT  BT  Pri\n");
    for (int i = 0; i < 4; i++){
        printf("%d %2d %2d %2d\n", p[i].id, p[i].AT, p[i].burstRemaining, p[i].p);
    }

    pr_preempt();

    printf("\nGantt Chart:\n");
    for (int i = 0; i < 20; i++){
        printf("%d ", gantt[i]);
    }

     calculate_turnaround_time();
    calculate_waiting_time();

    printf("\nId  AT  BT  FT  TT  WT \n");
    
    for (int i = 0; i <= 4; i++) {
        printf("%d %3d %3d %3d %3d %3d\n", p[i].id, p[i].AT, p[i].BT, p[i].FT, p[i].TT, p[i].WT);
        total_wt+=p[i].WT;
        total_tt += p[i].TT;
  }

  printf("Average waiting time: %d\n", total_wt/5);
  printf("Average turnaround time: %d\n", total_tt/5);


    return 0;
}

//round robit
#include<stdio.h>

struct process
{
    int id;
    int AT;
    int burstRemaining;
};

int processes[] = {0, 1, 2, 3, 4};
int AT[] = {0, 2, 4, 6, 8};
int BT[] = {3, 6, 4, 5, 2};

int ready[10];
int time_c = 0;
int gantt[20] = {0};
int top = 0;
int gt = 0;
int total_burst;
int curr = -1;
int iterate = 0;
int ct = 0;
int rd_pc = 0;

struct process p[4];

void insert_ready(int id) {
    if (p[id].burstRemaining == 0)
        return;
    ready[top] = id;
    top++;
}

void delete_ready(int hi_id) {
    for (int i = 0; i < top; i++) {
        if (ready[i] == hi_id) {
            for (int j = i; j < top - 1; j++)
                ready[j] = ready[j + 1];
            top--;
            break;
        }
    }
}

void pr_nonpreempt() {
    while (time_c != total_burst) {

        for (int i = 0; i < 5; i++) {
            if (p[i].AT == time_c) {
                insert_ready(i);
                rd_pc++;
            }
        }

        if (ct >= 2 || p[curr].burstRemaining <= 0) {
            int next_process = iterate % rd_pc;
            curr = ready[next_process];
            iterate++;
            ct = 0;
        }

        gantt[time_c] = curr;

         if (p[curr].burstRemaining <= 0 && curr!=-1) {
            delete_ready(curr);
            rd_pc--;
        }
    
        p[curr].burstRemaining--;
        ct++;
        time_c++;
    }
}

int main() {
    for (int i = 0; i < 5; i++) {
        p[i].id = processes[i];
        p[i].AT = AT[i];
        p[i].burstRemaining = BT[i];
    }

    printf("Id  AT  BT\n");
    for (int i = 0; i < 5; i++) {
        printf("%d %3d %3d\n", p[i].id, p[i].AT, p[i].burstRemaining);
        total_burst += p[i].burstRemaining;
    }

    pr_nonpreempt();

    printf("\nGantt Chart:\n");
    for (int i = 0; i < total_burst; i++) {
        printf("%d ", gantt[i]);
    }

    return 0;
}

//SJF
#include<stdio.h>

struct process
{
    int id;
    int AT;
    int burstRemaining;
    int FT;
    int TT;
    int WT;
    int burstRemaining;
};

int processes[]={0,1,2,3,4};
int AT[]={0,2,4,6,8};
int BT[]={3,6,4,5,2};

int ready[10];
int time_c=0;
int gantt[20] = {0};
int top=0;
int gt=0;
int total_burst;
int curr=-1;

struct process p[4];

void insert_ready(int id){
    if (p[id].burstRemaining == 0)
        return;
    ready[top]= id;
    top++;
}

void delete_ready(int hi_id){
    for (int i = 0; i < top; i++){
        if (ready[i] == hi_id) {
            for (int j = i; j < top - 1; j++)
                ready[j] = ready[j + 1];
            top--;
            break;
        }
    }
}

int shorest_job(){
    int min_pri = 999; 
    int pid = -1; 
    for(int i=0;i<top;i++){
        if (p[ready[i]].AT <= time_c && p[ready[i]].burstRemaining < min_pri && p[ready[i]].burstRemaining!=0){
            min_pri = p[ready[i]].burstRemaining;
            pid = ready[i];
        }
    }
    return pid;
}

void pr_nonpreempt(){
    while (time_c!=total_burst)
    {

        for(int i=0;i<5;i++){
            if(p[i].AT==time_c){
                insert_ready(i);
            }
        }

        if(p[curr].burstRemaining == 0 || curr==-1){
            curr = shorest_job();
            delete_ready(curr);
        }

        printf("Shortest Job: %d", curr);
        gantt[time_c] = curr;
        time_c++;
        p[curr].burstRemaining--;

        if (p[curr].burstRemaining == 0) {
            p[curr].FT = time_c;
        }
    }
}

void calculate_waiting_time() {
  for (int i = 0; i < 5; i++) {
    p[i].WT = p[i].FT - p[i].AT - p[i].burstRemaining;
  }
}

void calculate_turnaround_time() {
  for (int i = 0; i < 5; i++) {
    p[i].TT = p[i].WT + p[i].burstRemaining;
  }
}

int main(){

    int total_wt=0, total_tt=0;

    for(int i=0;i<5;i++){
        p[i].id=processes[i];
        p[i].AT = AT[i];
        p[i].burstRemaining = BT[i];
        p[i].burstRemaining=BT[i];
    }

    printf("Id  AT  BT\n");
    for (int i = 0; i <= 4; i++){
        printf("%d %3d %3d\n", p[i].id, p[i].AT, p[i].burstRemaining);
        total_burst+=p[i].burstRemaining;
    }

    pr_nonpreempt();

    printf("\nGantt Chart:\n");
    for (int i = 0; i < 20; i++){
        printf("%d ", gantt[i]);
    }

    calculate_turnaround_time();
    calculate_waiting_time();

      printf("\nId  AT  BT  FT  TT  WT \n");
  for (int i = 0; i <= 4; i++) {
    printf("%d %3d %3d %3d %3d %3d\n", p[i].id, p[i].AT, p[i].burstRemaining, p[i].FT, p[i].TT, p[i].WT);
    total_wt+=p[i].WT;
    total_tt += p[i].TT;
  }

  printf("Average waiting time: %d\n", total_wt/5);
  printf("Average turnaround time: %d\n", total_tt/5);


    return 0;
}


//SRTF
#include <stdio.h>

struct process {
  int id;
  int AT;
  int burstRemaining;
  int remaining_BT; // Track remaining burst time for preemption
  int FT;
  int WT;
  int TT;
};

int processes[] = {0, 1, 2, 3, 4};
int AT[] = {0, 2, 4, 6, 8};
int BT[] = {3, 6, 4, 5, 2};

int ready[10];
int time_c = 0;
int gantt[20] = {0};
int top = 0;
int gt = 0;
int total_burst;
int curr = -1;
int avg_wt;
int avg_tt;

struct process p[5];

void insert_ready(int id) {
  if (p[id].burstRemaining == 0) {
    return;
  }
  ready[top] = id;
  top++;
}

void delete_ready(int hi_id) {
  for (int i = 0; i < top; i++) {
    if (ready[i] == hi_id) {
      for (int j = i; j < top - 1; j++) {
        ready[j] = ready[j + 1];
      }
      top--;
      break;
    }
  }
}

int shortest_job() {
  int min_BT = 999;
  int pid = -1;
  for (int i = 0; i < top; i++) {
    if (p[ready[i]].AT <= time_c && p[ready[i]].remaining_BT < min_BT && p[ready[i]].remaining_BT != 0) {
      min_BT = p[ready[i]].remaining_BT;
      pid = ready[i];
    }
  }
  return pid;
}

void pr_preemptive() {
  while (time_c != total_burst) {
    // Check for arriving processes
    for (int i = 0; i < 5; i++) {
      if (p[i].AT == time_c) {
        insert_ready(i);
      }
    }

    // Preemption logic: Check for shorter jobs among arrived processes
    if (curr != -1 && ready[0] != -1) {
      int next_job = shortest_job();
      if (next_job != -1 && p[next_job].remaining_BT < p[curr].remaining_BT) {
        // Preempt the current process and add it back to the ready queue
        p[curr].remaining_BT += time_c - p[curr].AT; // Update remaining BT for later execution
        delete_ready(curr);
        insert_ready(curr);
        curr = next_job;
        delete_ready(curr);
      }
    }

    if (curr == -1) {
      curr = shortest_job();
      if (curr == -1) {
        // No processes in ready queue, skip to next time unit
        time_c++;
        continue;
      }
      delete_ready(curr);
    }

    gantt[time_c] = curr;
    p[curr].remaining_BT--;
    time_c++;

     if (p[curr].remaining_BT == 0) {
      p[curr].FT = time_c; // Update finish time
      curr = -1; // Process completed, clear current proces
    }
  }
}

void calculate_waiting_time() {
  for (int i = 0; i < 5; i++) {
    p[i].WT = p[i].FT - p[i].AT - p[i].burstRemaining;
  }
}

void calculate_turnaround_time() {
  for (int i = 0; i < 5; i++) {
    p[i].TT = p[i].WT + p[i].burstRemaining;
  }
}

int main() {

    int total_wt=0, total_tt=0;

  for (int i = 0; i < 5; i++) {
    p[i].id = processes[i];
    p[i].AT = AT[i];
    p[i].burstRemaining = BT[i];
    p[i].remaining_BT = BT[i]; // Initialize remaining_BT for preemption
  }

  printf("Id  AT  BT\n");
  for (int i = 0; i <= 4; i++) {
    printf("%d %3d %3d\n", p[i].id, p[i].AT, p[i].burstRemaining);
    total_burst += p[i].burstRemaining;
  }

  pr_preemptive();

    printf("\nGantt Chart:\n");
    for (int i = 0; i < 20; i++){
        printf("%d ", gantt[i]);
    }

      p[1].FT=20;
    calculate_turnaround_time();
    calculate_waiting_time();

      printf("\nId  AT  BT  FT  TT  WT \n");
  for (int i = 0; i <= 4; i++) {
    printf("%d %3d %3d %3d %3d %3d\n", p[i].id, p[i].AT, p[i].burstRemaining, p[i].FT, p[i].TT, p[i].WT);
    total_wt+=p[i].WT;
    total_tt += p[i].TT;
  }

  printf("Average waiting time: %d\n", total_wt/5);
  printf("Average turnaround time: %d\n", total_tt/5);

    return 0;
}


//dining philosopher
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t room;
sem_t chopstick[5];

void * philosopher(void *);
void eat(int);
int main()
{
	int i,a[5];
	pthread_t tid[5];
	
	sem_init(&room,0,4);
	
	for(i=0;i<5;i++)
		sem_init(&chopstick[i],0,1);
		
	for(i=0;i<5;i++){
		a[i]=i;
		pthread_create(&tid[i],NULL,philosopher,(void *)&a[i]);
	}
	for(i=0;i<5;i++)
		pthread_join(tid[i],NULL);
}

void * philosopher(void * num){
	int phil=*(int *)num;

	sem_wait(&room);
	printf("\nPhilosopher %d has entered room",phil);
	sem_wait(&chopstick[phil]);
	sem_wait(&chopstick[(phil+1)%5]);

	eat(phil);
	sleep(2);
	printf("\nPhilosopher %d has finished eating",phil);

	sem_post(&chopstick[(phil+1)%5]);
	sem_post(&chopstick[phil]);
	sem_post(&room);
}

void eat(int phil){
	printf("\nPhilosopher %d is eating",phil);
}

//producer consumer
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFFER_SIZE 5
typedef struct {
int buf[BUFFER_SIZE];
size_t len;
pthread_mutex_t mutex;
pthread_cond_t can_produce;
pthread_cond_t can_consume;
} buffer_t;
void *producer(void *arg) {
buffer_t *buffer = (buffer_t *)arg;
while (1) {
#ifdef UNDERFLOW
sleep(5);
#endif
pthread_mutex_lock(&buffer->mutex);
if (buffer->len == BUFFER_SIZE) {
pthread_cond_wait(&buffer->can_produce, &buffer->mutex);
}
int t = rand();
printf("Produced %d\n ", t);
buffer->buf[buffer->len] = t;
++buffer->len;
pthread_cond_signal(&buffer->can_consume);
pthread_mutex_unlock(&buffer->mutex);
printf("FULL: %ld\n", buffer->len);
printf("Empty: %ld\n", (BUFFER_SIZE - buffer->len));
}
return NULL;
}
void *consumer(void *arg) {
buffer_t *buffer = (buffer_t *)arg;
while (1) {
#ifdef OVERFLOW
sleep(5);
#endif
pthread_mutex_lock(&buffer->mutex);
if (buffer->len == 0) {
pthread_cond_wait(&buffer->can_consume, &buffer->mutex);
}
--buffer->len;
printf("Consumed %d\n", buffer->buf[buffer->len]);
pthread_cond_signal(&buffer->can_produce);
pthread_mutex_unlock(&buffer->mutex);
printf("FULL: %ld\n", buffer->len);
printf("Empty: %ld\n", (BUFFER_SIZE - buffer->len));
}
return NULL;
}
int main(int argc, char *argv[]) {
buffer_t buffer = {
.len = 0,
.mutex = PTHREAD_MUTEX_INITIALIZER,
.can_produce = PTHREAD_COND_INITIALIZER,
.can_consume = PTHREAD_COND_INITIALIZER};
pthread_t prod, cons;
pthread_create(&prod, NULL, producer, (void *)&buffer);
pthread_create(&cons, NULL, consumer, (void *)&buffer);
pthread_join(prod, NULL);
pthread_join(cons, NULL);
return 0;
}

//reader writer
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
sem_t mutex, writeblock;
int data = 0, rcount = 0;
void *reader(void *arg) {
int f;
f = *((int *)arg);
sem_wait(&mutex);
rcount++;
if (rcount == 1) {
sem_wait(&writeblock);
}
sem_post(&mutex);
printf("Reader %d is reading data: %d\n", f, data);
sleep(2);
sem_wait(&mutex);
rcount--;
if (rcount == 0) {
sem_post(&writeblock);
}
sem_post(&mutex);
return NULL;
}
void *writer(void *arg) {
int f;
f = *((int *)arg);
sem_wait(&writeblock);
data++;
printf("Data Written By The Writer: %d\n", data);
sleep(1);
sem_post(&writeblock);
return NULL;
}
int main() {
int i;
pthread_t rtid[3], wtid[3];
sem_init(&mutex, 0, 1);
sem_init(&writeblock, 0, 1);
while (1) {
for (i = 0; i < 3; i++) {
pthread_create(&wtid[i], NULL, writer, &i);
pthread_create(&rtid[i], NULL, reader, &i);
}
for (i = 0; i < 3; i++) {
pthread_join(wtid[i], NULL);
pthread_join(rtid[i], NULL);
}
sleep(5); // Delay for 5 seconds before running the loop again
printf("\n\n");
}
return 0;
}
