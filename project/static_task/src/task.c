#include "task.h"

#include <stdlib.h>
#include <time.h>
#include <math.h>

#define EPS 1e-9

point_t* identify_centers(point_t* arr, size_t len, size_t clusters_len) {
  if (arr == NULL || len == 0) {
    return NULL;
  }

  point_t* centers = calloc(clusters_len, sizeof(point_t));
  if (centers == NULL) {
    return NULL;
  }

  srand(time(NULL));

  for (int i = 0; i < clusters_len; ++i) {
    point_t temp = arr[0 + rand() % len];

    for (int j = i; j < clusters_len; ++j) {
      if (temp.x == centers[j].x || temp.y == centers[j].y || temp.z == centers[j].z) {
        --i;
        break;
      }

      centers[j] = temp;
    }
  }

  return centers;
}

inline static size_t calculate_distance(point_t center, point_t point) {
  return sqrt(pow(center.x - point.x, 2) + pow(center.y - point.y, 2) + pow(center.z - point.z, 2));
}

point_t* k_means_cluster(point_t* arr, size_t len, point_t* centers, size_t clusters_len) {
  if (arr == NULL || len == 0 || centers == 0 || clusters_len == 0) {
    return NULL;
  }

  size_t* cluster_sizes = calloc(clusters_len, sizeof(size_t));
  if (cluster_sizes == NULL) {
    return NULL;
  }

  point_t* new_centers = calloc(clusters_len, sizeof(point_t));
  if (new_centers == NULL) {
    free(cluster_sizes);
    return NULL;
  }

  for (size_t i = 0; i < clusters_len; ++i) {
    new_centers[i] = centers[i];
    cluster_sizes[i] = 1;
  }

  for (size_t i = 0; i < len; ++i) {
    point_t arr_temp = arr[i];
    size_t temp = calculate_distance(new_centers[0], arr_temp);

    size_t min_distance = temp;
    size_t min_index = 0;

    size_t is_center = 0;

    for (size_t j = 0; j < clusters_len; ++j) {
      if (fabs(centers[j].x - arr_temp.x) <= EPS && fabs(centers[j].y - arr_temp.y) <= EPS &&
        fabs(centers[j].z - arr_temp.z) <= EPS) {
        is_center = 1;
        break;
      }

      temp = calculate_distance(new_centers[j], arr_temp);

      if (temp < min_distance) {
        min_distance = temp;
        min_index = j;
      }
    }

    if (is_center == 1) {
      continue;
    }

    point_t centers_temp = new_centers[min_index];
    temp = cluster_sizes[min_index];

    centers_temp.x = (centers_temp.x * temp + arr_temp.x) / (temp + 1);
    centers_temp.y = (centers_temp.y * temp + arr_temp.y) / (temp + 1);
    centers_temp.z = (centers_temp.z * temp + arr_temp.z) / (temp + 1);

    new_centers[min_index] = centers_temp;
    cluster_sizes[min_index] = temp + 1;
  }

  for (size_t i = 0; i < clusters_len; ++i) {
    centers[i] = new_centers[i];
  }

  free(cluster_sizes);
  free(new_centers);

  return centers;
}
