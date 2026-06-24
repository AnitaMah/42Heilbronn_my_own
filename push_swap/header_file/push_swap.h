/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 16:17:37 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/18 15:02:23 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

/* ========================================================================== */
/* DEFINITIONS AND CONSTANTS                                                  */
/* ========================================================================== */

# define STRATEGY_SIMPLE 0
# define STRATEGY_MEDIUM 1
# define STRATEGY_COMPLEX 2
# define STRATEGY_ADAPTIVE 3

# define OP_SA 0
# define OP_SB 1
# define OP_SS 2
# define OP_PA 3
# define OP_PB 4
# define OP_RA 5
# define OP_RB 6
# define OP_RR 7
# define OP_RRA 8
# define OP_RRB 9
# define OP_RRR 10
# define OP_TOTAL 11

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>

/* ========================================================================== */
/* DATA STRUCTURES                                                            */
/* ========================================================================== */

/* --- FLAGS STRUCTURE --- */

typedef struct s_flags
{
    int             strategy;
    int             bench;
}                   t_flags;

/*
 * t_node - Represents a single element in the doubly linked list.
 * Each node stores the raw integer value and its corresponding 
 * normalized index used for sorting algorithms. The prev and next 
 * pointers allow for efficient traversal in both directions, which 
 * is crucial for complex stack manipulations and rotations.
 */
typedef struct s_node
{
    int             value;
    int             index;
    struct s_node   *next;
    struct s_node   *prev;
}                   t_node;

/*
 * t_stack - The core data structure container for the stack.
 * Manages the top and bottom nodes of the doubly linked list.
 * It tracks the current size of the stack, the chunk size for 
 * partitioning algorithms, and stores a name identifier. This 
 * encapsulation simplifies stack operations like pushes and rotations.
 */
typedef struct s_stack
{
    t_node          *top;
    t_node          *bottom;
    int             size;
    int             chunk_size;
    char            name;
}                   t_stack;

/*
 * t_input - Holds the raw input data before stack conversion.
 * Stores the sequence of integers parsed from command-line arguments 
 * along with the total count of numbers. This structure acts as a 
 * temporary buffer to facilitate array-based sorting (like quicksort) 
 * needed for index normalization.
 */
typedef struct s_input
{
    int             *arr;
    int             size;
}                   t_input;

/*
 * t_context - Aggregates all global program components.
 * This structure serves as the main context object, grouping stack A, 
 * stack B, the input data, and configuration flags. Passing this 
 * context to functions allows for a clean API, avoiding the need for 
 * global variables and ensuring thread-safety/modularity.
 */
typedef struct s_context
{
    t_stack         *a;
    t_stack         *b;
    t_input         *in;
    t_flags         *flags;
}                   t_context;

/* ========================================================================== */
/* STACK OPERATIONS BLOCK                                                     */
/* ========================================================================== */
/*
 * sb - Swap the first two elements at the top of stack A.
 * Similar to sa, this function swaps the positions of the top two 
 * elements within stack B. It ensures safe operation by checking 
 * the stack size and updates the operation counter. This is vital 
 * for local optimization during various sorting phases.
 */
void	sa(t_stack *a, t_flags *apply);

/*
 * sb - Swap the first two elements at the top of stack B.
 * Similar to sa, this function swaps the positions of the top two 
 * elements within stack B. It ensures safe operation by checking 
 * the stack size and updates the operation counter. This is vital 
 * for local optimization during various sorting phases.
 */
void                sb(t_stack *b, t_flags *apply);

/*
 * ss - Swap the first two elements of both stack A and stack B.
 * This helper combines both sa and sb operations into a single step.
 * It is used to minimize the total number of operations when both
 * stacks require a local swap simultaneously. The function maintains
 * stack integrity and records both actions in the counter.
 */
void                ss(t_stack *a, t_stack *b, t_flags *apply);

/*
 * pa - Push the top element from stack B to stack A.
 * This operation removes the top node from stack B and attaches it 
 * to the top of stack A. It is the primary mechanism for transferring 
 * sorted or partitioned elements back to the main stack. The operation 
 * is tracked for statistical analysis and benchmarking.
 */
