#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <cstdio>
#include <ctime>
#include <cstring>
#include <graphics.h>

using namespace std;


//function to give space in the console after any function
void Clr(){
    for(int i=0;i<3;i++)
        {
            cout<<" "<<endl;
        }
}


//function to change the balance after adding an income or expense
//input is the value to be added or subtracted from balance
void Balance_change(int input){
    //first the balance is read and stored in the variable prev_balance
    int prev_balance=0;
    int sal,sal_date,check1=0,check2=0;
    char reader[10],balance[5],salary[5],date1[5];
    FILE* read;
    read=fopen("details.txt","r");
    if(read==NULL)
        {
            cout<<"File error"<<endl;
            return;
        }
    else
        {
            fgets(reader,10,read);
            int k=0;
            while((balance[k]=reader[k])!='\n'){k++;}
            balance[k]='\0';
            sscanf(balance,"%d",&prev_balance);
            int j=0,i=0;
            if(fgets(reader,10,read))
                {
                    while((salary[j]=reader[i])!=','){i++;j++;}
                    salary[j]='\0';j=0;i++;
                    sscanf(salary,"%d",&sal);
                    while((date1[j]=reader[i])!='\0'){i++;j++;}
                    date1[j]='\0';
                    sscanf(date1,"%i",&sal_date);
                }
            fclose(read);
        }
    FILE* change_balance;//Defining pointer
    change_balance=fopen("details.txt","w");
    if(change_balance==NULL)//To checck if file succesfully opened
        {
            cout<<"Error updating Balance"<<endl;
            return;
        }
    else
        {
            int curr_balance;//stores balance after update
            cout<<"previous balance: "<<prev_balance<<endl;
            curr_balance=prev_balance+input;
            cout<<"current balance: "<<curr_balance<<endl;
            fprintf(change_balance,"%d\n%i,%i",curr_balance,sal,sal_date);//writing to file
            fclose(change_balance);
        }
}


//Function to show balance
void Balance(){
    int balance=0;//to store the balance from file
    ifstream reader;//Defining pointer
    reader.open ("details.txt");
    if (reader.is_open())//Verifying if file is open
        {
            reader>>balance;
            cout<<"Your current balance is "<<balance<<endl;
            reader.close();
        }
    else {cout<<"Error reading balance"<<endl;}
}


void Set_salary(){
    int sal,pr_date,pr_bal;char input[10],balance[5];
    cout<<"Enter the salary for monthly update"<<endl;
    cin>>sal;
    cout<<"Enter the date of receiving salary"<<endl;
    while(1)
        {
            cin>>pr_date;
            if((1<=pr_date)&&(pr_date<=31)){break;}
            else {cout<<"Invalid input";}
        }
    FILE* read;
    read=fopen("details.txt","r");
    if(read==NULL)
        {
            cout<<"File error"<<endl;
            return;
        }
    else
        {
            fgets(input,10,read);
            int k=0;
            while((balance[k]=input[k])!='\0'){k++;}
            balance[k]='\0';
            sscanf(balance,"%d",&pr_bal);
            fclose(read);
        }
    FILE* write;
    write=fopen("details.txt","w");
    if(write==NULL)
        {
            cout<<"File error"<<endl;
            return;
        }
    else
        {
            fprintf(write,"%d\n%d,%i",pr_bal,sal,pr_date);
            cout<<"Salary updated successfully"<<endl;
            Clr();
            cout<<"Salary: "<<sal<<"    Date: "<<pr_date<<endl;
            fclose(write);
        }
    return;
}


void Check_salary(){
    int sal,sal_date,check1=0,check2=1;
    char input[10],balance[5],salary[5],date1[5];
    char date[3],month[3],year[3],source[20],amount[3];
    int ch_month,ch_year;
    char ch_name[]="salary";
    time_t rawtime;
    time(&rawtime);
    struct tm* timeinfo;
    timeinfo=localtime(&rawtime);
    int curr_month;
    curr_month=timeinfo->tm_mon+1;
    int curr_year;
    curr_year=timeinfo->tm_year+1900;
    FILE* salary_check;
    salary_check=fopen("income.txt","r");
    if(salary_check==NULL)
        {
            cout<<"File Error"<<endl;
            return;
        }
    else
        {
            while(fgets(input,40,salary_check))
                {
                    int i=0,j=0;
                    while((date[j]=input[i])!=','){i++; j++;}
                    date[j]='\0'; j=0; i++;
                    while((month[j]=input[i])!=','){i++; j++;}
                    month[j]='\0'; j=0; i++;
                    sscanf(month,"%i",&ch_month);
                    while((year[j]=input[i])!=','){i++; j++;}
                    year[j]='\0'; j=0; i++;
                    sscanf(year,"%i",&ch_year);
                    while((source[j]=input[i])!=','){i++; j++;}
                    source[j]='\0';j=0; i++;
                    while((amount[j]=input[i])!='\0'){i++; j++;}
                    amount[j]='\0';
                    if(curr_month==ch_month&&curr_year==ch_year&&strcmp(source,ch_name)==0){check2=0;}
                }
            fclose(salary_check);
        }
    FILE* read;
    read=fopen("details.txt","r");
    if(read==NULL)
        {
            cout<<"File error"<<endl;
            return;
        }
    else
        {
            fgets(input,10,read);
            int k=0;
            while((balance[k]=input[k])!='\n'){k++;}
            balance[k]='\0';
            int j=0,i=0;
            if(fgets(input,10,read))
                {
                    while((salary[j]=input[i])!=','){i++;j++;}
                    salary[j]='\0';j=0;i++;
                    sscanf(salary,"%d",&sal);
                    while((date1[j]=input[i])!='\0'){i++;j++;}
                    date1[j]='\0';
                    sscanf(date1,"%i",&sal_date);
                }
            else check1=1;
            fclose(read);
        }
    if(check1){return;}
    if(check2)
        {
            FILE* salary_check;
            salary_check=fopen("income.txt","a");
            if(salary_check==NULL)
                {
                    cout<<"File Error"<<endl;
                    return;
                }
            else
                {
                    fprintf(salary_check,"%i,%i,%i,%s,%d\n",sal_date,curr_month,curr_year,ch_name,sal);
                    cout<<"Salary added for this month"<<endl;
                    Balance_change(sal);
                    fclose(salary_check);
                }
        }
}


