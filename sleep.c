/*
 * Part of Astonia Server (c) Daniel Brockhaus. Please read license.txt.
 */

#include <stdio.h>
#include <sys/time.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#include "server.h"
#include "log.h"
#include "sleep.h"

int cidle_avg=0;

long long mono_us(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (long long)ts.tv_sec*1000000LL + ts.tv_nsec/1000;
}

void tick_sleep(int show) {
    long long now, tosleep, diff;
    static long long next = 0;
    static int nextshow = 0;

    //return;	// !!!!!!!!!!!!

    if (!next) next = mono_us() + TICK;

    now = mono_us();
    tosleep = next - now;
    xlog("ToSleep:%lld", tosleep);
    if (tosleep > MAX_SLEEP_US) tosleep = MAX_SLEEP_US;

    if (tosleep > 0) {
        struct timespec ts;
        ts.tv_sec  = tosleep / 1000000LL;
        ts.tv_nsec = (tosleep % 1000000LL) * 1000LL;

        // robust nanosleep that handles signals
        while (nanosleep(&ts, &ts) == -1 && errno == EINTR) {}
        long long after = mono_us();
        diff = next - after; // negative if we overslept
    } else {
        diff = 0; // already late
    }

    // update statistics
    long long slept = (tosleep > 0) ? (tosleep - diff) : 0; // actual sleep
    int cidle = (int)((100LL * slept) / TICK);
    if (cidle < 0) cidle = 0;
    if (cidle > 100) cidle = 100;

    cidle_avg = (int)((cidle_avg * 0.99) + (cidle * 0.01) * 100);

    // advance schedule; catch up if we’re late by multiple ticks
    next += TICK;
    now = mono_us();
    if (now > next + (10 * TICK)) {
        // if we fell >10 ticks behind, resync to avoid a long busy catch-up
        next = now + TICK;
    } else {
        // fast-forward by whole ticks if slightly behind
        while (now > next) next += TICK;
    }

    if (show) {
        if (nextshow) nextshow--;
        else {
            xlog("idle=%d%%.", cidle_avg);
            nextshow = TICKS * 3;
        }
    }
}
