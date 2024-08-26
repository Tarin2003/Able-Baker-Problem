#include<stdio.h>
#include<conio.h>
int total_waiting_time=0,total_idle_time=0,wait_count=0;
struct simulation{
    int cust_no;
    int rd_ar;
    int intr_arr_time;
    int arr_time;
    int rd_se;
    int service_begin;
    int service_time;
    int time_ser_end;
    int waiting_time;
    int idle_time;
    int spend;

};
typedef struct simulation Simulation;

void schedule_arrival_time (Simulation s[],int n);
void schedule_service_begin_time (Simulation s[],int n);
void schedule_end_of_service (Simulation s[],int n);
int waiting_and_idle_time (Simulation s[],int n);
int schedule_spend_time(Simulation s[],int n);

void main(){

    //freopen("result.txt", "r", stdin);
    //freopen("result.txt", "w", stdout);

    Simulation s[200];
    int i,j,n,total_service_time=0;
    float avg_waiting_time,probability_wait,probability_of_idle_server,avg_service_time,avg_time_btn_arrival,
    avg_waiting_time_those_who_wait,Average_time_customer_spends_in_the_system;
    printf(" Enter customer number: ");
    scanf("%d",&n);
      printf(" Warning!! Please Enter RD. around 1-1000\n");
    printf(" Enter random digit for arrival time for each customer: \n");
    for(i=1;i<2;i++){
      printf("  RD.Arrival[1]: -\n");
      s[i].cust_no=1;
      s[i].rd_ar=0;
      s[i].intr_arr_time=0;
    }

    for(i=2;i<=n;i++){
        printf("  RD.Arrival[%d]: ",i);
        scanf("%d",&s[i].rd_ar);
        s[i].cust_no=i;
        if(s[i].rd_ar >= 0 && s[i].rd_ar <= 125) s[i].intr_arr_time=1;
        else if(s[i].rd_ar >= 126 && s[i].rd_ar <= 250) s[i].intr_arr_time=2;
        else if(s[i].rd_ar >= 251 && s[i].rd_ar <= 375) s[i].intr_arr_time=3;
        else if(s[i].rd_ar >= 376 && s[i].rd_ar <= 500) s[i].intr_arr_time=4;
        else if(s[i].rd_ar >= 501 && s[i].rd_ar <= 625) s[i].intr_arr_time=5;
        else if(s[i].rd_ar >= 626 && s[i].rd_ar <= 750) s[i].intr_arr_time=6;
        else if(s[i].rd_ar >= 751 && s[i].rd_ar <= 875) s[i].intr_arr_time=7;
        else if(s[i].rd_ar >= 876 && s[i].rd_ar <= 1000) s[i].intr_arr_time=8;

    }

    schedule_arrival_time( s, n);
    printf(" Warning!! Please Enter RD. around 1-100\n");
    printf(" Enter random digit for service time for each customer: \n");
    for(i=1;i<2;i++){
      s[i].service_begin=0;
    }

    for(i=1;i<=n;i++){
        printf("  RD.Service[%d]: ",i);
        scanf("%d",&s[i].rd_se);
        if(s[i].rd_se > 0 && s[i].rd_se < 11) s[i].service_time=1;
        else if(s[i].rd_se > 10 && s[i].rd_se < 31) s[i].service_time=2;
        else if(s[i].rd_se > 30 && s[i].rd_se < 61) s[i].service_time=3;
        else if(s[i].rd_se > 60 && s[i].rd_se < 86) s[i].service_time=4;
        else if(s[i].rd_se > 85 && s[i].rd_se < 96) s[i].service_time=5;
        else if(s[i].rd_se > 95 && s[i].rd_se < 101) s[i].service_time=6;

        total_service_time+=s[i].service_time;

    }
    schedule_service_begin_time( s, n);
    schedule_end_of_service( s, n);
    schedule_service_begin_time( s, n);
    schedule_end_of_service( s, n);

    waiting_and_idle_time( s, n);
   int total_spend_time = schedule_spend_time(s, n);



    printf("\n  ------------------------------------------------------------------------------------------------------------------------------");
    printf("\n  |Cust.| RD. for | Inter_arrival| Arrival | RD. for | Service  | T.Service | Waiting |T.Service| Time Spend      | Idle time of|\n");
    printf("  | No. |Arrival.T| Time(IAT)    | Time(AT)|Service.T|  Time(ST)| Begin(TSB)| Time(WT)|ends(TSE)| in a system(TSS)| server(IOS) |");
    printf("\n  ------------------------------------------------------------------------------------------------------------------------------\n");
    for(i=1; i<=n; i++){

        printf("     %d\t  %d\t     %d\t           %d\t      %d\t     %d\t    %d\t       %d\t     %d\t        %d\t            %d\n"
               ,s[i].cust_no,s[i].rd_ar,s[i].intr_arr_time,s[i].arr_time,s[i].rd_se,s[i].service_time,s[i].service_begin,
               s[i].waiting_time,s[i].time_ser_end,s[i].spend,s[i].idle_time);
    if(i!=n){
    printf("  -------------------------------------------------------------------------------------------------------------------------------\n");
        }
        else{
            printf("  -------------------------------------------------------------------------------------------------------------------------------\n");
        }
        }


    avg_waiting_time = (float)total_waiting_time/(float)n;
    probability_wait = (float)wait_count/(float)n;
    probability_of_idle_server = (float)total_idle_time/(float)s[n].time_ser_end;
    avg_service_time = (float)total_service_time/(float)n;
    avg_time_btn_arrival = (float)s[n].arr_time/(float)(n-1);
    avg_waiting_time_those_who_wait = (float)total_waiting_time/(float)wait_count;
    Average_time_customer_spends_in_the_system = (float)total_spend_time/(float)n;
    printf("\n Average waiting time = %.2f",avg_waiting_time);
    printf("\n Probability customer has to wait in queue = %.2f",probability_wait);
    printf("\n Probability of idle time = %.2f",probability_of_idle_server);
    printf("\n Average service time = %.2f",avg_service_time);
    printf("\n Average time between arrival= %.2f",avg_time_btn_arrival);
    printf("\n Average waiting time of those who wait= %.2f",avg_waiting_time_those_who_wait);
    printf("\n Average time customer spends in the system= %.2f",Average_time_customer_spends_in_the_system);
printf("\n\n\n\n");
    return 0;

}
void schedule_arrival_time (Simulation s[],int n){
    int i;
    for( i=2; i<=n; i++){
        s[i].arr_time=s[i-1].arr_time+s[i].intr_arr_time;
    }
}
void schedule_service_begin_time (Simulation s[],int n){
    int i;
    for( i=2; i<=n; i++){
            if(s[i].arr_time > s[i-1].time_ser_end){
                s[i].service_begin=s[i].arr_time;
            }
            else{
                s[i].service_begin=s[i-1].time_ser_end;
            }
    }
}
void schedule_end_of_service (Simulation s[],int n){
    int i;
    for( i=1; i<=n; i++){
        s[i].time_ser_end=s[i].service_begin+s[i].service_time;
    }
}
int waiting_and_idle_time (Simulation s[],int n ){
    int i;
    s[1].waiting_time=0;
    s[1].idle_time=0;
    for( i=2; i<=n; i++){
            if(s[i].arr_time > s[i-1].time_ser_end){
                s[i].idle_time=s[i].arr_time-s[i-1].time_ser_end;
                total_idle_time+=s[i].idle_time;
                s[i].waiting_time=0;
            }
            else{
                s[i].waiting_time=s[i-1].time_ser_end-s[i].arr_time;
                total_waiting_time+=s[i].waiting_time;
                s[i].idle_time=0;
            }
            if(s[i].waiting_time!=0){
                wait_count=wait_count+1;
            }

    }

}
int schedule_spend_time (Simulation s[],int n){
    int i,aa, total_spend_time=0;
    for(i=1;i<=n;i++)
    {
        s[i].spend = s[i].service_time+s[i].waiting_time;
        total_spend_time+=s[i].spend;

    }
    return total_spend_time;


}