//function to add income
void Add_Income(){
    //defining a structure to store the parts of income
    struct inc
        {
            int amount;
            char source[40];
        };
    inc sample;
    FILE* income_input;
    income_input=fopen("income.txt","a");
    if(income_input==NULL)//check for file opening
        {
            cout<<"Error adding the income"<<endl;
            return;
        }
    else
        {
            cout<<"Enter the source of income(dont use space)"<<endl;
            cin>>sample.source;
            cout<<"Enter the amount received"<<endl;
            cin>>sample.amount;
            time_t rawtime;
            time(&rawtime);
            struct tm* timeinfo;
            timeinfo=localtime(&rawtime);
            int month;
            month=timeinfo->tm_mon+1;
            int year;
            year=timeinfo->tm_year+1900;
            Clr();
            fprintf(income_input,"%i,%i,%i,%s,%d\n",timeinfo->tm_mday,month,year,sample.source,sample.amount);//wrting to file
            cout<<"Income added succesfully"<<endl;
            printf("%s\t%d\n",sample.source,sample.amount);//giving output of what was added
            fclose(income_input);
            Balance_change(sample.amount);//calling function to update balance by the amount added
        }
}


//Function to show income
void Show_Income(){
    char input[40];//variable for reading file
    int n=1;//variable to number the list
    char date[3],month[3],year[3],source[20],amount[3];
    //header text for visual appeal
    cout<<"_______________________________________________________________________________"<<endl;
    cout<<"    Income list "<<endl;
    cout<<"_______________________________________________________________________________"<<endl;
    cout<<"Sr.no.   date      source             amount"<<endl;
    FILE* income_show;// pointer for file
    income_show=fopen("income.txt","r");
    if(income_show==NULL)//file open check
        {
            cout<<"First add an income to show "<<endl;
            return;
        }
    else
        {
            while(fgets(input,40,income_show))
                {
                    cout<<"  "<<n<<"    ";
                    n++;
                    int i=0,j=0;
                    while((date[j]=input[i])!=','){i++; j++;}
                    date[j]='\0'; j=0; i++;
                    cout<<date<<'/';
                    while((month[j]=input[i])!=','){i++; j++;}
                    month[j]='\0'; j=0; i++;
                    cout<<month<<'/';
                    while((year[j]=input[i])!=','){i++; j++;}
                    year[j]='\0'; j=0; i++;
                    cout<<year<<"   ";
                    while((source[j]=input[i])!=','){i++; j++;}
                    source[j]='\0';
                    cout<<source;
                    for(int i=0;i<20-j;i++){cout<<" ";}
                    j=0; i++;
                    while((amount[j]=input[i])!='\0'){i++; j++;}
                    amount[j]='\0';
                    cout<<amount;
                }
        }
    fclose(income_show);
}


void Income(){
    cout<<"Give the number of what you want to do: "<<endl;
    cout<<"1. Add Income"<<endl;
    cout<<"2. Show Income"<<endl;
    int command;
    cin>>command;
    switch(command)
        {
            case 1:
                {
                    Add_Income();
                    break;
                }
            case 2:
                {
                    Show_Income();
                    break;
                }

        }
}


//Function to add expenses
void Add_Expense(){
    //Function to add expense is similar to adding income
    struct exp//To store the parts of expense
        {
            int amount;
            char receiver[40];
        };
    exp sample;
    FILE* expense_input;
    expense_input=fopen("expense.txt","a");
    if(expense_input==NULL)//File open check
        {
            cout<<"Error adding an expense"<<endl;
            return;
        }
    else
        {
            //Selection of category of expense and input
            cout<<" "<<endl;
            cout<<"Select category of expense :"<<endl;
            cout<<"1. Food"<<endl;
            cout<<"2. Transport"<<endl;
            cout<<"3. Clothing"<<endl;
            cout<<"4. Stationery & Household"<<endl;
            cout<<"5. Mobile"<<endl;
            cout<<"6. Other"<<endl;
            int category;
            cin>>category;
            cout<<" "<<endl;
            cout<<"Enter to whom was money given or for what money was given(dont use space)"<<endl;
            cin>>sample.receiver;
            cout<<"Enter the amount given"<<endl;
            cin>>sample.amount;
            //reading time from system
            time_t rawtime;
            time(&rawtime);
            struct tm* timeinfo;
            timeinfo=localtime(&rawtime);
            int month;
            month=timeinfo->tm_mon+1;
            int year;
            year=timeinfo->tm_year+1900;
            Clr();
            //writing to file
            fprintf(expense_input,"%i,%i,%i,%i,%s,%d\n",category,timeinfo->tm_mday,month,year,sample.receiver,sample.amount);
            cout<<"Expense added succesfully"<<endl;
            printf("%s\t%d\t\n",sample.receiver,sample.amount);
            fclose(expense_input);
            Balance_change(-sample.amount);//negative is put as it is an expense and balance has to be subtracted
        }
}


