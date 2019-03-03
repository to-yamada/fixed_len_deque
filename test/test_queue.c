#include "PCUnit/PCUnit.h"
#include "../queue.h"

DEFINE_FIXED_LEN_QUEUE(unsigned char, 5, UC_QUEUE);
static UC_QUEUE uc_queue;

static int initialize(void)
{
	return 0;
}

static int cleanup(void)
{
	return 0;
}

static int setup(void)
{
	clear_UC_QUEUE(&uc_queue);
	return 0;
}

static int teardown(void)
{
	return 0;
}


static void test_enqueue_dequeue_single_uc(void)
{
	unsigned char data = 0;
	const unsigned char expected = 10;

	PCU_ASSERT_TRUE(enqueue_UC_QUEUE(&uc_queue, &expected));

	PCU_ASSERT_TRUE(dequeue_UC_QUEUE(&uc_queue, &data));
	PCU_ASSERT_EQUAL(expected, data);
}

static void test_enqueue_dequeue_multi_uc(void)
{
	const unsigned char expected[] = {10, 20, 30, 40, 50};
	int i = 0;

	for (i = 0; i < 5; i++) {
		PCU_ASSERT_TRUE(enqueue_UC_QUEUE(&uc_queue, &expected[i]));
	}

	for (i = 0; i < 5; i++) {
		unsigned char data = 0;
		PCU_ASSERT_TRUE(dequeue_UC_QUEUE(&uc_queue, &data));
		PCU_ASSERT_EQUAL(expected[i], data);
	}
}

static void test_enqueue_full_uc(void)
{
	unsigned char data = 0;
	int i = 0;

	for (i = 0; i < 5; i++) {
		PCU_ASSERT_TRUE(enqueue_UC_QUEUE(&uc_queue, &data));
	}
	PCU_ASSERT_FALSE(enqueue_UC_QUEUE(&uc_queue, &data));
}

static void test_dequeue_empty_uc(void)
{
	unsigned char data = 0;
	PCU_ASSERT_FALSE(dequeue_UC_QUEUE(&uc_queue, &data));
}

static void test_dequeue_more_than_num_enqueues_uc(void)
{
	unsigned char data = 0;

	PCU_ASSERT_TRUE(enqueue_UC_QUEUE(&uc_queue, &data));

	PCU_ASSERT_TRUE(dequeue_UC_QUEUE(&uc_queue, &data));
	PCU_ASSERT_FALSE(dequeue_UC_QUEUE(&uc_queue, &data));
}


PCU_Suite *test_queue_suite(void)
{
	static PCU_Test tests[] = {
#include "test_queue.pcutests"
	};
	static PCU_Suite suite = {
		"test_queue", tests, sizeof tests / sizeof tests[0],
		setup,
		teardown,
		initialize,
		cleanup,
	};
	return &suite;
}

