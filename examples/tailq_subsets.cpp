#include <string>
#include <vector>
#include <stdio.h>
#include <zf_queue.h>

namespace
{
	struct item
	{
		char v;
		zf_tailq_node node;
	};
	typedef zf_tailq_head_t(item, node) items_t;

	std::string to_string(items_t &items)
	{
		std::string s;
		for (item *i = zf_tailq_begin_(&items), *e = zf_tailq_end_(&items);
			 e != i; i = zf_tailq_next_(&items, i))
		{
			s.push_back(i->v);
		}
		return s;
	}

	void subsets_iter(items_t &taken, items_t &items)
	{
		if (zf_tailq_empty(&items))
		{
			printf("%s\n", to_string(taken).c_str());
			return;
		}
		item *const i = zf_tailq_first_(&items);
		zf_tailq_remove_(&items, i);
		// 1. i is out
		subsets_iter(taken, items);
		// 2. i is in
		zf_tailq_insert_head_(&taken, i);
		subsets_iter(taken, items);
		// 3. cleanup
		zf_tailq_remove_(&taken, i);
		zf_tailq_insert_head_(&items, i);
	}

	void subsets(const unsigned n)
	{
		items_t items = ZF_TAILQ_INITIALIZER(&items);
		std::vector<item> storage(n);
		for (unsigned i = 0; n > i; ++i)
		{
			storage[i].v = 'a' + i;
			zf_tailq_insert_tail_(&items, &storage[i]);
		}
		items_t taken = ZF_TAILQ_INITIALIZER(&taken);
		subsets_iter(taken, items);
	}
}

int main(int argc, char *argv[])
{
	try
	{
		if (1 >= argc)
		{
			throw std::logic_error("invalid command line arguments");
		}
		const unsigned n = std::stoi(argv[1]);
		if (n > 'z' - 'a')
		{
			throw std::logic_error("n out of range");
		}
		subsets(n);
		return 0;
	}
	catch (const std::logic_error &e)
	{
		fprintf(stderr, "Error: %s\n", e.what());
		fprintf(stderr, "Usage: prog SET_SIZE\n");
		return 1;
	}
}