//Function to show expenses
void Show_Expense(){
    //selection of viewing preference
    cout<<" "<<endl;
    cout<<"1. Show all expenses"<<endl;
    cout<<"2. Show expenses of a particular category"<<endl;
    cout<<"3. Show expenses of a particular month"<<endl;
    cout<<"4. Show bar graph of monthly expenses"<<endl;
    cout<<"5. Show bar graph of category wise expenses"<<endl;
    int command;
    cin>>command;
    switch(command)
        {
            case 1:
                {
                    //similar to function for showing income
                    char input[40];//variable for reading file
                    int n=1;//variable to number the list
                    char date[3],month[3],year[3],receiver[20],amount[3],category[3];//variables to store details
                    //header text for visual appeal
                    cout<<"_______________________________________________________________________________"<<endl;
                    cout<<"    Expenses list "<<endl;
                    cout<<"_______________________________________________________________________________"<<endl;
                    cout<<"Sr.no.   date      receiver             amount"<<endl;
                    FILE* expense_show;// pointer for file
                    expense_show=fopen("expense.txt","r");
                    if(expense_show==NULL)//file open check
                        {
                            cout<<"First add an expense to show "<<endl;
                            return;
                        }
                    else
                        {
                            while(fgets(input,40,expense_show))//File reading and output
                                {
                                    cout<<"  "<<n<<"    ";
                                    n++;
                                    int i=0,j=0;
                                    while((category[j]=input[i])!=','){i++;j++;}
                                    category[j]='\0';j=0;i++;
                                    while((date[j]=input[i])!=','){i++; j++;}
                                    date[j]='\0'; j=0; i++;
                                    cout<<date<<'/';
                                    while((month[j]=input[i])!=','){i++; j++;}
                                    month[j]='\0'; j=0; i++;
                                    cout<<month<<'/';
                                    while((year[j]=input[i])!=','){i++; j++;}
                                    year[j]='\0'; j=0; i++;
                                    cout<<year<<"   ";
                                    while((receiver[j]=input[i])!=','){i++; j++;}
                                    receiver[j]='\0';
                                    cout<<receiver;
                                    for(int i=0;i<22-j;i++){cout<<" ";}
                                    j=0; i++;
                                    while((amount[j]=input[i])!='\0'){i++; j++;}
                                    amount[j]='\0';
                                    cout<<amount;
                                }
                        }
                    fclose(expense_show);//cosing file
                    break;
                }
            case 2:
                {
                    //Selection of category to view
                    cout<<" "<<endl;
                    cout<<"Select Category :"<<endl;
                    cout<<"1. Food"<<endl;
                    cout<<"2. Transport"<<endl;
                    cout<<"3. Clothing"<<endl;
                    cout<<"4. Stationery & Household"<<endl;
                    cout<<"5. Mobile"<<endl;
                    cout<<"6. Other"<<endl;
                    int req_category;
                    cin>>req_category;
                    cout<<" "<<endl;
                    int cat=0;
                    char input[40];//variable for reading file
                    int n=1;//variable to number the list
                    char date[3],month[3],year[3],receiver[20],amount[3],category[3];//variables to store details
                    //header text for visual appeal
                    cout<<"_______________________________________________________________________________"<<endl;
                    cout<<"    Expenses list "<<endl;
                    cout<<"_______________________________________________________________________________"<<endl;
                    cout<<"Sr.no.   date      receiver             amount"<<endl;
                    FILE* expense_show;// pointer for file
                    expense_show=fopen("expense.txt","r");
                    if(expense_show==NULL)//file open check
                        {
                            cout<<"First add an expense to show "<<endl;
                            return;
                        }
                    else
                        {
                            while(fgets(input,40,expense_show))//reading file and output
                                {
                                    int i=0,j=0;
                                    while((category[j]=input[i])!=','){i++;j++;}
                                    category[j]='\0';j=0;i++;
                                    sscanf(category,"%i",&cat);
                                    if(req_category!=cat){continue;}
                                    cout<<"  "<<n<<"    ";
                                    n++;
                                    while((date[j]=input[i])!=','){i++; j++;}
                                    date[j]='\0'; j=0; i++;
                                    cout<<date<<'/';
                                    while((month[j]=input[i])!=','){i++; j++;}
                                    month[j]='\0'; j=0; i++;
                                    cout<<month<<'/';
                                    while((year[j]=input[i])!=','){i++; j++;}
                                    year[j]='\0'; j=0; i++;
                                    cout<<year<<"   ";
                                    while((receiver[j]=input[i])!=','){i++; j++;}
                                    receiver[j]='\0';
                                    cout<<receiver;
                                    for(int i=0;i<22-j;i++){cout<<" ";}
                                    j=0; i++;
                                    while((amount[j]=input[i])!='\0'){i++; j++;}
                                    amount[j]='\0';
                                    cout<<amount;
                                }
                        }
                    fclose(expense_show);//closing file
                    break;
                }
            case 3:
                {
                    //selection of month to view
                    cout<<" "<<endl;
                    cout<<"Enter the month (ex: for jan -> '1';for nov -> '11')"<<endl;
                    int req_mon;
                    cin>>req_mon;
                    cout<<" "<<endl;
                    char input[40];//variable for reading file
                    int n=1;//variable to number the list
                    char date[3],month[3],year[3],receiver[20],amount[3],category[3];//variables to store details
                    int mon=0;char output[20];
                    //header text for visual appeal
                    cout<<"_______________________________________________________________________________"<<endl;
                    cout<<"    Expenses list "<<endl;
                    cout<<"_______________________________________________________________________________"<<endl;
                    cout<<"Sr.no.   date      receiver             amount"<<endl;
                    FILE* expense_show;// pointer for file
                    expense_show=fopen("expense.txt","r");
                    if(expense_show==NULL)//file open check
                        {
                            cout<<"First add an expense to show "<<endl;
                            return;
                        }
                    else
                        {
                            while(fgets(input,40,expense_show))//reading file and output
                                {
                                    int i=0,j=0;
                                    while((category[j]=input[i])!=','){i++;j++;}
                                    category[j]='\0';j=0;i++;
                                    while((date[j]=input[i])!=','){i++; j++;}
                                    date[j]='\0'; j=0; i++;
                                    while((month[j]=input[i])!=','){i++; j++;}
                                    month[j]='\0'; j=0; i++;
                                    sscanf(month,"%i",&mon);
                                    if(req_mon!=mon){continue;}
                                    while((year[j]=input[i])!=','){i++; j++;}
                                    year[j]='\0'; j=0; i++;
                                    while((receiver[j]=input[i])!=','){i++; j++;}
                                    receiver[j]='\0';
                                    sscanf(receiver,"%s",output);
                                    int k=j;j=0; i++;
                                    while((amount[j]=input[i])!='\0'){i++; j++;}
                                    amount[j]='\0';
                                    cout<<"  "<<n<<"    ";
                                    n++;
                                    cout<<date<<'/';
                                    cout<<mon<<'/';
                                    cout<<year<<"   ";
                                    cout<<output;
                                    for(int i=0;i<22-k;i++){cout<<" ";}
                                    cout<<amount;
                                }
                        }
                    fclose(expense_show);//closing file
                    break;
                }
            case 4:
                {
                    char input[40];//variable to read file
                    //variables to store details read from file
                    char date[3],month[3],year[3],receiver[20],amount[3],category[3];
                    int mon=0,amt=0;float dv=1.0,maxamt=0;int amtlen[12];float pr_amtlen[12];char c_amtlen[12][5];
                    for(int k=0;k<12;k++){amtlen[k]=0;}//initialising values
                    FILE* expense_read;//defining file pointer
                    expense_read=fopen("expense.txt","r");
                    if(expense_read==NULL)//file open check
                        {
                            cout<<"File Error"<<endl;
                            return;
                        }
                    else
                        {
                            while(fgets(input,40,expense_read))//reading file and storing values
                                {
                                    int i=0,j=0;
                                    while((category[j]=input[i])!=','){i++;j++;}
                                    category[j]='\0';j=0;i++;
                                    while((date[j]=input[i])!=','){i++; j++;}
                                    date[j]='\0'; j=0; i++;
                                    while((month[j]=input[i])!=','){i++; j++;}
                                    month[j]='\0'; j=0; i++;
                                    sscanf(month,"%i",&mon);
                                    while((year[j]=input[i])!=','){i++; j++;}
                                    year[j]='\0'; j=0; i++;
                                    while((receiver[j]=input[i])!=','){i++; j++;}
                                    receiver[j]='\0';j=0; i++;
                                    while((amount[j]=input[i])!='\0'){i++; j++;}
                                    amount[j]='\0';
                                    sscanf(amount,"%d",&amt);
                                    amtlen[mon-1]=amtlen[mon-1]+amt;
                                }
                            fclose(expense_read);//closing reading file
                        }
                    for(int k=0;k<12;k++)
                        {
                            sprintf(c_amtlen[k],"%d",amtlen[k]);//converting string to integer values
                            if(amtlen[k]>maxamt){maxamt=amtlen[k];}//finding maximum amount
                        }
                    int z;
                    z=maxamt/1000;
                    dv=450.0/1000*(1+z);//to standardize graph scale
                    for(int k=0;k<12;k++)
                        {
                            pr_amtlen[k]=(524.0-(amtlen[k]*dv));//storing co-ordinate of lengths
                        }
                    initwindow(1000,600,"Expenses-monthly");//opening graph window and printing the graphs
                    settextstyle(SANS_SERIF_FONT,HORIZ_DIR,2);
                    setcolor(WHITE);
                    setlinestyle(SOLID_LINE,0,2);
                    //creating the lines
                    line(100,525,100,60);
                    line(100,525,920,525);
                    line(90,70,100,60);
                    line(110,70,100,60);
                    line(910,515,920,525);
                    line(910,535,920,525);
                    //writing extra info
                    outtextxy(450,575,"Months");
                    outtextxy(95,35,"Y");
                    outtextxy(940,515,"X");
                    outtextxy(80,520,"O");
                    outtextxy(880,10,"press any key");
                    outtextxy(880,30,"to exit graph");
                    //printing respective month bar graph
                    setfillstyle(INTERLEAVE_FILL,BLUE);
                    bar(125,pr_amtlen[0],165,524);
                    outtextxy(130,530,"Jan");
                    outtextxy(130,pr_amtlen[0]-25,c_amtlen[0]);
                    setfillstyle(INTERLEAVE_FILL,RED);
                    bar(190,pr_amtlen[1],230,524);
                    outtextxy(195,530,"Feb");
                    outtextxy(195,pr_amtlen[1]-25,c_amtlen[1]);
                    setfillstyle(INTERLEAVE_FILL,GREEN);
                    bar(255,pr_amtlen[2],295,524);
                    outtextxy(260,530,"Mar");
                    outtextxy(260,pr_amtlen[2]-25,c_amtlen[2]);
                    setfillstyle(INTERLEAVE_FILL,MAGENTA);
                    bar(320,pr_amtlen[3],360,524);
                    outtextxy(325,530,"Apr");
                    outtextxy(325,pr_amtlen[3]-25,c_amtlen[3]);
                    setfillstyle(INTERLEAVE_FILL,BROWN);
                    bar(385,pr_amtlen[4],425,524);
                    outtextxy(390,530,"May");
                    outtextxy(390,pr_amtlen[4]-25,c_amtlen[4]);
                    setfillstyle(INTERLEAVE_FILL,BLUE);
                    bar(450,pr_amtlen[5],490,524);
                    outtextxy(455,530,"Jun");
                    outtextxy(455,pr_amtlen[5]-25,c_amtlen[5]);
                    setfillstyle(INTERLEAVE_FILL,RED);
                    bar(515,pr_amtlen[6],555,524);
                    outtextxy(520,530,"Jul");
                    outtextxy(520,pr_amtlen[6]-25,c_amtlen[6]);
                    setfillstyle(INTERLEAVE_FILL,GREEN);
                    bar(580,pr_amtlen[7],620,524);
                    outtextxy(585,530,"Aug");
                    outtextxy(585,pr_amtlen[7]-25,c_amtlen[7]);
                    setfillstyle(INTERLEAVE_FILL,MAGENTA);
                    bar(645,pr_amtlen[8],685,524);
                    outtextxy(650,530,"Sep");
                    outtextxy(650,pr_amtlen[8]-25,c_amtlen[8]);
                    setfillstyle(INTERLEAVE_FILL,BROWN);
                    bar(710,pr_amtlen[9],750,524);
                    outtextxy(715,530,"Oct");
                    outtextxy(715,pr_amtlen[9]-25,c_amtlen[9]);
                    setfillstyle(INTERLEAVE_FILL,BLUE);
                    bar(775,pr_amtlen[10],815,524);
                    outtextxy(780,530,"Nov");
                    outtextxy(780,pr_amtlen[10]-25,c_amtlen[10]);
                    setfillstyle(INTERLEAVE_FILL,RED);
                    bar(840,pr_amtlen[11],880,524);
                    outtextxy(845,530,"Dec");
                    outtextxy(845,pr_amtlen[11]-25,c_amtlen[11]);
                    getch();//wait for char input to close
                    closegraph();//closing graph window
                    break;
                }
            case 5:
                {
                    char input[40];//variable to read file
                    //variables to store the requires details
                    char date[3],month[3],year[3],receiver[20],amount[3],category[3];
                    int cat=0,amt=0;float dv=1.0,maxamt=0;int amtlen[6];float pr_amtlen[6];char c_amtlen[6][5];
                    for(int k=0;k<6;k++){amtlen[k]=0;}//intialising
                    FILE* expense_read;//defining file pointer
                    expense_read=fopen("expense.txt","r");
                    if(expense_read==NULL)//file open check
                        {
                            cout<<"File Error"<<endl;
                            return;
                        }
                    else
                        {
                            while(fgets(input,40,expense_read))//reading file and storing values
                                {
                                    int i=0,j=0;
                                    while((category[j]=input[i])!=','){i++;j++;}
                                    category[j]='\0';j=0;i++;
                                    sscanf(category,"%i",&cat);
                                    while((date[j]=input[i])!=','){i++; j++;}
                                    date[j]='\0'; j=0; i++;
                                    while((month[j]=input[i])!=','){i++; j++;}
                                    month[j]='\0'; j=0; i++;
                                    while((year[j]=input[i])!=','){i++; j++;}
                                    year[j]='\0'; j=0; i++;
                                    while((receiver[j]=input[i])!=','){i++; j++;}
                                    receiver[j]='\0';j=0; i++;
                                    while((amount[j]=input[i])!='\0'){i++; j++;}
                                    amount[j]='\0';
                                    sscanf(amount,"%d",&amt);
                                    amtlen[cat-1]=amtlen[cat-1]+amt;
                                }
                            fclose(expense_read);//closing reading file
                        }
                    for(int k=0;k<6;k++)
                        {
                            sprintf(c_amtlen[k],"%d",amtlen[k]);//converting string to integer values
                            if(amtlen[k]>maxamt){maxamt=amtlen[k];}//finding largest amount
                        }
                    int z;
                    z=maxamt/1000;
                    dv=450.0/1000*(1+z);//to standardize graph scale
                    for(int k=0;k<6;k++)
                        {
                            pr_amtlen[k]=(524.0-(amtlen[k]*dv));//storing co-ordinates to plot
                        }
                    initwindow(1000,600,"Expenses-category wise");//opening graph window
                    settextstyle(SANS_SERIF_FONT,HORIZ_DIR,2);
                    setcolor(WHITE);
                    setlinestyle(SOLID_LINE,0,2);
                    //drawing lines
                    line(100,525,100,60);
                    line(100,525,920,525);
                    line(90,70,100,60);
                    line(110,70,100,60);
                    line(910,515,920,525);
                    line(910,535,920,525);
                    //writing text
                    outtextxy(450,575,"Categories");
                    outtextxy(95,35,"Y");
                    outtextxy(940,515,"X");
                    outtextxy(80,520,"O");
                    outtextxy(880,10,"press any key");
                    outtextxy(880,30,"to exit graph");
                    //drawing respective category graphs
                    setfillstyle(INTERLEAVE_FILL,BLUE);
                    bar(125,pr_amtlen[0],185,524);
                    outtextxy(130,530,"Food");
                    outtextxy(130,pr_amtlen[0]-25,c_amtlen[0]);
                    setfillstyle(INTERLEAVE_FILL,RED);
                    bar(235,pr_amtlen[1],295,524);
                    outtextxy(220,530,"Transport");
                    outtextxy(240,pr_amtlen[1]-25,c_amtlen[1]);
                    setfillstyle(INTERLEAVE_FILL,GREEN);
                    bar(345,pr_amtlen[2],405,524);
                    outtextxy(340,530,"Clothing");
                    outtextxy(350,pr_amtlen[2]-25,c_amtlen[2]);
                    setfillstyle(INTERLEAVE_FILL,MAGENTA);
                    bar(455,pr_amtlen[3],515,524);
                    outtextxy(440,530,"Stationery &");
                    outtextxy(445,550,"Household");
                    outtextxy(460,pr_amtlen[3]-25,c_amtlen[3]);
                    setfillstyle(INTERLEAVE_FILL,BROWN);
                    bar(565,pr_amtlen[4],625,524);
                    outtextxy(568,530,"Mobile");
                    outtextxy(570,pr_amtlen[4]-25,c_amtlen[4]);
                    setfillstyle(INTERLEAVE_FILL,BLUE);
                    bar(675,pr_amtlen[5],735,524);
                    outtextxy(670,530,"Others");
                    outtextxy(680,pr_amtlen[5]-25,c_amtlen[5]);
                    getch();//waiting for character input to close window
                    closegraph();//closing window
                    break;
                }
            default://for random input
                {
                    cout<<"Invalid Input"<<endl;
                    break;
                }
        }//closing switch
}


