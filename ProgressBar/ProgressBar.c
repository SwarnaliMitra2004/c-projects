#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>

const int BAR_LENGTH=50;
const int MAX_TASKS=5;

typedef struct{
    int id;
    int progress;
    int step;
}Task;

void print_bar(Task task);
void clear_screen();

int main(){
    Task tasks[MAX_TASKS];
    srand(time(NULL));

    //initialization
    for(int i=0;i<MAX_TASKS;i++){
        tasks[i].id=i+1;
        tasks[i].progress=0;
        tasks[i].step=rand()%5+1;
    }   
    int tasks_incomplete=1;
    while(tasks_incomplete){
        clear_screen();
        for(int i=0;i<MAX_TASKS;i++){
            tasks[i].progress+=tasks[i].step;
            if(tasks[i].progress>100){
                tasks[i].progress=100;
            }
            if(tasks[i].progress<100){
                tasks_incomplete=1;
            }
        print_bar(tasks[i]);
        }
        sleep(1); //sleep for 1 sec
    }
    printf("All tasks completed!!!");
    return 0;
}
void print_bar(Task task){
     int bar_to_show=(task.progress*BAR_LENGTH)*100;
    printf("Task %d : [",task.id);
    for(int i=0;i<BAR_LENGTH;i++){
        if(i<bar_to_show){
            printf("=");
        }
        else{
            printf(" ");
        }
    }
    printf("] %d%%\n",task.progress);
}
void clear_screen(){
    #ifdef _Win32
        system("cls");
    #else 
        system("clear");
 #endif   
}