#include <linux/module.h>
#include <linux/tty.h>
#include <linux/kd.h>
#include <linux/vt.h>
#include <linux/console_struct.h>
#include <linux/vt_kern.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/string.h>
#include <linux/timer.h>

MODULE_DESCRIPTION("Module for controlling keyboard LEDs via sysfs.");
MODULE_LICENSE("GPL");

#define BLINK_DELAY   HZ/5
#define ALL_LEDS_ON 0x07
#define RESTORE_LEDS  0xFF

static struct timer_list my_timer;
struct kobject *kbd_kobject;
struct tty_driver *my_driver;
static int _kbledstatus = ALL_LEDS_ON;

void my_timer_callback(struct timer_list *timer) {
    _kbledstatus = _kbledstatus == ALL_LEDS_ON ? 0 : ALL_LEDS_ON;
    (my_driver->ops->ioctl) (vc_cons[fg_console].d->port.tty, KDSETLED, _kbledstatus);
    mod_timer(&my_timer, jiffies + BLINK_DELAY);
}

static ssize_t led_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf) {
    return sprintf(buf, "%d\n", _kbledstatus);
}

static ssize_t led_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count) {
    sscanf(buf, "%du", &_kbledstatus);
    (my_driver->ops->ioctl) (vc_cons[fg_console].d->port.tty, KDSETLED, _kbledstatus);
    return count;
}

static struct kobj_attribute led_attribute = __ATTR(led_status, 0660, led_show, led_store);

static int __init kbleds_init(void) {
    int error = 0;
    printk(KERN_INFO "kbleds: loading\n");
    my_driver = vc_cons[fg_console].d->port.tty->driver;

    kbd_kobject = kobject_create_and_add("kbd", kernel_kobj);
    if(!kbd_kobject) return -ENOMEM;

    error = sysfs_create_file(kbd_kobject, &led_attribute.attr);
    if (error) {
        printk(KERN_INFO "failed to create the led_status file in /sys/kernel/kbd \n");
    }

    timer_setup(&my_timer, my_timer_callback, 0);
    mod_timer(&my_timer, jiffies + BLINK_DELAY);

    return error;
}

static void __exit kbleds_cleanup(void) {
    printk(KERN_INFO "kbleds: unloading...\n");
    (my_driver->ops->ioctl) (vc_cons[fg_console].d->port.tty, KDSETLED, RESTORE_LEDS);
    kobject_put(kbd_kobject);
    del_timer(&my_timer);
}

module_init(kbleds_init);
module_exit(kbleds_cleanup);