//call for functionality
void Expense(){
    //selection of what to do
    cout<<" "<<endl;
    cout<<"Give the number of what you want to do: "<<endl;
    cout<<"1. Add Expense"<<endl;
    cout<<"2. Show Expenses"<<endl;
    int command;
    cin>>command;
    switch(command)//calling respective function
        {
            case 1:
                {
                    Add_Expense();
                    break;
                }
            case 2:
                {
                    Show_Expense();
                    break;
                }

        }
}


//Function to show the taken loan
void Show_loan_taken(){
    cout<<" "<<endl;
    //similar to function for showing income
    char input[40];//variable for reading file
    int n=1;//variable to number the list
    char date[3],month[3],year[3],source[20],amount[3];//variable to store details
    //header text for visual appeal
    cout<<"_______________________________________________________________________________"<<endl;
    cout<<"    Loan taken list "<<endl;
    cout<<"_______________________________________________________________________________"<<endl;
    cout<<"Sr.no.   source             amount         date"<<endl;
    FILE* loan_taken_show;// pointer for file
    loan_taken_show=fopen("loan_taken.txt","r");
    if(loan_taken_show==NULL)//file open check
        {
            cout<<"No loans taken yet "<<endl;
            return;
        }
    else
        {
            while(fgets(input,40,loan_taken_show))//Reading file and output
                {
                    cout<<"  "<<n<<"      ";
                    n++;
                    int i=0,j=0;
                    while((source[j]=input[i])!=','){i++; j++;}
                    source[j]='\0';
                    cout<<source;
                    for(int k=0;k<20-j;k++){cout<<" ";}
                    j=0;i++;
                    while((amount[j]=input[i])!=','){i++; j++;}
                    amount[j]='\0'; j=0; i++;
                    cout<<amount<<"        ";
                    while((date[j]=input[i])!=','){i++; j++;}
                    date[j]='\0'; j=0; i++;
                    cout<<date<<"/";
                    while((month[j]=input[i])!=','){i++; j++;}
                    month[j]='\0';
                    cout<<month<<"/";j=0; i++;
                    while((year[j]=input[i])!='\0'){i++; j++;}
                    year[j]='\0';
                    cout<<year;
                }
        }
    fclose(loan_taken_show);//closing file
}


