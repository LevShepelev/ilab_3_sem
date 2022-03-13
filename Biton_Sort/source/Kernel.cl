__kernel void bitonic_sort_step(__global TYPE *array, int partition_size, int compare_distance, int sort_direction) {

    const unsigned int monotonic_part_indicator = 0;
    unsigned int array_index = get_global_id(0);
    unsigned int compare_distance_rotated_index = compare_distance ^ array_index;

   if (compare_distance_rotated_index > array_index) {

       unsigned int bitonic_sequence_part_indicator = array_index & partition_size;
       if (sort_direction) {
               bitonic_sequence_part_indicator = ! bitonic_sequence_part_indicator;
       }

       bool swap = (bitonic_sequence_part_indicator == monotonic_part_indicator &&
                         array[array_index] > array[compare_distance_rotated_index]) ||
                     (bitonic_sequence_part_indicator != monotonic_part_indicator &&
                         array[array_index] <= array[compare_distance_rotated_index]);

       if (swap) {
           int temp_var = array[array_index];
           array[array_index] = array[compare_distance_rotated_index];
           array[compare_distance_rotated_index] = temp_var;
      }
   }
}