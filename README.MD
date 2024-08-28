# ft_ls

## Mandatory part

- [ ]  Your program must be written in **C.**
- [ ]  Name of the program **ft_ls.**
- [ ]  Allowed functions: write, opendir, readdir, closedir, stat, lstat, getpwuid, getgrgid, listxattr, time, ctime, readlink, malloc, free, perror, strerror, exit.

## Man ls

ls — list directory contents.

The following options are needed:

- [x]  -l: List in long format. A total sum for all the file sizes is output on a line before the long listing. The following information is displayed for each file: file mode, number of links, owner name, group name, number of bytes in the file, abbreviated month, day-of-month file was last modified, hour file last modified, minute file last modified, and the pathname.
- [x]  -R: Recursively list subdirectories encountered. When a symbolic link to a directory is encountered, the directory shall not be recursively listed
- [x]  -a: Include directory entries whose names begin with a dot (.).
- [x]  -r: Reverse the order of the sort to get reverse lexicographical order or the oldest entries first (or largest files last, if combined with sort by size).
- [x]  -t: Sort by time modified (most recently modified first) before sorting the operands by lexicographical order.

## Allowed functions

- write
    
    Data is written to an open file with the write function.
    
    ```c
    #include <unistd.h>
    
    ssize_t write(int fd, const void *buf, size_t nbytes);
    	Returns: number of bytes written if OK, -1 on error.
    ```
    
- opendir
    
    ```c
    #include <dirent.h>
    
    DIR *opendir(const char *pathname);
    
    		Returns: pointer if OK, NULL on error.
    ```
    
- readdir
    
    ```c
    #include <dirent.h>
    
    struct dirent *readdir(DIR *dp);
    
    		Returns: pointer if OK, NULL at the end of the directory on error.
    ```
    
- closedir
    
    ```c
    #include <dirent.h>
    
    int closedir(DIR *dp);
    
    		Returns: 0 if OK, -1 on error.
    ```
    
- stat
    
    ```c
    #include <sys/stat.h>
    
    int stat(const char *restrict pathname, struct stat *restrict buf);
    	
    		Both return: 0 if OK, -1 on error.
    ```
    
    Given a pathname, the **stat** **function returns a structure of information about the named file.
    
- lstat
    
    ```c
    #include <sys/stat.h>
    
    int lstat(const char *restrict pathname, struct stat *restrict buf);
    
    		return: 0 if OK, -1 on error.
    ```
    
    The **lstat** function is similar to **stat**, but when the named file is a symbolik link, **lstat** returns information about the symbolic link, not the file referenced by the symbolic link.
    
- getpwuid
    
    ```c
    #include <pwd.h>
    
    struct passwd *getpwuid(uid_t uid);
    
    		return: pointer if OK, NULL on error.
    ```
    
    The getpwuid function is used by the *ls(1)* program to map the numerical user ID contained in an i-node intro a user’s login name.
    
    It’s important to remember that if getpwuid returns `NULL`, it generally means that there is no entry for the given `uid` in the password database (`/etc/passwd`), not that there is necessarily an error in the function call itself. In order to handle when getpwuid returns null we can just print the UID instead of the usernam.
    
- getgrgid
    
    We can look up either a group name or a numerical group ID with the following two functions, which are defined by POSIX.1.
    
    ```c
    #include <grp.h>
    
    struct group *getgrgid(gid_t gid);
    
    		Both return: pointer if OK, NULL on error.
    ```
    
    Like the password file functions, both of these functions normally return pointers to a *static* variable, which is overwritten on each call.
    
- listxattr
- getxattr
- time
- ctime
- readlink
    
    Because the open function follows a symbolic link, we need a way to open the link itself and read the name in the link. 
    
    ```c
    #include <unistd.h>
    
    ssize_t readlink(const char *restrict pathname,
    										char *restrict buf, size_t buf_size);
    										
    		return: number of bytes read if OK, -1 on error.
    ```
    
    These functions combine the actions of open, read and close. If successful, they return the number of bytes placed into buf. The contents of the symbolic link that returned in buf are **not** null terminated.
    
- malloc
- free
- perror
- strerror
- exit

## Output

```bash
user:~/Desktop$ ls -l
total 4 
-rw-r--r-- 1 root root 5 Jun 17 12:32 hola.txt
```

**Total**: show total size of the folder

**File type**:

- “l” : It is a symbolic link to another file or directory.
- “d”: It is a directory.
- “-”: It is a regular file.
- “b”: It is a block device.
- “c”: It is a character special file.

**Owner**: This field tells us who is the creator of the file.

**Group**: This fields provides info about the group.

**1**: Indicates the number of hard links to the file.

**File size**: This is the file size in bytes.

**Time**: Date and time of last modification.

## Bonus part

### Management of ACL and Extended Attributes

### Management of Columns without the Option -l

Normally, `ls` arranges the output in columns if `-l` is not specified. This requires determining the optimal number of columns based on the terminal width.

- **Terminal Width**: Use `ioctl()` with `TIOCGWINSZ` to get the terminal width.
- **Column Calculation**: Calculate how many files can fit in one row and arrange them accordingly.

### Management of Options -u, -f, -g, -d, …

- [ ]  **u**: Sort by and display the file's last access time instead of the modification time. You can use `stat()` to get `st_atime` for this.
- [x]  **f**: Do not sort, enable `a` (show all files including hidden files). This disables sorting completely.
- [x]  **g**: Similar to `l` but do not list the owner. You'll need to modify the long listing format to skip the user ID. Turn on the **-l** (ell) option.
- [x]  **d**: List directories themselves, not their contents. This changes how you handle directories, listing them as regular files.

### Management of Views in Colors (Similar to Option -G)

Displaying different file types in different colors helps users quickly distinguish file types.

- **Color Codes**: Use ANSI escape codes to color different types of files.
- **File Types**: Determine file types using `stat()` or `lstat()`.

Example color scheme:

- Directories: Blue
- Executable files: Green
- Symbolic links: Cyan
- Regular files: Default color

Example implementation in C:

```c
cCopy code
if (S_ISDIR(statbuf.st_mode)) {
    printf("\033[1;34m%s\033[0m\n", filename); // Blue
} else if (statbuf.st_mode & S_IXUSR) {
    printf("\033[1;32m%s\033[0m\n", filename); // Green
} else if (S_ISLNK(statbuf.st_mode)) {
    printf("\033[1;36m%s\033[0m\n", filename); // Cyan
} else {
    printf("%s\n", filename); // Default
}

```

## Notes

- When you use the `ls` command with a list of files and directories as arguments, the behavior of `ls` is to first list the non-directory files specified in the arguments, followed by each directory and its contents. The sorting and display behavior is as follows:
    1. **Directories are listed with their contents**: After listing the specified files, `ls` then lists each specified directory and its contents. Each directory's name is followed by a colon, and then the contents of the directory are listed.
    2. **Files are listed first**: If you specify individual files and directories as arguments, `ls` will list the files first in lexicographical order.
    3. Notice that the flag **-d** changes this behaviour. If this flag is set they are all treated as files and it’s sorted.
- Normally ls, by default, uses the LC_COLLATE to sort, using strcoll. So in order to match the lexicographical sorting we should export the variable, otherwise ls command might use other ways to sort:
    
    ```bash
    export LC_ALL=C
    ```
    

## Links

https://www.cyberciti.biz/faq/linux-ls-command-sort-by-file-size/

https://pubs.opengroup.org/onlinepubs/009604499/utilities/ls.html
