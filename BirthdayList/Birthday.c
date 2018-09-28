#include <linux/list.h>
#include <linux/slab.h>
struct birthday
{
	int month;
	int day;
	int year;
	char *name;
	struct list_head list;
};
/**
* The following defines and initializes a list_head object named birthday_list
*/
static LIST_HEAD(birthday_list);
int simple_init(void)
{
	/* Create a linked list containing five struct birthday elements*/
	struct birthday *person;
	person = kmalloc(sizeof(*person), GFP_KERNEL);
	person->name = "John William Martin";
	person->day = 22;
	person->month = 12;
	person->year = 1992;
	INIT_LIST_HEAD(&person->list);
	
	list_add_tail(&person->list, &birthday_list);
	
	person = kmalloc(sizeof(*person), GFP_KERNEL);
	person->name = "George";
	person->day = 8;
	person->month = 3;
	person->year = 1979;
	
	list_add_tail(&person->list, &birthday_list);
	
	person = kmalloc(sizeof(*person), GFP_KERNEL);
	person->name = "William";
	person->day = 26;
	person->month = 10;
	person->year = 1987;
	
	list_add_tail(&person->list, &birthday_list);
	
	person = kmalloc(sizeof(*person), GFP_KERNEL);
	person->name = "Mike";
	person->day = 1;
	person->month = 5;
	person->year = 1967;
	
	list_add_tail(&person->list, &birthday_list);
	
	person = kmalloc(sizeof(*person), GFP_KERNEL);
	person->name = "James";
	person->day = 17;
	person->month = 2;
	person->year = 1980;
	
	list_add_tail(&person->list, &birthday_list);
	list_for_each_entry(person, &birthday_list, list) {
		printk(KERN_INFO "Added %s %d %d %d\n", person->name,
			person->day, person->month, person->year);
	}
	return 0;
}
void simple_exit(void) {
	/* Remove the elements from the linked list and return the free memory back to the kernel */
	struct birthday *ptr, *next;
	list_for_each_entry_safe(ptr, next, &birthday_list, list)
	{
		list_del(&ptr->list);
		printk(KERN_INFO "Removed %s %d %d %d\n", ptr->name,
			ptr->day, ptr->month, ptr->year);
		kfree(ptr);
	}
}
module_init( simple_init );
module_exit( simple_exit );
