# Creating MSS Application #

The steps needed to create MSS application are described as follows:

## Creating Configuration Files ##
Create and modify configuration files llist\_cfg.h and mss\_cfg.h (template files are available under ROOT\_DIRECTORY/Sources/mss/templates/configuration)

### llist\_cfg.h ###
llist\_cfg.h contains the maximum number of linked list in the application. MSS needs at least one linked list if MSS timer is activated, one for every message queues, and one for every memory blocks. Application might increase this number if necessary.

### mss\_cfg.h ###
mss\_cfg.h contains MSS main configurations:

  * Setting maximum number of tasks (MSS\_NUM\_OF\_TASKS), list of tasks (MSS\_TASK\_LIST), initial value of task ready bits (MSS\_READY\_TASK\_BITS\_INIT) which represents whether a task shall be activated per default at the begining.

  * Setting the scheduler policy: cooperative scheduling if MSS\_PREEMPTIVE\_SCHEDULUNG = FALSE or preemptive scheduling if MSS\_PREEMPTIVE\_SCHEDULING.

  * Each MSS modules (timer, message queue, event, semaphore, and memory blocks) can be disabled, enabled, and configured (e.g. setting maximum number of module objects, or data types) in this file. Modules which are not used shall be disabled to save memory footprint.


## Populating Files ##
Include the configuration files and the mss hardware independent (under "common" folder) and hardware dependent (under "target/TARGET\_NAME" folder) for compilation


## Writing Application ##
Start writing the MSS application tasks which are included in the MSS\_TASK\_LIST.


## Launching MSS ##
MSS shall be launched in the main() function which is recommended to look like follows:

```

void main(void)
{
// initialize mss
mss_init();

// initialize application
init_app();

// run mss - shall never return
mss_run();
}
```