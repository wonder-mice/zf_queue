#include "zf_queue.hpp"

namespace
{
	struct slist_node
	{
		zf_slist_entry<slist_node> entry;
	};
	typedef zf_slist_head<slist_node, &slist_node::entry> slist_nodes;

	struct tailq_node
	{
		zf_tailq_entry<tailq_node> entry;
	};
	typedef zf_tailq_head<tailq_node, &tailq_node::entry> tailq_nodes;
}

// Test that header can be used from multiple .cpp files
void test_link()
{
	slist_nodes slist_ns = zf_slist_initializer(&slist_ns);
	zf_slist_init(&slist_ns);
	zf_slist_empty(&slist_ns);
	zf_slist_first(&slist_ns);
	tailq_nodes tailq_ns = zf_tailq_initializer(&tailq_ns);
	zf_tailq_empty(&tailq_ns);
	zf_tailq_first(&tailq_ns);
	zf_tailq_last(&tailq_ns);
}
