*This project has been created as part of the 42 curriculum by aiwane.*

# Get Next Line

## Description

Get Next Line is a 42 project whose objective is to implement a function capable of reading and returning one line at a time from a file descriptor.

The project introduces one of the most important concepts in C programming: **static variables**. Since the `read()` system call reads data in chunks determined by `BUFFER_SIZE`, it may read beyond the end of the current line. Any extra data must therefore be preserved between function calls.

The implemented function:

```c
char	*get_next_line(int fd);
```

returns:

* The next line from the specified file descriptor.
* A line including the terminating `\n` when present.
* The final line without `\n` when EOF is reached.
* `NULL` when there is nothing left to read or when an error occurs.

The implementation works with:

* Regular files
* Standard input (`stdin`)
* Pipes
* FIFOs
* Any readable file descriptor

The bonus implementation additionally supports:

* Simultaneous handling of multiple file descriptors.
* Independent reading states for each file descriptor.
* Only one static variable.

---

## Instructions

### Compilation

Mandatory:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
get_next_line.c get_next_line_utils.c
```

Bonus:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
get_next_line_bonus.c get_next_line_utils_bonus.c
```

The project can be compiled:

* With `-D BUFFER_SIZE=n`
* Without `-D BUFFER_SIZE=n`

If `BUFFER_SIZE` is not specified during compilation, the default value defined in the header file will be used.

### Example Usage

```c
int		fd;
char	*line;

fd = open("file.txt", O_RDONLY);
while ((line = get_next_line(fd)) != NULL)
{
	printf("%s", line);
	free(line);
}
close(fd);
```

---

## Algorithm and Design Choices

### Overview

The main challenge of this project is that `read()` does not read data line by line. Instead, it reads up to `BUFFER_SIZE` bytes at a time.

For example, consider the following file:

```text
Hello
World
```

If `BUFFER_SIZE` is large enough, a single call to `read()` may return:

```text
Hello\nWorl
```

However, `get_next_line()` must return only:

```text
Hello\n
```

The remaining:

```text
Worl
```

must be preserved for the next call.

To achieve this, a static storage area called **stash** is used.

### Reading Process

1. Verify that the file descriptor is valid.
2. Check whether the stash already contains a newline.
3. If not, continue reading until a newline or EOF is found.
4. Extract one complete line from the stash.
5. Store the remaining characters back into the stash.
6. Return the extracted line.

### Why Use a Static Variable?

A normal local variable is destroyed when the function returns.

Since `get_next_line()` must remember unread data between calls, a static variable is required.

Without a static variable, any data read beyond the requested line would be lost.

### Performance Considerations

A common implementation repeatedly concatenates strings:

```c
stash = strjoin(stash, buffer);
```

This approach causes repeated allocations and copies, which can become inefficient for very long lines.

This implementation expands the storage capacity when necessary and appends data directly into the allocated memory area. This reduces the number of memory copies and improves performance on large files.

### Bonus Design

The mandatory version uses a single stash because only one file descriptor needs to be tracked.

The bonus version must support multiple file descriptors simultaneously.

To achieve this, a linked list is used. Each node stores:

* A file descriptor.
* Its associated stash.
* A pointer to the next node.

This allows each file descriptor to maintain its own reading state independently while still using only one static variable.

---

## Resources

### Documentation

* `man 2 read`
* `man 3 malloc`
* `man 3 free`
* GCC Documentation
* 42 Get Next Line Subject

### AI Usage

AI tools were used for:

* Reviewing the overall algorithm design.
* Reviewing README structure.

The implementation, debugging process, testing, and final validation were performed manually.
