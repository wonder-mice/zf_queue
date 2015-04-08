#include <stdlib.h>
#include <stdio.h>
#include <zf_queue.h>

struct arg_entry
{
	const char *value;
	zf_slist_node slist_node;
};

int main(int argc, char *argv[])
{
	zf_slist_head_<arg_entry, &arg_entry::slist_node> args(ZF_LIST_INITIALIZER);
	for (int i = 0; argc > i; ++i)
	{
		arg_entry *const arg = (arg_entry *)malloc(sizeof(arg_entry));
		arg->value = argv[i];
		zf_slist_insert_head_(&args, arg);
	}
	while (!zf_slist_empty(&args))
	{
		arg_entry *const arg = zf_slist_first_(&args);
		zf_slist_remove_head(&args);
		printf("arg: \"%s\"\n", arg->value);
		free(arg);
	}
	return 0;
}
