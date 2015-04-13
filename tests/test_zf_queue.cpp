#include "test_zf_queue.h"

int main(int argc, char *argv[])
{
	TEST_RUNNER_CREATE(argc, argv);

	TEST_EXECUTE_SUITE(test_zf_queue_h);

	return TEST_RUNNER_EXIT_CODE();
}
