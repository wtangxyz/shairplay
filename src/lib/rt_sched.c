#define _GNU_SOURCE
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sched.h>
#include <string.h>
#include "rt_sched.h"


int set_process_affinity(unsigned cpu_mask)
{
	cpu_set_t cpuset;

	if (cpu_mask < 0)
		return 0;

	CPU_ZERO(&cpuset);
	for (int i = 0; i < sysconf(_SC_NPROCESSORS_ONLN); i++) {
		if (1 << i & cpu_mask) {
			fprintf(stdout, "set process on cpu%d\n", i);
			CPU_SET(i, &cpuset);
		}
	}
	if (sched_setaffinity(0, sizeof(cpuset), &cpuset)) {
		fprintf(stderr, "set cpu affinity failed: %s\n", strerror(errno));
		return errno;
	}
	return 0;
}

int set_process_priority(unsigned priority)
{
	int ret;
	struct sched_param param;

	param.sched_priority = priority;
	fprintf(stdout, "set process prioriry to %d\n", priority);
	ret = sched_setscheduler(0, SCHED_FIFO, &param);
	if (ret) {
		fprintf(stderr, "set fifo failed: %s\n", strerror(errno));
		return ret;
	}
	return 0;
}