//Function to show loan given
void Show_loan_given(){
    cout<<" "<<endl;
    //similar to function for showing income
    char input[40];//variable for reading file
    int n=1;//variable to number the list
    char date[3],month[3],year[3],receiver[20],amount[3];//variable to store details
    //header text for visual appeal
    cout<<"_______________________________________________________________________________"<<endl;
    cout<<"    Loan given list "<<endl;
    cout<<"_______________________________________________________________________________"<<endl;
    cout<<"Sr.no.   receiver             amount         date"<<endl;
    FILE* loan_given_show;// pointer for file
    loan_given_show=fopen("loan_given.txt","r");
    if(loan_given_show==NULL)//file open check
        {
            cout<<"No loans given yet "<<endl;
            return;
        }
    else
        {
            while(fgets(input,40,loan_given_show))//Reading file and output
                {
                    cout<<"  "<<n<<"      ";
                    n++;
                    int i=0,j=0;
                    while((receiver[j]=input[i])!=','){i++; j++;}
                    receiver[j]='\0';
                    cout<<receiver;
                    for(int k=0;k<22-j;k++){cout<<" ";}
                    j=0;i++;
                    while((amount[j]=input[i])!=','){i++; j++;}
                    amount[j]='\0'; j=0; i++;
                    cout<<amount<<"        ";
                    while((date[j]=input[i])!=','){i++; j++;}
                    date[j]='\0'; j=0; i++;
                    cout<<date<<"/";
                    while((month[j]=input[i])!=','){i++; j++;}
                    month[j]='\0';
                    cout<<month<<"/";j=0; i++;
                    while((year[j]=input[i])!='\0'){i++; j++;}
                    year[j]='\0';
                    cout<<year;
                }
        }
    fclose(loan_given_show);//closing file
}


