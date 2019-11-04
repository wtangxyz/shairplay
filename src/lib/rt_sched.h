#ifndef _RT_SCHED_H
#define _RT_SCHED_H_

#define CONFIG_BETTER_PERFORMANCE
#define CONFIG_LARGE_BUFFER

int set_process_affinity(unsigned cpu_mask);
int set_process_priority(unsigned priority);

#endif