void                pa(t_stack *a, t_stack *b, t_flags *apply);

/*
 * pb - Push the top element from stack A to stack B.
 * This operation moves the top node from stack A to stack B. 
 * It is commonly used during the partitioning stage of sorting 
 * algorithms to isolate specific groups of data. The function handles
 * node pointer updates and records the operation count.
 */
void                pb(t_stack *a, t_stack *b, t_flags *apply);

/*
 * ra - Rotate stack A upwards (top element becomes the bottom).
 * The top node of stack A is shifted to the bottom, effectively
 * moving all other elements one position up towards the top.
 * This is a fundamental operation for navigating and reordering 
 * the stack, tracked for performance evaluation.
 */
void                ra(t_stack *a, t_flags *apply);

/*
 * rb - Rotate stack B upwards (top element becomes the bottom).
 * Shifts all elements in stack B one position up, making the current
 * top node the new bottom node. This facilitates easier access to 
 * elements in stack B during chunk or radix sorting operations,
 * with state changes recorded via the apply pointer.
 */
void                rb(t_stack *b, t_flags *apply);

/*
 * rr - Rotate both stack A and stack B upwards.
 * Executes both ra and rb simultaneously. This is designed for 
 * efficient synchronization of both stacks, reducing the total 
 * number of instructions when both need to be shifted in the 
 * same direction. Each rotation is logged for operation tracking.
 */
void                rr(t_stack *a, t_stack *b, t_flags *apply);

/*
 * rra - Reverse rotate stack A (bottom element becomes the top).
 * The bottom node of stack A is moved to the top position, shifting
 * all other nodes one position down. This is useful when the required
 * target element is located at the bottom of the stack, avoiding
 * unnecessary long-distance rotations.
 */
void                rra(t_stack *a, t_flags *apply);

/*
 * rrb - Reverse rotate stack B (bottom element becomes the top).
 * Similar to rra, but applied specifically to stack B. It helps 
 * bring the bottom element to the top, providing a more efficient 
 * way to access nodes during complex sorting routines while keeping
 * the operation count accurate.
 */
void                rrb(t_stack *b, t_flags *apply);

/*
 * rrr - Reverse rotate both stack A and stack B simultaneously.
 * Performs both rra and rrb in a single instruction sequence.
 * It is used for synchronized backward rotation, further optimizing
 * the total number of operations required to reorganize the 
 * dual-stack structure during algorithm execution.
 */
void                rrr(t_stack *a, t_stack *b, t_flags *apply);

/* ========================================================================== */
/* SORTING ALGORITHMS BLOCK                                                   */
/* ========================================================================== */

/*
 * quicksort - Performs the quicksort algorithm for array normalization.
 * This function is used to prepare data by determining the relative 
 * rank of every element. It uses a divide-and-conquer strategy to 
 * sort an integer array, which is then used to assign indices 
 * to stack nodes, simplifying the final sorting process.
 */
void                quicksort(int *arr, int left, int right);

/*
 * normalize_index - Assigns relative rank indices to stack values.
 * After the initial parsing, this function uses the sorted array to 
 * map every value in the stack to its corresponding relative rank. 
 * This transformation is critical for algorithms like Radix Sort 
 * that rely on numeric indices rather than raw values.
 */
void                normalize_index(t_stack *a);

/*
 * chunk_sort - Sorts elements using a chunk-based partitioning algorithm.
 * The stack is divided into several chunks of specific sizes, which are
 * then moved to stack B based on their index values. This approach 
 * reduces the movement overhead compared to naive selection methods 
 * for medium-sized data sets.
 */
void                chunk_sort(t_stack *a, t_stack *b, t_flags *apply);

/*
 * bring_to_top - Efficiently rotates stack to place target node at top.
 * Calculates the shortest path (ra vs rra) to bring a specific node 
 * to the top of the stack. It then executes the necessary rotation 
 * operations, ensuring minimal movement and optimal performance 
 * within the sorting dispatcher.
 */
void                bring_to_top(t_stack *stack, t_node *target,
                        t_flags *apply);

