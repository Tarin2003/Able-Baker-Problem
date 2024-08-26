#include<stdio.h>
#include<conio.h>
int  total_spend_time=0,total_waiting_time=0,wait_count=0,abl_ser_count,baker_ser_count=0,total_IAT=0,total_service_time_able=0,total_service_time_baker=0,p,i,n;
struct simulation{
    int cust_no,rd_ar,intr_arr_time,arr_time,rd_se,ableTSE,bakerTSE,ableTSB,bakerTSB,ableST,bakerST,able_available,baker_available,waiting_time,spend;
    float prob,ableProb,bakerProb;
    int IAT,ableSer,bakerSer;
};

typedef struct simulation Simulation;
void schedule_arrival_time (Simulation s[],int n);
int Able(Simulation s[],int i);
int Baker(Simulation s[],int i);

void main(){
    Simulation s[200];
    float avg_waiting_time,avg_IAT,avg_service_time_able,avg_service_time_baker,
    avg_waiting_time_those_who_wait,Average_time_customer_spends_in_the_system;

    printf(" Enter Time between call : ");
    scanf("%d",&p);
    printf("\n Enter Time Between Arrival : ");
    for(i=1;i<=p;i++){
      scanf("%d",&s[i].IAT);
    }

     printf("\n Enter Probability : ");
    for(i=1;i<=p;i++){
      scanf("%f",&s[i].prob);
    }
     printf("\n Enter Service Time for Able :  ");
      for(i=1;i<=p;i++){
      scanf("%d",&s[i].ableSer);
    }

    printf("\n Enter Probability for Able :   ");
    for(i=1;i<=p;i++){
      scanf("%f",&s[i].ableProb);
    }
    printf("\n Enter Service Time for Baker : ");
    for(i=1;i<=p;i++){
      scanf("%d",&s[i].bakerSer);
    }
    printf("\n Enter Probability for Baker : ");
    for(i=1;i<=p;i++){
      scanf("%f",&s[i].bakerProb);
    }

    printf("\n Enter customer number: ");
    scanf("%d",&n);
    printf(" Warning!! Please Enter RD. around 1-100\n");
    printf(" Enter random digit for arrival time for each customer: \n");

      printf(" RD.Arrival[1]: -\n");
      s[1].cust_no=1;
      s[1].rd_ar=0;
      s[1].intr_arr_time=0;


    for(i=2;i<=n;i++){
        printf(" RD.Arrival[%d]: ",i);
        scanf("%d",&s[i].rd_ar);
        s[i].cust_no=i;
        if(s[i].rd_ar >= 0 && s[i].rd_ar <= 25) s[i].intr_arr_time=1;
        else if(s[i].rd_ar >= 26 && s[i].rd_ar <= 65) s[i].intr_arr_time=2;
        else if(s[i].rd_ar >= 66 && s[i].rd_ar <= 85) s[i].intr_arr_time=3;
        else if(s[i].rd_ar >= 86 && s[i].rd_ar <= 100) s[i].intr_arr_time=4;
    }

    printf(" Warning!! Please Enter RD. around 1-100\n");
    printf(" Enter random digit for service time for each customer: \n");
    for(i=1;i<=n;i++){
        printf(" RD.Service[%d]: ",i);
        scanf("%d",&s[i].rd_se);
        if(s[i].rd_se >=0 && s[i].rd_se <=30){ s[i].ableST=2;}
        if(s[i].rd_se >=0 && s[i].rd_se <=33){ s[i].bakerST=3;
        }
        else if(s[i].rd_se >=31 && s[i].rd_se <=58) { s[i].ableST=3;}
        if(s[i].rd_se >=36 && s[i].rd_se <=60) {s[i].bakerST=4;}
        else if(s[i].rd_se >=59 && s[i].rd_se <=83){ s[i].ableST=4;}
            if(s[i].rd_se >=61 && s[i].rd_se <=80) {s[i].bakerST=5;}
        else if(s[i].rd_se >=84 && s[i].rd_se <=100){ s[i].ableST=5;}
                if(s[i].rd_se >=81 && s[i].rd_se <=100) {s[i].bakerST=6;}
    }

    schedule_arrival_time (s,n);
        //For first customer
        s[1].ableTSB=0;
        s[1].able_available =0;
        s[1].baker_available =0;
       total_service_time_able,abl_ser_count,wait_count,total_spend_time=Able(s,1);

        //for 2 to n customer
      for (i = 2; i <= n; i++) {
            //Able free Time
        if(s[i-1].ableTSE < 0) s[i].able_available= s[i-1].able_available;
		else s[i].able_available = s[i-1].ableTSE;
		// Baker free time
		if(s[i-1].bakerTSE< 0) s[i].baker_available = s[i-1].baker_available;
		else s[i].baker_available = s[i-1].bakerTSE;

       if (s[i].arr_time >= s[i].able_available) {
            s[i].ableTSB = s[i].arr_time;
           total_service_time_able,abl_ser_count,wait_count,total_spend_time,total_waiting_time=Able(s,i);
       }

       else if (s[i].arr_time < s[i].able_available && s[i].able_available<=s[i].baker_available) {
            s[i].ableTSB = s[i].able_available;
            total_service_time_able,abl_ser_count,wait_count,total_spend_time,total_waiting_time=Able(s,i);
       }
       else if (s[i].arr_time >= s[i].baker_available) {
            s[i].bakerTSB = s[i].arr_time;
            total_service_time_baker,baker_ser_count,wait_count,total_spend_time,total_waiting_time=Baker(s,i);
            }

     else if (s[i].arr_time < s[i].baker_available && s[i].baker_available < s[i].able_available) {
            s[i].bakerTSB = s[i].baker_available;
           total_service_time_baker,baker_ser_count,wait_count,total_spend_time,total_waiting_time=Baker(s,i);
           }
    }

    printf("\n Simulation Table : ");
    printf("\n -----------------------------------------------------------------------------------------------------");
    printf("\n  Cust.\tR.D\tIAT\tAT\tR.D\tAble\tAble\tAble\tBaker\tBaker\tBaker\tCaller\tT.S.S \n");
    printf("  No.\tIAT\t  \t  \tS.T \tTSB\tST \tTSE\tTSB\tST\tTSE\tdelay\t  \n");
    printf("\n -----------------------------------------------------------------------------------------------------\n");

    for(i=1; i<=n; i++){

    printf("   %d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t %d\t %d\n"
               ,s[i].cust_no,s[i].rd_ar,s[i].intr_arr_time,s[i].arr_time,s[i].rd_se,s[i].ableTSB,s[i].ableST,
               s[i].ableTSE,s[i].bakerTSB,s[i].bakerST,s[i].bakerTSE,s[i].waiting_time,s[i].spend);
    if(i!=n){
    printf(" -----------------------------------------------------------------------------------------------------\n");
        }
    else{
    printf(" -----------------------------------------------------------------------------------------------------\n");
        }
        }

       avg_waiting_time = (float)total_waiting_time/(float)n;
       avg_IAT = (float)s[n].arr_time/(float)n;
       avg_service_time_able = (float)total_service_time_able/(float)abl_ser_count;
       avg_service_time_baker = (float)total_service_time_baker/(float)baker_ser_count;
       avg_waiting_time_those_who_wait = (float)total_waiting_time/(float)wait_count;

       printf("\n Average waiting time = %.3f",avg_waiting_time);
       printf("\n Average IAT = %.3f",avg_IAT);
       printf("\n Average service time for Able = %.3f",avg_service_time_able);
       printf("\n Average service time for Baker = %.3f",avg_service_time_baker);
       printf("\n Average waiting time of those who wait= %.3f",avg_waiting_time_those_who_wait);
       printf("\n\n");

}

