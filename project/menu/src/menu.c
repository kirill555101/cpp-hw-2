#include "menu.h"

#include <stdio.h>

#include "task.h"

int execute() {
  size_t len = 6;
  const point_t arr[] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}, {13, 14, 15}, { 16, 17, 18 } };

  point_t* centers = identify_centers((point_t*)arr, len, 2);

  centers = k_means_cluster((point_t*)arr, len, centers, 2);

  for (size_t i = 0; i < 2; ++i) {
    printf("%lf %lf %lf\n", centers[i].x, centers[i].y, centers[i].z);
  }

  return 0;
}
