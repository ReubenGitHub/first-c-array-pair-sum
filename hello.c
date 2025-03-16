#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void naiveSolver(int nums[], int nums_size, int target) {
    for (int i = 0; i < nums_size; i++) {
        for (int j = i + 1; j < nums_size; j++) {
            int sum = nums[i] + nums[j];
            if (sum == target) {
                printf("Indices of the two numbers whose sum equal to target value: %d %d. These numbers are %d and %d, which sums to %d\n", i, j, nums[i], nums[j], sum);
                break;
            }
        }
    }
    return;
}

// Create a new array of structs to store the values and their original indices
typedef struct {
    int value;
    int original_index;
} NumWithIndex;

// Comparison function for qsort
int compare(const void *a, const void *b) {
    NumWithIndex *num_a = (NumWithIndex *)a;
    NumWithIndex *num_b = (NumWithIndex *)b;
    return num_a->value - num_b->value;
}

void pointerSolver(int nums[], int nums_size, int target) {
    NumWithIndex num_with_indices[nums_size];
    for (int i = 0; i < nums_size; i++) {
        num_with_indices[i].value = nums[i];
        num_with_indices[i].original_index = i;
    }

    // Sort the array of structs based on the values
    qsort(num_with_indices, nums_size, sizeof(NumWithIndex), compare);

    // Now use two-pointer technique to find the solution
    int left_pointer = 0;
    int right_pointer = nums_size - 1;
    while (left_pointer < right_pointer) {
        int sum = num_with_indices[left_pointer].value + num_with_indices[right_pointer].value;
        if (sum == target) {
            printf("Indices of the two numbers whose sum equal to target value: %d %d. These numbers are %d and %d, which sums to %d\n",
                   num_with_indices[left_pointer].original_index,
                   num_with_indices[right_pointer].original_index,
                   num_with_indices[left_pointer].value,
                   num_with_indices[right_pointer].value,
                   sum);
            break;
        } else if (sum < target) {
            left_pointer++;
        } else {
            right_pointer--;
        }
    }
    return;
}

int main() {
    int nums[] = {4, 2, 1, 5, 7, 10, 12};
    int target = 7;
    int nums_size = sizeof(nums) / sizeof(nums[0]);
    
    clock_t start = clock();
    naiveSolver(nums, nums_size, target);
    clock_t end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken by naiveSolver: %f seconds\n", time_taken);

    clock_t start2 = clock();
    pointerSolver(nums, nums_size, target);
    clock_t end2 = clock();
    double time_taken2 = (double)(end2 - start2) / CLOCKS_PER_SEC;
    printf("Time taken by pointerSolver: %f seconds\n", time_taken2);

    printf("pointerSolver is %f times faster than naiveSolver\n", time_taken / time_taken2);

    return 0;
}
