#include "types.h"
#include "riscv.h"
#include "param.h"
#include "defs.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;


  argint(0, &n);
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}


// #ifdef LAB_PGTBL
// int
// sys_pgaccess(void)
// {
//   // lab pgtbl: your code here.
//   return 0;
// }
// #endif

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint64
sys_pgaccess(void) {
  uint64 starting_va;
  int num_of_pages;
  uint64 out_buff;
  argaddr(0, &starting_va);
  argint(1, &num_of_pages);
  argaddr(2, &out_buff);
  unsigned int ker_out_buff = 0;
  struct proc *p = myproc();
  pte_t * pte;

  for(int i=0; i<num_of_pages; i++) {
    uint64 va = starting_va + PGSIZE*i;
    if ((pte = walk(p->pagetable, va, 0))) {
      if(*pte & PTE_A) {
        *pte = *pte & (~(unsigned int)PTE_A);
        ker_out_buff =  ker_out_buff | (1 << i);
      }
    }
  }
  printf("%d\n", ker_out_buff);
  copyout(p->pagetable, out_buff, (char*)&ker_out_buff, sizeof(ker_out_buff));
  return 0;

}