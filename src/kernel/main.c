/* main.c
 *   测试线程执行
 */

#include <stddef.h>
#include <printk.h>
#include <init.h>
#include <thread.h>
#include <interrupt.h>
#include <console.h>
#include <print.h>
#include <ioqueue.h>
#include <keyboard.h>
#include <process.h>
#include <syscall.h>
#include <sys.h>
#include <stdio.h>
#include <memory.h>
#include <timer.h>
#include <fs.h>
#include <dir.h>

void k_thread_a(void *arg);
void k_thread_b(void *arg);
void u_prog_a(void);
void u_prog_b(void);

int main(void)
{
    put_str("kernel start ... \n");
    init_all();     /* 初始化所有模块 */

    /************ test code start ***************/
    
    struct dir* p_dir = sys_opendir("/dir1/subdir1");
    if (p_dir) 
    {
        printf("/dir1/subdir1 open done!\ncontent:\n");
        char* type = NULL;
        struct dir_entry* dir_e = NULL;
        while((dir_e = sys_readdir(p_dir))) 
        { 
            if (dir_e->f_type == FT_REGULAR) 
            {
                type = "regular";
            } else {
                type = "directory";
            }
            printf("   %-10s  %s\n", type, dir_e->filename);
        }
        
        if (sys_closedir(p_dir) == 0) 
        {
            printf("/dir1/subdir1 close done!\n");
        } else {
            printf("/dir1/subdir1 close fail!\n");
        }
    } 
    else 
    {
        printf("/dir1/subdir1 open fail!\n");
    }
    
    /************ test code end ***************/
    while (1)
        ;

    return 0;
}

/* 在线程中运行的函数 */
void k_thread_a(void *arg)
{
    void * addr1 = sys_malloc(256);
    void * addr2 = sys_malloc(255);
    void * addr3 = sys_malloc(254);

    printk(" thread_a, malloc addr: %x, %x, %x\n", 
                (int)addr1, (int)addr2, (int)addr3);

    int cpu_delay = 100000;
    while (cpu_delay-- > 0)
        ;

    sys_free(addr1);
    sys_free(addr2);
    sys_free(addr3);
    
    while(1)
        ;
}

void k_thread_b(void *arg)
{
    void * addr1 = sys_malloc(256);
    void * addr2 = sys_malloc(255);
    void * addr3 = sys_malloc(254);

    printk(" thread_b, malloc addr: %x, %x, %x\n", 
                (int)addr1, (int)addr2, (int)addr3);

    int cpu_delay = 100000;
    while (cpu_delay-- > 0)
        ;

    sys_free(addr1);
    sys_free(addr2);
    sys_free(addr3);
    
    while(1)
        ;
}

/* 测试用户进程 */
void u_prog_a(void)
{
    void * addr1 = malloc(256);
    void * addr2 = malloc(255);
    void * addr3 = malloc(254);

    printf(" prog_a, malloc addr: %x, %x, %x\n", 
                (int)addr1, (int)addr2, (int)addr3);

    int cpu_delay = 100000;
    while (cpu_delay-- > 0)
        ;

    free(addr1);
    free(addr2);
    free(addr3);
    
    while(1)
        ;
}

/* 测试用户进程 */
void u_prog_b(void)
{
    void * addr1 = malloc(256);
    void * addr2 = malloc(255);
    void * addr3 = malloc(254);

    printf(" prog_b, malloc addr: %x, %x, %x\n", 
                (int)addr1, (int)addr2, (int)addr3);

    int cpu_delay = 100000;
    while (cpu_delay-- > 0)
        ;

    free(addr1);
    free(addr2);
    free(addr3);
    
    while(1)
        ;
}
