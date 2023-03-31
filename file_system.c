#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

#define O_RDONLY         00
#define O_WRONLY         01
#define O_RDWR           02

int *get_file_contents(char *path)
{
  if (is_regular_file(path) == 0) {
    return 0;
  }

  size_t size_of_file = 0;
  size_t bytes_read;

  int successful = 0;

  struct stat buf;
  char *buffer, *pointer;

  FILE *fp = fopen(path, O_RDONLY);

  successful = stat(path, &buf);

  if (fp == NULL) {
    return 0;
  }

  size_of_file = buf.st_size;
  pointer = buffer = malloc(size_of_file); // Reserve storage block

  if (buffer == NULL) {
    return 0;
  }

  off_t chunk = 0;
  while (chunk < size_of_file) {
    bytes_read = fread(pointer, 1, size_of_file, fp);

    if (bytes_read < 0) {
      free(buffer);
      pclose(fp);

      return 0;
    }

    chunk += bytes_read;
  }

  free(buffer);
  pclose(fp);

  return (int *)1; //TODO
}

int *is_regular_file(char *path)
{
  int successful = 0;
  struct stat buf;

  successful = stat(path, &buf);

  // 0 = stat was successful.
  // -1 = stat was not successful;
  if (successful < 0) {
    return 0;
  }

  // S_IFREG    0100000   regular file.
  // st_mode : A bit string indicating the permissions and privileges of the file. 
  if (!(buf.st_mode & S_IFREG)) {
    return 0;
  }

  return (int *)1;
}

int *is_symbolic_link(char *path)
{
  int successful = 0;
  struct stat buf;

  successful = stat(path, &buf);

  // 0 = stat was successful.
  // -1 = stat was not successful;
  if (successful < 0) {
    return 0;
  }

  // S_IFREG    0100000   regular file.
  // st_mode : A bit string indicating the permissions and privileges of the file. 
  if (!(buf.st_mode & S_IFLNK)) {
    return 0;
  }

  return (int *)1;
}

int *is_block_device(char *path)
{
  int successful = 0;
  struct stat buf;

  successful = stat(path, &buf);

  // 0 = stat was successful.
  // -1 = stat was not successful;
  if (successful < 0) {
    return 0;
  }

  // S_IFCHR    0020000   character device
  // st_mode : A bit string indicating the permissions and privileges of the file. 
  if (!(buf.st_mode & S_IFCHR)) {
    return 0;
  }

  return  (int *)1;
}

int *is_directory(char *path)
{
  int successful = 0;
  struct stat buf;

  successful = stat(path, &buf);

  // 0 = stat was successful.
  // -1 = stat was not successful;
  if (successful < 0) {
    return 0;
  }

  // S_IFDIR    0040000   directory
  // st_mode : A bit string indicating the permissions and privileges of the file. 
  if (!(buf.st_mode & S_IFDIR)) {
    return 0;
  }

  return  (int *)1;
}

int *is_fifo(char *path)
{
  int successful = 0;
  struct stat buf;

  successful = stat(path, &buf);

  // 0 = stat was successful.
  // -1 = stat was not successful;
  if (successful < 0) {
    return 0;
  }

  // S_IFIFO    0010000   FIFO
  // st_mode : A bit string indicating the permissions and privileges of the file. 
  if (!(buf.st_mode & S_IFIFO)) {
    return 0;
  }

  return (int *)1;
}
