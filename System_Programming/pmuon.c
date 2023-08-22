// DGIST, System Programming, 2023
// Yeseong Kim, CELL
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/time.h>
#include <linux/spinlock.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DGIST_CELL");
MODULE_DESCRIPTION("PMUON");

// PMU event number to collect -- YOUR QUIZ!
#define EVT_INSTRUCTIONS    0x08 // # of instructions
#define EVT_CACHE_MISSES    0x03 // # of L1 data cache refills (misses)
#define EVT_CACHE_REFS      0x04 // # of L1 data cache accesses
#define EVT_CPU_CYCLES      0x11 // # of CPU cycles

spinlock_t lock[4];
struct timer_list timer[4];
uint64_t counters[4][4];


void set_pmu(void* dummy) {
    uint64_t v;
    int cpu = smp_processor_id();
    printk("Turn PMU on Core %d\n", cpu);

    // 1. Enable "User Enable Register"
    asm volatile("msr pmuserenr_el0, %0" :: "r" (0x00000001));

    // 2. Reset i) Performance Monitor Control Register(PMCR),
    // ii) Count Enable Set Register, and
    // iii) Overflow Flag Status Register
    asm volatile ("msr pmcr_el0, %0" :: "r" (0x00000017));
    asm volatile ("msr pmcntenset_el0, %0" :: "r" (0x8000003f));
    asm volatile ("msr pmovsclr_el0, %0" :: "r" (0x8000003f));

    // 3. Disable Interrupt Enable Clear Register
    asm volatile("msr pmintenclr_el1, %0" :: "r" (~0));

    // 4. Read how many event counters exist
    asm volatile("mrs %0, pmcr_el0" : "=r" (v)); // Read PMCR
    printk("We have %llu configurable event counters on Core %d\n",
            (v >> 11) & 0x1F, smp_processor_id());

    // 5. Set event counter registers
    asm volatile("msr pmevtyper0_el0, %0" :: "r"(EVT_INSTRUCTIONS));
    asm volatile("msr pmevtyper1_el0, %0" :: "r"(EVT_CACHE_MISSES));
    asm volatile("msr pmevtyper2_el0, %0" :: "r"(EVT_CACHE_REFS));
    asm volatile("msr pmevtyper3_el0, %0" :: "r"(EVT_CPU_CYCLES));

    // Enable the four counters
    asm volatile("msr pmcntenset_el0, %0" :: "r"(0x0F));
}


void read_and_reset_pmu(void* dummy) {
    uint64_t tmp[4];
    int cpu = smp_processor_id();

    // Read all counters
    asm volatile("mrs %0, pmevcntr0_el0" : "=r"(tmp[0]));
    asm volatile("mrs %0, pmevcntr1_el0" : "=r"(tmp[1]));
    asm volatile("mrs %0, pmevcntr2_el0" : "=r"(tmp[2]));
    asm volatile("mrs %0, pmevcntr3_el0" : "=r"(tmp[3]));

    counters[cpu][0] += tmp[0];
    counters[cpu][1] += tmp[1];
    counters[cpu][2] += tmp[2];
    counters[cpu][3] += tmp[3];

    // Reset counters
    asm volatile("msr pmevcntr0_el0, %0" :: "r"(0));
    asm volatile("msr pmevcntr1_el0, %0" :: "r"(0));
    asm volatile("msr pmevcntr2_el0, %0" :: "r"(0));
    asm volatile("msr pmevcntr3_el0, %0" :: "r"(0));
}


void stop_pmu(void* dummy) {
    int cpu = smp_processor_id();

    // Disable all counters
    asm volatile("msr pmcntenclr_el0, %0" :: "r"(0x0F));

    // Collect and print
    read_and_reset_pmu(NULL);
    printk("[Core %d]\tInsts: %llu, Misses: %llu, Refs: %llu, Cycles: %llu\n",
            smp_processor_id(),
            counters[cpu][0],
            counters[cpu][1],
            counters[cpu][2],
            counters[cpu][3]);
}


void timer_callback(struct timer_list *timer) {
    int cpu = smp_processor_id();
    spin_lock(&lock[cpu]);
    read_and_reset_pmu(NULL);
    mod_timer(timer, jiffies + (HZ >> 2));
    spin_unlock(&lock[cpu]);
}


void timer_init(void) {
    int i;
    for (i = 0; i < 4; ++i) {
        spin_lock_init(&lock[i]);
        timer_setup(&timer[i], timer_callback, 0);
        timer[i].expires = jiffies + (HZ >> 2);
        add_timer_on(&timer[i], i);
    }
}


void timer_exit(void) {
    int ret;
    int i;
    for (i = 0; i < 4; ++i) {
        spin_lock(&lock[i]);
        ret = del_timer(&timer[i]);
        spin_unlock(&lock[i]);
    }
}


int init_module(void) {
    // Set Performance Monitoring Unit (aka Performance Counter) across all cores
    on_each_cpu(set_pmu, NULL, 1);
    timer_init();
    printk("Ready to use PMU\n");
    return 0;
}


void cleanup_module(void) {
    printk("PMU Kernel Module Off\n");
    timer_exit();
    on_each_cpu(stop_pmu, NULL, 1); // Stop PMU on all CPUs
}
