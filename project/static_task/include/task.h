#ifndef PROJECT_STATIC_TASK_INCLUDE_TASK_H_
#define PROJECT_STATIC_TASK_INCLUDE_TASK_H_

#include <stddef.h>

typedef struct {
  double x;
  double y;
  double z;
} point_t;

point_t* identify_centers(point_t* arr, size_t len, size_t clusters_len);

point_t* k_means_cluster(point_t* arr, size_t len, point_t* centers, size_t clusters_len);

#endif // PROJECT_STATIC_TASK_INCLUDE_TASK_H_