//Loan functionality call
void Loan(){
    //Selection for specific function
    cout<<" "<<endl;
    cout<<"Give the numer of what you want to do :"<<endl;
    cout<<"1. Add loan taken"<<endl;
    cout<<"2. Add loan given"<<endl;
    cout<<"3. Show loan to collect"<<endl;
    cout<<"4. Show loan to repay"<<endl;
    cout<<"5. Clear loan"<<endl;
    int command;
    cin>>command;//Selection from user
    cout<<" "<<endl;
    switch(command)
        {
            case 1:
                {
                    //defining a structure to store the parts of the loan
                    struct loan
                        {
                            int amount;
                            char source[40];
                        };
                    loan sample;
                    FILE* loan_taken_input;
                    loan_taken_input=fopen("loan_taken.txt","a");
                    if(loan_taken_input==NULL)//check for file opening
                        {
                            cout<<"Error adding the loan"<<endl;
                            return;
                        }
                    else
                        {
                            cout<<"Enter the source of loan(dont use space)"<<endl;
                            cin>>sample.source;
                            cout<<"Enter the amount received"<<endl;
                            cin>>sample.amount;
                            time_t rawtime;
                            time(&rawtime);
                            struct tm* timeinfo;
                            timeinfo=localtime(&rawtime);
                            int month;
                            month=timeinfo->tm_mon+1;
                            int year;
                            year=timeinfo->tm_year+1900;
                            Clr();
                            fprintf(loan_taken_input,"%s,%d,%i,%i,%i\n",sample.source,sample.amount,timeinfo->tm_mday,month,year);//wrting to file
                            cout<<"Loan added succesfully"<<endl;
                            printf("%s\t%d\t\n",sample.source,sample.amount);//giving output of what was added
                            fclose(loan_taken_input);
                            Balance_change(sample.amount);//calling function to update balance by tthe amount added
                        }
                    break;
                }
            case 2:
                {
                    //defining a structure to store the parts of income
                    struct loan
                        {
                            int amount;
                            char source[40];
                        };
                    loan sample;
                    FILE* loan_given_input;
                    loan_given_input=fopen("loan_given.txt","a");
                    if(loan_given_input==NULL)//check for file opening
                        {
                            cout<<"Error adding the loan"<<endl;
                            return;
                        }
                    else
                        {
                            cout<<"Enter to whom is loan given(dont use space)"<<endl;
                            cin>>sample.source;
                            cout<<"Enter the amount given"<<endl;
                            cin>>sample.amount;
                            time_t rawtime;
                            time(&rawtime);
                            struct tm* timeinfo;
                            timeinfo=localtime(&rawtime);
                            int month;
                            month=timeinfo->tm_mon+1;
                            int year;
                            year=timeinfo->tm_year+1900;
                            Clr();
                            fprintf(loan_given_input,"%s,%d,%i,%i,%i\n",sample.source,sample.amount,timeinfo->tm_mday,month,year);//wrting to file
                            cout<<"Loan added succesfully"<<endl;
                            printf("%s\t%d\t\n",sample.source,sample.amount);//giving output of what was added
                            fclose(loan_given_input);
                            Balance_change(-sample.amount);//calling function to update balance by tthe amount added
                        }
                    break;
                }
            case 3:
                {
                    Show_loan_given();
                    Clr();
                    break;
                }
            case 4:
                {
                    Show_loan_taken();
                    Clr();
                    break;
                }
            case 5:
                {
                    cout<<"1. Clear a loan taken"<<endl;
                    cout<<"2. Clear a loan given"<<endl;
                    int command;
                    cin>>command;
                    switch(command)
                        {
                            case 1:
                                {
                                    Show_loan_taken();
                                    cout<<" "<<endl;
                                    cout<<"Whom do you want to repay : "<<endl;
                                    char clear_source[20];
                                    cin>>clear_source;
                                    char test[20];
                                    char input[80];
                                    char date[3],month[3],year[3],source[20],amount[3];
                                    int date1,month1,year1,amount1; char source1[20];
                                    FILE* loan_taken;
                                    loan_taken=fopen("loan_taken.txt","r");
                                    if(loan_taken==NULL)
                                        {
                                            cout<<"Error reading file"<<endl;
                                            return;
                                        }
                                    else
                                        {
                                            while(fgets(input,80,loan_taken))
                                                {
                                                    int i=0,j=0;
                                                    while((source[j]=input[i])!=','){i++; j++;}
                                                    source[j]='\0';
                                                    sscanf(source,"%s",test);
                                                    j=0; i++;
                                                    while((amount[j]=input[i])!=','){i++; j++;}
                                                    amount[j]='\0'; j=0; i++;
                                                    while((date[j]=input[i])!=','){i++; j++;}
                                                    date[j]='\0'; j=0; i++;
                                                    while((month[j]=input[i])!=','){i++; j++;}
                                                    month[j]='\0';j=0;i++;
                                                    while((year[j]=input[i])!='\0'){i++; j++;}
                                                    year[j]='\0';
                                                    if(strcmp(clear_source,test)==0){break;}
                                                }
                                        }
                                    fclose(loan_taken);
                                    if(strcmp(clear_source,test)!=0){cout<<"name doesnt match"<<endl;break;}
                                    cout<<" "<<endl;
                                    cout<<"Amount to be given is "<<amount<<endl;
                                    cout<<"Press y to continue or n to stop"<<endl;
                                    char check;
                                    cin>>check;
                                    switch(check)
                                        {
                                            case 'y':
                                                {
                                                    int bal=0;
                                                    sscanf(amount,"%d",&bal);
                                                    Balance_change(-bal);
                                                    FILE* file1;
                                                    FILE* file2;
                                                    file1=fopen("loan_taken.txt","r");
                                                    if(file1==NULL)
                                                        {
                                                            cout<<"Could not open file 1"<<endl;
                                                            return;
                                                        }
                                                    file2=fopen("loan_taken_2.txt","w");
                                                    if(file2==NULL)
                                                        {
                                                            cout<<"Could not open file 2"<<endl;
                                                            return;
                                                        }
                                                    while(fgets(input,40,file1))
                                                        {
                                                            int i=0,j=0;
                                                            while((source[j]=input[i])!=','){i++; j++;}
                                                            source[j]='\0'; j=0; i++;
                                                            sscanf(source,"%s",source1);
                                                            while((amount[j]=input[i])!=','){i++; j++;}
                                                            amount[j]='\0'; j=0; i++;
                                                            while((date[j]=input[i])!=','){i++; j++;}
                                                            date[j]='\0'; j=0; i++;
                                                            while((month[j]=input[i])!=','){i++; j++;}
                                                            month[j]='\0';j=0; i++;
                                                            while((year[j]=input[i])!='\0'){i++; j++;}
                                                            year[j]='\0';
                                                            if(strcmp(source1,clear_source)==0){continue;}
                                                            sscanf(amount,"%d",&amount1);
                                                            sscanf(date,"%i",&date1);
                                                            sscanf(month,"%i",&month1);
                                                            sscanf(year,"%i",&year1);
                                                            fprintf(file2,"%s,%d,%i,%i,%i\n",source1,amount1,date1,month1,year1);
                                                        }
                                                    fclose(file1);
                                                    fclose(file2);
                                                    remove("loan_taken.txt");
                                                    rename("loan_taken_2.txt","loan_taken.txt");
                                                    break;
                                                }
                                            case 'n':
                                                {
                                                    break;
                                                }
                                            default:
                                                {
                                                    cout<<"Invalid Input"<<endl;
                                                    break;
                                                }
                                        }
                                    break;
                                }
                            case 2:
                                {
                                    Show_loan_given();
                                    cout<<" "<<endl;
                                    cout<<"Enter the receiver of loan: "<<endl;
                                    char clear_receiver[20];
                                    cin>>clear_receiver;
                                    char input[80];
                                    char date[3],month[3],year[3],receiver[20],amount[3];
                                    int date1,month1,year1,amount1; char receiver1[20];
                                    FILE* loan_given;
                                    loan_given=fopen("loan_given.txt","r");
                                    if(loan_given==NULL)
                                        {
                                            cout<<"Error reading file"<<endl;
                                            return;
                                        }
                                    else
                                        {
                                            while(fgets(input,80,loan_given))
                                                {
                                                    int i=0,j=0;
                                                    while((receiver[j]=input[i])!=','){i++; j++;}
                                                    receiver[j]='\0'; j=0; i++;
                                                    while((amount[j]=input[i])!=','){i++; j++;}
                                                    amount[j]='\0'; j=0; i++;
                                                    while((date[j]=input[i])!=','){i++; j++;}
                                                    date[j]='\0'; j=0; i++;
                                                    while((month[j]=input[i])!=','){i++; j++;}
                                                    month[j]='\0';j=0;i++;
                                                    while((year[j]=input[i])!='\0'){i++; j++;}
                                                    year[j]='\0';
                                                    if(strcmp(clear_receiver,receiver)==0){break;}
                                                }
                                        }
                                    fclose(loan_given);
                                    if(strcmp(clear_receiver,receiver)!=0){break;}
                                    cout<<" "<<endl;
                                    cout<<"Amount to be given is "<<amount<<endl;
                                    cout<<"Press y to continue or n to stop"<<endl;
                                    char check;
                                    cin>>check;
                                    switch(check)
                                        {
                                            case 'y':
                                                {
                                                    int bal=0;
                                                    sscanf(amount,"%d",&bal);
                                                    Balance_change(bal);
                                                    FILE* file1;
                                                    FILE* file2;
                                                    file1=fopen("loan_given.txt","r");
                                                    if(file1==NULL)
                                                        {
                                                            cout<<"Could not open file 1."<<endl;
                                                            return;
                                                        }
                                                    file2=fopen("loan_given_2.txt","w");
                                                    if(file2==NULL)
                                                        {
                                                            cout<<"Could not open file 2."<<endl;
                                                            return;
                                                        }
                                                    while(fgets(input,40,file1))
                                                        {
                                                            int i=0,j=0;
                                                            while((receiver[j]=input[i])!=','){i++; j++;}
                                                            receiver[j]='\0'; j=0; i++;
                                                            sscanf(receiver,"%s",receiver1);
                                                            while((amount[j]=input[i])!=','){i++; j++;}
                                                            amount[j]='\0'; j=0; i++;
                                                            while((date[j]=input[i])!=','){i++; j++;}
                                                            date[j]='\0'; j=0; i++;
                                                            while((month[j]=input[i])!=','){i++; j++;}
                                                            month[j]='\0';j=0; i++;
                                                            while((year[j]=input[i])!='\0'){i++; j++;}
                                                            year[j]='\0';
                                                            if(strcmp(receiver,clear_receiver)==0){continue;}
                                                            sscanf(amount,"%d",&amount1);
                                                            sscanf(date,"%i",&date1);
                                                            sscanf(month,"%i",&month1);
                                                            sscanf(year,"%i",&year1);
                                                            fprintf(file2,"%s,%d,%i,%i,%i\n",receiver1,amount1,date1,month1,year1);
                                                        }
                                                    fclose(file1);
                                                    fclose(file2);
                                                    remove("loan_given.txt");
                                                    rename("loan_given_2.txt","loan_given.txt");
                                                    break;
                                                }
                                            case 'n':
                                                {
                                                    break;
                                                }
                                            default:
                                                {
                                                    cout<<"Invalid Input"<<endl;
                                                    break;
                                                }
                                        }
                                    break;
                                }//closing case 2 of clear loan
                            default:
                                {
                                    cout<<"Invalid Input"<<endl;
                                    break;
                                }
                        }//closing switch in clear loan
                    break;
                }//closing clear loan case
            default:
                {
                    cout<<"Invalid Input"<<endl;
                    break;
                }
        }//closing switch from main function
}//closing functionality