/*
 * restore_to_a - Moves all remaining elements from stack B back to A.
 * Once the partitioning process is complete, this function systematically
 * pushes the sorted chunks from stack B back to stack A. It ensures 
 * the elements are placed in the correct order to result in a fully 
 * sorted stack upon completion.
 */
void                restore_to_a(t_stack *a, t_stack *b, t_flags *apply);

/*
 * find_max - Searches for the node with the highest index in stack B.
 * This utility function traverses the stack to identify the node
 * currently holding the maximum index value. This information is 
 * frequently needed when deciding which element to push back to A 
 * during the sorting process.
 */
t_node              *find_max(t_stack *b);

/*
 * radix_sort - Sorts stack elements using the bitwise radix sort algorithm.
 * This algorithm iterates through the binary representation of indices
 * to partition elements between stack A and B. It is highly efficient 
 * for large sets of data, guaranteeing a stable time complexity 
 * regardless of the initial distribution of values.
 */
void                radix_sort(t_stack *a, t_stack *b, t_flags *apply);

/*
 * selection_sort_adaptation - Basic selection sort modified for stack logic.
 * It iteratively searches for the next smallest element in stack A 
 * and moves it to the top. While not optimal for large inputs, it is
 * extremely effective for small stacks or as a fallback mechanism 
 * for nearly sorted data.
 */
void                selection_sort_adaptation(t_stack *a, t_stack *b,
                        t_flags *apply);

/*
 * sort_five - Specific sorting logic for 5 elements.
 * This function contains specialized handling for a small, fixed-size
 * input. By using a pre-defined sequence of operations, it sorts 
 * 5 elements with minimal instruction counts compared to generalized 
 * sorting strategies.
 */
void                sort_five(t_stack *a, t_stack *b, t_flags *apply);

/*
 * sort_four_five - Unified sorting logic for 4 or 5 elements.
 * Acts as a wrapper for sorting small stacks. It detects the current 
 * size and triggers the appropriate push/rotate/swap sequence. 
 * This keeps the logic organized and ensures that edge cases for 
 * tiny inputs are handled predictably and efficiently.
 */
void                sort_four_five(t_stack *a, t_stack *b, int size,
                        t_flags *apply);

/*
 * sort_three - Efficient sorting logic for exactly 3 elements.
 * Manages the specific permutations possible with 3 integers. 
 * It determines the optimal swap/rotate sequence based on the 
 * current relative values, ensuring the stack is sorted in the 
 * fewest possible operations.
 */
void                sort_three(t_stack *a, t_flags *apply);

/*
 * sort_two - Sorts stack if 2 elements are out of order.
 * A lightweight check that verifies if the top two elements are 
 * inverted. If a swap is required, it performs the sa operation.
 * It is often called as a final step in other, more complex 
 * recursive or iterative sorting functions.
 */
void                sort_two(t_stack *a, t_flags *apply);

/*
 * stack_to_array - Copies stack contents into an array.
 * This utility iterates through the linked list of the stack and 
 * transfers all values into a dynamically allocated integer array. 
 * This is primarily used for algorithms that require index-based 
 * access or quicksort-based normalization.
 */
int                 stack_to_array(t_stack *a);

/*
 * compute_disorder - Calculates the disorder coefficient (0 to 1).
 * Analyzes the sequence of numbers to determine how close the stack 
 * is to being sorted. A value of 0 indicates a perfectly sorted list,
 * while values approaching 1 indicate high entropy. This helps 
 * the dispatcher choose the best sorting strategy.
 */
double              compute_disorder(int *arr, int size);

/*
 * init_stack - Sets initial values and state for a stack structure.
 * Prepares the stack pointers and metadata, such as name and size.
 * It ensures that the memory is correctly zeroed out before any 
 * data is inserted, providing a clean slate for the input parser 
 * to build the list.
 */
void                init_stack(t_stack *stack, char name);

/*
 * is_sorted - Returns 1 if the stack is sorted in ascending order.
 * Performs a traversal of stack A to check if every element is 
 * smaller than its successor. This is used to skip sorting logic 
 * if the input is already in the desired final state, saving 
 * precious processing time.
 */
int                 is_sorted(t_stack *a);

