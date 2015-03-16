# MSS Multi Tasking Basic #

## MSS Task ##

MSS Task is based on coroutine concept which allows a function code (in this case the MSS task function code) to suspend at a certain location and then resume at the same spot where it left before. Coroutine enables the possibility to implement a very light weight multi tasking system at the cost of losing the ability to retain the local variables between suspending and re-entering the task code (MSS has only one memory stack shared by the scheduler and all tasks).

This means that when using local variable(s) in its code, a task shall expect that the local variable value to be changed when re-entering the function after suspending it self. Therefore static data type shall be used if the variable value is wished to be retained between suspending and re-entering the task.

Even tough MSS also supports preemptive schedulding (see next section), it doesn't mean that when a lower task is preempted, it will lose the local variable. MSS scheduler preempts the lower priority task by calling a software interrupt which will call the scheduler function again and execute the higher priority task. So basically the local variable context of the preempted task is stored safely on the top of memory stack.

In general a MSS task looks like the following:

```

void a_mss_task(void *param)
{
static mss_task_ctx_t task_ctx = MSS_TASK_CTX_STATE_INIT_VAL;
// other variable declaration - be careful of using local variables

MSS_BEGIN(task_ctx); // must be the first instruction in the task code

// initialization code

while(1)
{
// do some tasks

MSS_RETURN(task_ctx); // suspend task temporarily

// do another tasks
}

MSS_FINISH(); // last instruction in task code
}
```

As can be seen above, a task needs a static variable with mss\_task\_ctx\_t type (initialized with value MSS\_TASK\_CTX\_STATE\_INIT\_VAL) to store the information in which code part the function has been suspended last time.

MSS\_BEGIN(ctx) shall be the first instruction in the task code, while MSS\_FINISH() as the last one. When a task want to give up a CPU, it calls the MSS\_RETURN(ctx) which also stores the information of the address where the task is left. The MSS\_RETURN() is also encapsulated by some macro functions of MSS modules, please refer to the API documentation for further information.

The implementation of coroutine in MSS is derived from: http://www.chiark.greenend.org.uk/~sgtatham/coroutines.html and similar to the implementation of protothreads: http://dunkels.com/adam/pt/


## MSS Scheduling ##

MSS supports two basic scheduling policy depending on the configuration value of MSS\_PREEMPTIVE\_SCHEDULING in mss\_cfg.h:

### Cooperative Scheduling (MSS\_PREEMPTIVE\_SCHEDULING = FALSE) ###
In the cooperative scheduling mode, a task will be executed as long as it hasn't given up the CPU by calling the MSS\_RETURN() function. The scheduler always looks for the highest priority task which is ready to be executed after the running task suspends. The advantage of this scheduling policy is that it needs less memory stack than the preemptive mode, however the disadvatage is that higher prioirty task might expect longer lattency since it can't preempt a running task with lower priority.

### Preemptive Scheduling (MSS\_PREEMPTIVE\_SCHEDULING = TRUE) ###
In the preemptive scheduling mode, a higher priority task can preempt a running task which has lower priority. Altough the MSS task is based on coroutine concept, it can be assured that a preempted task will not lose its local variable when it is preempted by the higher priority task. The main advantage of this scheduling policy is that preemption which increase the responsiveness of higher priority task, however in this policy the scheduler can go deep into the memory stack, and therefore a bigger memory stack is needed to prevent stack overflow.