//Function for the home screen
void main_screen(){
    //Header text for visual appeal
    cout<<"_______________________________________________________________________________"<<endl;
    cout<<"                                   My Money Tracker"<<endl;
    cout<<"_______________________________________________________________________________"<<endl;
    //output asking for the required function
    cout<<" Please select your category :"<<endl;
    cout<<" 1.Show Current Balance"<<endl;
    cout<<" 2.Income"<<endl;
    cout<<" 3.Expense"<<endl;
    cout<<" 4.Loan"<<endl;
    cout<<" 5.Set the monthly salary"<<endl;
    cout<<" 6.Exit App"<<endl;
    int input;//to store the received function call
    cin>>input;
    //switch to call for the respective function
    switch(input)
        {
            case 1:
                {
                    Balance();
                    Clr();
                    main_screen();
                    break;
                }
            case 2:
                {
                    Income();
                    Clr();
                    main_screen();
                    break;
                }
            case 3:
                {
                    Expense();
                    Clr();
                    main_screen();
                    break;
                }
            case 4:
                {
                    Loan();
                    Clr();
                    main_screen();
                    break;
                }
            case 5:
                {
                    Set_salary();
                    Clr();
                    main_screen();
                    break;
                }
            case 6:
                {
                    char command;
                    cout<<"Press 'y' if you really want to exit"<<endl;
                    cout<<"To go back press any other character"<<endl;// to verify from user
                    cin>>command;
                    if(command=='y')
                        {
                            cout<<"_______________________________________________________________________________"<<endl;
                            cout<<"                             @^Thanks for using the app^@"<<endl;
                            cout<<"_______________________________________________________________________________"<<endl;
                            exit(0);//function to stop app
                        }
                    else main_screen();//otherwise go back to home screen
                    break;
                }
            default:
                {
                    cout<<"Invalid input"<<endl;//for other random input
                    Clr();
                    main_screen();
                    break;
                }
        }
}


int main(){
    Check_salary();//To check if salary for this month is added
    main_screen();//calling for home screen
}
# money_tracker
#money_tracker
# money_tracker