/*
 * sort_stack - Main dispatcher to select and apply sorting algorithms.
 * Based on the calculated disorder coefficient and flags, this 
 * function decides whether to use a simple, medium, or complex 
 * algorithm. It serves as the primary gateway between the input 
 * environment and the actual sorting implementation.
 */
void                sort_stack(t_stack *a, t_stack *b, t_flags *flags,
                        double disorder);

/*
 * free_stack - Deallocates all memory associated with stack nodes.
 * Iterates through the linked list, freeing each node individually.
 * This is a critical cleanup function called during program 
 * termination or error recovery to prevent memory leaks in the 
 * long-running execution of the program.
 */
void                free_stack(t_stack *a);

/*
 * execute_rotation - Helper to perform a specific operation by index.
 * Maps integer operation identifiers to the corresponding stack
 * rotation functions. This allows for clean dispatching of 
 * instructions stored in buffers or calculated during benchmark 
 * mode, keeping the main loop concise.
 */
void                execute_rotation(t_stack *stack, int ops, t_flags *apply);

/* ========================================================================== */
/* PARSING AND INITIALIZATION BLOCK                                           */
/* ========================================================================== */

/*
 * parse_flags - Extracts program configuration from arguments.
 * Iterates through the command-line arguments to identify and store 
 * flags such as --simple, --bench, or --count_only. It populates the 
 * flags structure, which informs the program how to behave during 
 * the sorting phase.
 */
void                parse_flags(int argc, char **argv, t_flags *flags);

/*
 * is_flag - Checks if an argument string matches a known flag.
 * Compares the provided input string against a target flag definition.
 * It is a robust helper used to identify command-line switches 
 * while ensuring that arbitrary inputs do not cause unexpected 
 * behavior in the parsing module.
 */
int                 is_flag(char *s, char *flag);

/*
 * op_counter - Tracks or retrieves the total number of operations.
 * Maintains an internal static counter of all movements (sa, pb, ra, etc.).
 * When called with specific modes, it can increment the count, 
 * reset it, or simply return the current total, serving as the 
 * central record-keeper for algorithm efficiency.
 */
int                 op_counter(int mode);

/*
 * print_bench - Displays performance benchmark data.
 * When enabled, this function outputs diagnostic information 
 * about the sorting process, including the total operations and the 
 * initial disorder level. It is instrumental for developers to 
 * analyze and tune the performance of different sorting algorithms.
 */
void                print_bench(t_flags *flags, double disorder);

/*
 * count_words_in_split - Counts strings in a NULL-terminated array.
 * This helper calculates the total number of elements in an array 
 * produced by the ft_split function. It is essential for determining 
 * the required stack size when inputs are passed as quoted strings 
 * containing multiple numbers.
 */
int                 count_words_in_split(char **split);

/*
 * fill_single_split - Populates an integer array from a string split.
 * Iterates through a split string array, converts each valid substring 
 * to an integer, and stores it in the provided numeric array. 
 * This ensures that input parsing handles space-delimited formats 
 * correctly and efficiently.
 */
int                 fill_single_split(char **split, int *nums, int *k);

/*
 * parse_args - Initializes and populates data from arguments.
 * Orchestrates the full process of argument ingestion, from 
 * counting total inputs to allocating memory for the integer array 
 * and converting string arguments into usable numeric data for the stack.
 */
int                 *parse_args(int argc, char **argv, int *size);

/*
 * handle_args - Main handler for command line argument parsing.
 * Acts as the bridge between raw command-line input and the data 
 * structure population. It loops through arguments, handles flag 
 * skipping, and invokes appropriate parsing helpers to ensure all 
 * numbers are correctly captured.
 */
int                 handle_args(int argc, char **argv, int *nums, int mode);

/*
 * stack_from_array - Creates a stack from a provided integer array.
 * Converts the flat integer array into the doubly-linked list nodes 
 * of the stack. It sets up the top, bottom, and size metadata,
 * providing the required structure for the subsequent sorting 
 * algorithms to operate effectively.
 */
int                 stack_from_array(t_stack *a, int *arr, int size);

