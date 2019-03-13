#include "PCUnit/PCUnit.h"
#include "../queue.h"

typedef struct {
	int x;
	int y;
} POINT;
static POINT point_data[10];
QUEUE point_queue;

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
	INIT_QUEUE_ARRAY(&point_queue, point_data);
	return 0;
}

static int teardown(void)
{
	return 0;
}

static void test_enqueue_dequeue_single(void)
{
	POINT data = {0};
	const POINT expected = {-1000, 256};

	PCU_ASSERT_TRUE(enqueue_queue(&point_queue, &expected));

	PCU_ASSERT_TRUE(dequeue_queue(&point_queue, &data));
	PCU_ASSERT_MEMORY_EQUAL(&expected, &data, sizeof(POINT), 1);
}

static void test_enqueue_dequeue_multi(void)
{
	const POINT expected[] = {
		{ 1000,  -1000},
		{ 2000,  -2000},
		{ 3000,  -3000},
		{ 4000,  -4000},
		{ 5000,  -5000},
		{ 6000,  -6000},
		{ 7000,  -7000},
		{ 8000,  -8000},
		{ 9000,  -9000},
		{10000, -10000},
	};
	int i = 0;

	for (i = 0; i < 10; i++) {
		PCU_ASSERT_TRUE(enqueue_queue(&point_queue, &expected[i]));
	}

	for (i = 0; i < 5; i++) {
		POINT data = {0};
		PCU_ASSERT_TRUE(dequeue_queue(&point_queue, &data));
		PCU_ASSERT_MEMORY_EQUAL(&expected[i], &data, sizeof(POINT), 1);
	}
}

static void test_enqueue_full(void)
{
	POINT data = {0};
	int i = 0;

	for (i = 0; i < 10; i++) {
		PCU_ASSERT_TRUE(enqueue_queue(&point_queue, &data));
	}
	PCU_ASSERT_FALSE(enqueue_queue(&point_queue, &data));
}

static void test_dequeue_empty(void)
{
	POINT data = {0};
	PCU_ASSERT_FALSE(dequeue_queue(&point_queue, &data));
}

static void test_dequeue_more_than_num_enqueues(void)
{
	POINT data = {0};

	PCU_ASSERT_TRUE(enqueue_queue(&point_queue, &data));

	PCU_ASSERT_TRUE(dequeue_queue(&point_queue, &data));
	PCU_ASSERT_FALSE(dequeue_queue(&point_queue, &data));
}

static void test_enqueue_at_single(void)
{
	POINT data = {0};
	const POINT expected = {-1000, 256};

	PCU_ASSERT_TRUE(enqueue_queue(&point_queue, &expected));

	PCU_ASSERT_TRUE(at_queue(&point_queue, 0, &data));
	PCU_ASSERT_MEMORY_EQUAL(&expected, &data, sizeof(POINT), 1);
}

static void test_enqueue_at_multi(void)
{
	const POINT expected[] = {
		{ 1000,  -1000},
		{ 2000,  -2000},
		{ 3000,  -3000},
		{ 4000,  -4000},
		{ 5000,  -5000},
		{ 6000,  -6000},
		{ 7000,  -7000},
		{ 8000,  -8000},
		{ 9000,  -9000},
		{10000, -10000},
	};
	int i = 0;

	for (i = 0; i < 5; i++) {
		PCU_ASSERT_TRUE(enqueue_queue(&point_queue, &expected[i]));
	}

	for (i = 0; i < 5; i++) {
		POINT data = {0};
		PCU_ASSERT_TRUE(at_queue(&point_queue, i, &data));
		PCU_ASSERT_MEMORY_EQUAL(&expected[i], &data, sizeof(POINT), 1);
	}
}

static void test_at_empty(void)
{
	POINT data = {0};

	PCU_ASSERT_FALSE(at_queue(&point_queue, 0, &data));
}

static void test_at_more_than_num_enqueues(void)
{
	POINT data = {0};

	PCU_ASSERT_TRUE(enqueue_queue(&point_queue, &data));

	PCU_ASSERT_TRUE(at_queue(&point_queue, 0, &data));
	PCU_ASSERT_TRUE(at_queue(&point_queue, 0, &data));
}

static void test_at_invalid_index(void)
{
	POINT data = {0};

	PCU_ASSERT_TRUE(enqueue_queue(&point_queue, &data));

	PCU_ASSERT_FALSE(at_queue(&point_queue, 1, &data));
}

static void test_at_NULL(void)
{
	POINT data = {0};

	enqueue_queue(&point_queue, &data);
	PCU_ASSERT_TRUE(at_queue(&point_queue, 0, NULL));
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

