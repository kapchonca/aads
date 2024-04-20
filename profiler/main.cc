#include <chrono>
#include <iostream>

#define ROWS 100000
#define COLS 10000

void RowTraversal(int** arr) {
  int sum = 0;

  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      sum += arr[i][j];
    }
  }
}

void ColumnTraversal(int** arr) {
  int sum = 0;

  for (int j = 0; j < COLS; ++j) {
    for (int i = 0; i < ROWS; ++i) {
      sum += arr[i][j];
    }
  }
}

int main() {

  int** arr = (int**)malloc(ROWS * sizeof(int*));

  for (int i = 0; i < ROWS; ++i) {
    arr[i] = (int*)malloc(COLS * sizeof(int));
  }

  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      arr[i][j] = 1;
    }
  }

  std::chrono::steady_clock::time_point begin =
      std::chrono::steady_clock::now();

  // RowTraversal(arr);
  ColumnTraversal(arr);

  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  std::cout << "Traversal time = "
            << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                     begin)
                   .count()
            << "[ms]" << std::endl;

  for (int i = 0; i < ROWS; ++i) {
    free(arr[i]);
  }
  free(arr);

  return 0;
}

/*
TESTED ON 100000 ROWS AND 10000 COLUMNS OF INT'S

CACHEGRIND OUTPUT:

RowTraversal only:

==26908== 
==26908== I   refs:      29,056,183,340
==26908== I1  misses:             2,195
==26908== LLi misses:             2,118
==26908== I1  miss rate:           0.00%
==26908== LLi miss rate:           0.00%
==26908== 
==26908== D   refs:      15,021,598,134  (14,013,900,705 rd   + 1,007,697,429 wr)
==26908== D1  misses:       125,416,098  (    62,726,156 rd   +    62,689,942 wr)
==26908== LLd misses:       125,409,203  (    62,720,371 rd   +    62,688,832 wr)
==26908== D1  miss rate:            0.8% (           0.4%     +           6.2%  )
==26908== LLd miss rate:            0.8% (           0.4%     +           6.2%  )
==26908== 
==26908== LL refs:          125,418,293  (    62,728,351 rd   +    62,689,942 wr)
==26908== LL misses:        125,411,321  (    62,722,489 rd   +    62,688,832 wr)
==26908== LL miss rate:             0.3% (           0.1%     +           6.2%  )

ColumnTraversal only:

==26060== 
==26060== I   refs:      29,055,553,520
==26060== I1  misses:             2,197
==26060== LLi misses:             2,120
==26060== I1  miss rate:           0.00%
==26060== LLi miss rate:           0.00%
==26060== 
==26060== D   refs:      15,021,238,199  (14,013,630,749 rd   + 1,007,607,450 wr)
==26060== D1  misses:     1,187,888,596  ( 1,125,198,652 rd   +    62,689,944 wr)
==26060== LLd misses:     1,064,948,764  ( 1,002,259,930 rd   +    62,688,834 wr)
==26060== D1  miss rate:            7.9% (           8.0%     +           6.2%  )
==26060== LLd miss rate:            7.1% (           7.2%     +           6.2%  )
==26060== 
==26060== LL refs:        1,187,890,793  ( 1,125,200,849 rd   +    62,689,944 wr)
==26060== LL misses:      1,064,950,884  ( 1,002,262,050 rd   +    62,688,834 wr)
==26060== LL miss rate:             2.4% (           2.3%     +           6.2%  )

TIME MEASUREMENTS (WITHOUT CACHEGRIND):

RowTraveresal only:
Traversal time = 1083[ms]

ColumnTraversal only:
Traversal time = 8491[ms]
*/