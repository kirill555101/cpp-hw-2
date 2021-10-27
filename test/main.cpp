#include <gtest/gtest.h>

extern "C" {
#include "task.h"
}

#define EPS 1e-9


//* First test
const point_t* FIRST_INPUT_ARR = NULL;
const size_t FIRST_INPUT_ARR_LEN = 0;
const size_t FIRST_CLUSTERS_LEN = 0;

//* Second test
const point_t SECOND_INPUT_ARR[] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}, {13, 14, 15} };
const size_t SECOND_INPUT_ARR_LEN = 5;
const size_t SECOND_CLUSTERS_LEN = 2;

//* Third test
const point_t THIRD_INPUT_ARR[] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}, {13, 14, 15} };
const size_t THIRD_INPUT_ARR_LEN = 5;
point_t THIRD_CENTERS[] = { {4, 5, 6}, {10, 11, 12} };
const size_t THIRD_CLUSTERS_LEN = 2;
const point_t THIRD_RES_ARR[] = { {2.5, 3.5, 4.5}, {10, 11, 12} };


TEST(STATIC_TASK_TEST, HANDLE_EMPTY_ARRAY) {
  point_t* centers = identify_centers((point_t*)FIRST_INPUT_ARR, FIRST_INPUT_ARR_LEN, FIRST_CLUSTERS_LEN);

  EXPECT_TRUE(centers == NULL);

  point_t* res = k_means_cluster((point_t*)FIRST_INPUT_ARR, FIRST_INPUT_ARR_LEN, centers, FIRST_CLUSTERS_LEN);

  EXPECT_TRUE(res == NULL);
}

TEST(STATIC_TASK_TEST, HANDLE_ARRAY_IN_CENTERS) {
  point_t* res = identify_centers((point_t*)SECOND_INPUT_ARR, SECOND_INPUT_ARR_LEN, SECOND_CLUSTERS_LEN);

  EXPECT_TRUE(res != NULL);

  free(res);
}

TEST(STATIC_TASK_TEST, HANDLE_ARRAY_IN_CLUSTER) {
  point_t* res = k_means_cluster(
    (point_t*)THIRD_INPUT_ARR, THIRD_INPUT_ARR_LEN,
    (point_t*)THIRD_CENTERS, THIRD_CLUSTERS_LEN
  );

  EXPECT_TRUE(res != NULL);
  for (size_t i = 0; i < THIRD_CLUSTERS_LEN; ++i) {
    EXPECT_TRUE(abs(res[i].x - THIRD_RES_ARR[i].x) <= EPS);
    EXPECT_TRUE(abs(res[i].y - THIRD_RES_ARR[i].y) <= EPS);
    EXPECT_TRUE(abs(res[i].z - THIRD_RES_ARR[i].z) <= EPS);
  }
}


int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
