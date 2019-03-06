#include "PCUnit/PCUnit.h"
#include "../queue.h"

static unsigned char uc_data[5];
QUEUE uc_queue;

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
	INIT_QUEUE_ARRAY(&uc_queue, uc_data);
	INIT_QUEUE_ARRAY(&point_queue, point_data);
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

	PCU_ASSERT_TRUE(enqueue_queue(&uc_queue, &expected));

	PCU_ASSERT_TRUE(dequeue_queue(&uc_queue, &data));
	PCU_ASSERT_EQUAL(expected, data);
}

static void test_enqueue_dequeue_multi_uc(void)
{
	const unsigned char expected[] = {10, 20, 30, 40, 50};
	int i = 0;

	for (i = 0; i < 5; i++) {
		PCU_ASSERT_TRUE(enqueue_queue(&uc_queue, &expected[i]));
	}

	for (i = 0; i < 5; i++) {
		unsigned char data = 0;
		PCU_ASSERT_TRUE(dequeue_queue(&uc_queue, &data));
		PCU_ASSERT_EQUAL(expected[i], data);
	}
}

static void test_enqueue_full_uc(void)
{
	unsigned char data = 0;
	int i = 0;

	for (i = 0; i < 5; i++) {
		PCU_ASSERT_TRUE(enqueue_queue(&uc_queue, &data));
	}
	PCU_ASSERT_FALSE(enqueue_queue(&uc_queue, &data));
}

static void test_dequeue_empty_uc(void)
{
	unsigned char data = 0;
	PCU_ASSERT_FALSE(dequeue_queue(&uc_queue, &data));
}

static void test_dequeue_more_than_num_enqueues_uc(void)
{
	unsigned char data = 0;

	PCU_ASSERT_TRUE(enqueue_queue(&uc_queue, &data));

	PCU_ASSERT_TRUE(dequeue_queue(&uc_queue, &data));
	PCU_ASSERT_FALSE(dequeue_queue(&uc_queue, &data));
}

static void test_enqueue_at_single_uc(void)
{
	unsigned char data = 0;
	const unsigned char expected = 10;

	PCU_ASSERT_TRUE(enqueue_queue(&uc_queue, &expected));

	PCU_ASSERT_TRUE(at_queue(&uc_queue, 0, &data));
	PCU_ASSERT_EQUAL(expected, data);
}

static void test_enqueue_at_multi_uc(void)
{
	const unsigned char expected[] = {10, 20, 30, 40, 50};
	int i = 0;

	for (i = 0; i < 5; i++) {
		PCU_ASSERT_TRUE(enqueue_queue(&uc_queue, &expected[i]));
	}

	for (i = 0; i < 5; i++) {
		unsigned char data = 0;
		PCU_ASSERT_TRUE(at_queue(&uc_queue, i, &data));
		PCU_ASSERT_EQUAL(expected[i], data);
	}
}

static void test_at_empty_uc(void)
{
	unsigned char data = 0;

	PCU_ASSERT_FALSE(at_queue(&uc_queue, 0, &data));
}

static void test_at_more_than_num_enqueues_uc(void)
{
	unsigned char data = 0;

	PCU_ASSERT_TRUE(enqueue_queue(&uc_queue, &data));

	PCU_ASSERT_TRUE(at_queue(&uc_queue, 0, &data));
	PCU_ASSERT_TRUE(at_queue(&uc_queue, 0, &data));
}

static void test_at_invalid_index_uc(void)
{
	unsigned char data = 0;

	PCU_ASSERT_TRUE(enqueue_queue(&uc_queue, &data));

	PCU_ASSERT_FALSE(at_queue(&uc_queue, 1, &data));
}

static void test_at_NULL_uc(void)
{
	unsigned char data = 0;

	enqueue_queue(&uc_queue, &data);
	PCU_ASSERT_TRUE(at_queue(&uc_queue, 0, NULL));
}

static void test_enqueue_dequeue_single_point(void)
{
	POINT data = {0};
	const POINT expected = {-1000, 256};

	PCU_ASSERT_TRUE(enqueue_queue(&point_queue, &expected));

	PCU_ASSERT_TRUE(dequeue_queue(&point_queue, &data));
	PCU_ASSERT_MEMORY_EQUAL(&expected, &data, sizeof(POINT), 1);
}

static void test_enqueue_dequeue_multi_point(void)
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

static void test_enqueue_full_point(void)
{
	POINT data = {0};
	int i = 0;

	for (i = 0; i < 10; i++) {
		PCU_ASSERT_TRUE(enqueue_queue(&point_queue, &data));
	}
	PCU_ASSERT_FALSE(enqueue_queue(&point_queue, &data));
}

static void test_dequeue_empty_point(void)
{
	POINT data = {0};
	PCU_ASSERT_FALSE(dequeue_queue(&point_queue, &data));
}

static void test_dequeue_more_than_num_enqueues_point(void)
{
	POINT data = {0};

	PCU_ASSERT_TRUE(enqueue_queue(&point_queue, &data));

	PCU_ASSERT_TRUE(dequeue_queue(&point_queue, &data));
	PCU_ASSERT_FALSE(dequeue_queue(&point_queue, &data));
}

static void test_enqueue_at_single_point(void)
{
	POINT data = {0};
	const POINT expected = {-1000, 256};

	PCU_ASSERT_TRUE(enqueue_queue(&point_queue, &expected));

	PCU_ASSERT_TRUE(at_queue(&point_queue, 0, &data));
	PCU_ASSERT_MEMORY_EQUAL(&expected, &data, sizeof(POINT), 1);
}

static void test_enqueue_at_multi_point(void)
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

static void test_at_empty_point(void)
{
	POINT data = {0};

	PCU_ASSERT_FALSE(at_queue(&point_queue, 0, &data));
}

static void test_at_more_than_num_enqueues_point(void)
{
	POINT data = {0};

	PCU_ASSERT_TRUE(enqueue_queue(&point_queue, &data));

	PCU_ASSERT_TRUE(at_queue(&point_queue, 0, &data));
	PCU_ASSERT_TRUE(at_queue(&point_queue, 0, &data));
}

static void test_at_invalid_index_point(void)
{
	POINT data = {0};

	PCU_ASSERT_TRUE(enqueue_queue(&point_queue, &data));

	PCU_ASSERT_FALSE(at_queue(&point_queue, 1, &data));
}

static void test_at_NULL_point(void)
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

