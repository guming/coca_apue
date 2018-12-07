#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<semaphore.h>
char* buf[5];
int pos;
//1.定义信号量
sem_t sem;
void* task(void* pv){
    //3.使用信号量,-1
    sem_wait(&sem);
    
    //4.访问共享内存
    buf[pos]=(char*)pv;
    sleep(1);
    pos++;
    
    //5.使用信号量进行解锁
    sem_post(&sem);
}
main(){
    //2.初始化信号量
    sem_init(&sem,0,1);
    
    pthread_t thread;
    pthread_create(&thread,NULL,task,(void*)"zhangfei");
    pthread_t thread2;
    pthread_create(&thread2,NULL,task,(void*)"guanyu");
    
    pthread_join(thread,NULL);
    pthread_join(thread2,NULL);
    
//打印字符指针数组中的有效数据
    int i=0;
    for(i=0;i<pos;i++){
        printf("%s ",buf[i]);
    }
    printf("\n");
    //6.如果不再使用则销毁信号量
    sem_destroy(&sem);
    return 0;
}
