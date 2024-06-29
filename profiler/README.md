# Cache Performance Analysis of Row and Column Traversal

This project measures the cache performance of row-major and column-major traversal of a 2D array in C++. The code demonstrates the difference in cache efficiency when accessing array elements row-wise versus column-wise.

## Build and run

   ```bash
   cd <root project directory>
   mkdir build
   cd build
   cmake ..
   make
   ./profiler
   ```

### Cache Performance Results

Results obtained from `cachegrind`:

- **RowTraversal**:
  - L1 D-cache miss rate: 0.8%
  - L2 cache miss rate: 0.8%
  - Traversal time: 1083 ms

- **ColumnTraversal**:
  - L1 D-cache miss rate: 7.9%
  - L2 cache miss rate: 7.1%
  - Traversal time: 8491 ms

### Detailed Cachegrind Output

#### RowTraversal

```
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
```

#### ColumnTraversal

```
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
```

### Conclusion

The results clearly demonstrate that row-major traversal is significantly more cache-efficient than column-major traversal for this 2D array. This is due to better spatial locality when accessing contiguous memory locations in row-major order.
