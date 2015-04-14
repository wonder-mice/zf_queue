#include <stdlib.h>
#include <stdio.h>
#include <zf_queue.h>

typedef struct arg_entry
{
	const char *value;
	zf_slist_node slist_node;
} arg_entry_t;

int main(int argc, char *argv[])
{
	zf_slist_head args = ZF_LIST_INITIALIZER();
	for (int i = 0; argc > i; ++i)
	{
		arg_entry_t *const arg = (arg_entry_t *)malloc(sizeof(arg_entry_t));
		arg->value = argv[i];
		zf_slist_insert_head(&args, &arg->slist_node);
	}
	while (!zf_slist_empty(&args))
	{
		zf_slist_node *const node = zf_slist_first(&args);
		arg_entry_t *const arg = zf_entry(node, arg_entry_t, slist_node);
		zf_slist_remove_head(&args);
		printf("arg: \"%s\"\n", arg->value);
		free(arg);
	}
	return 0;
}