/*
 * is_valid_number - Validates if string represents a valid integer.
 * Performs a sanity check on input strings to ensure they only 
 * contain digits and optional sign characters. This acts as the 
 * first line of defense against malformed user input, preventing 
 * runtime errors during integer conversion.
 */
int                 is_valid_number(char *s);

/*
 * count_args - Counts total arguments provided in the list.
 * A utility to determine the number of elements in a command-line 
 * argument list. This is necessary for managing dynamic allocation 
 * of buffers during the parsing phase, ensuring that memory usage 
 * is always proportional to the input size.
 */
int                 count_args(char **args);

/*
 * count_total_words - Counts words across all arguments.
 * Specifically designed to handle the scenario where input arguments 
 * might contain multiple space-separated integers. It counts the total 
 * integer values that will be present in the final stack to pre-allocate 
 * arrays and avoid frequent reallocations.
 */
int                 count_total_words(int argc, char **argv);

/*
 * fill_all_nums - Populates array with all input numbers.
 * The final stage of parsing, where all identified numeric inputs are 
 * placed into a single array. It handles different input styles, 
 * merging arguments, and preparing the complete data set for 
 * stack initialization.
 */
int                 fill_all_nums(int argc, char **argv, int *nums);

/*
 * free_args_if_split - Cleans up split string arrays.
 * A safety function that determines if memory was dynamically 
 * allocated for argument splitting and frees it accordingly. 
 * This prevents memory leaks and keeps the parsing logic clean 
 * even when inputs are complex and nested.
 */
void                free_args_if_split(int argc, char **args);

/*
 * ft_atoi_ps - Custom string-to-integer conversion with error handling.
 * An extended version of the standard atoi, designed to flag errors 
 * when the input is outside integer limits or contains non-numeric 
 * characters. This ensures data integrity before it reaches the 
 * sorting layer.
 */
int                 ft_atoi_ps(const char *str, int *error);

/*
 * check_duplicates - Verifies that no two integers in the array are identical.
 * Before starting the sort, this function ensures the uniqueness 
 * of all elements in the input. Since the sorting algorithms assume 
 * unique ranks, this check is mandatory to prevent undefined 
 * behavior during the index normalization phase.
 */
int                 check_duplicates(int *array, int size);

/*
 * free_split - Utility to free dynamically allocated string arrays.
 * Handles the deallocation of memory for NULL-terminated arrays of 
 * strings. It is a standard cleanup helper used after any string 
 * parsing operation that relies on dynamic splits.
 */
void                free_split(char **arr);

/*
 * find_position - Finds the relative position of a node based on its index.
 * Helps in determining how many rotations are needed to reach a 
 * specific node within the stack. This is heavily used by strategies 
 * like chunk sort to identify the nearest path to a target element.
 */
int                 find_position(t_stack *stack, int index_limit);

/*
 * init_environment - Sets up global context and initial structures.
 * Allocates and initializes the stack structures and the main 
 * context object. It brings together all the initial components 
 * required for the program to operate, ensuring all pointers 
 * are valid and ready for the sorting cycle.
 */
int                 init_environment(int argc, char **argv, t_context *ctx);

/*
 * run_sorting - Manages the full lifecycle of the sorting process.
 * Acts as the high-level manager that executes the parsing, 
 * initialization, sorting, and reporting stages. It provides a 
 * structured flow from input to successful (or failed) output, 
 * abstracting complexity from the main entry point.
 */
void                run_sorting(t_stack *a, t_stack *b, t_flags *f,
                        t_input *in);

/*
 * init_and_fill_stack - Combines initialization and data loading.
 * A streamlined utility that initializes a stack and fills it 
 * with data from command-line arguments in one block. It simplifies 
 * the setup sequence for both stack A and B, making the core logic 
 * cleaner and easier to maintain.
 */
int                 init_and_fill_stack(t_stack *a, int argc, char **argv,
                        t_input *in);

/*
 * cleanup - Frees all allocated resources before exit.
 * Executes the final teardown process for the entire program, 
 * including freeing stacks and any temporary arrays. It ensures 
 * the operating system receives back all memory, resulting in a 
 * graceful exit for the process.
 */
void                cleanup(t_stack *a, t_stack *b);

#endif