void schedule_arrival_time (Simulation s[],int n){
    int i;
    for( i=2; i<=n; i++){
        s[i].arr_time=s[i-1].arr_time+s[i].intr_arr_time;
    }
}

Able(Simulation s[],int i){
            s[i].bakerTSB = -1;
            s[i].bakerTSE=  -1;
            s[i].bakerST = -1;
    if(s[i].arr_time >= s[i].ableTSB){
        s[i].waiting_time=0;
    }
    else{
     s[i].waiting_time=s[i].ableTSB - s[i].arr_time;
    }
    //Number of customer wait
    if(s[i].waiting_time!=0){
        wait_count=wait_count+1;
    }
    // Count ending Time
    s[i].ableTSE=s[i].ableTSB +  s[i].ableST;

    total_service_time_able =  total_service_time_able + s[i].ableST;
    //Number of customer service from able
    abl_ser_count = abl_ser_count+1;
    s[i].spend = s[i].ableST+s[i].waiting_time;
    total_spend_time = total_spend_time + s[i].spend;total_waiting_time = total_waiting_time + s[i].waiting_time;

    return total_service_time_able,abl_ser_count,wait_count,total_spend_time,total_waiting_time;

}
Baker( Simulation s[],int i){
            s[i].ableTSB = -1;
            s[i].ableTSE=  -1;
            s[i].ableST = -1;

    if(s[i].arr_time >= s[i].bakerTSB){
        s[i].waiting_time=0;
    }
    else{
     s[i].waiting_time=s[i].bakerTSB - s[i].arr_time;
    }
    if(s[i].waiting_time!=0){
        wait_count=wait_count+1;
    }
    s[i].bakerTSE=s[i].bakerTSB +  s[i].bakerST;

    total_service_time_baker = total_service_time_baker+ s[i].bakerST;
    baker_ser_count = baker_ser_count+1;
    s[i].spend = s[i].bakerST+s[i].waiting_time;
    total_spend_time = total_spend_time+ s[i].spend;
    total_waiting_time = total_waiting_time + s[i].waiting_time;
    return total_service_time_baker,baker_ser_count,wait_count,total_spend_time,total_waiting_time;

}











