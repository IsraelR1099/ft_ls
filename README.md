# ft_ls

## Mandatory part

- [ ]  Your program must be written in **C.**
- [ ]  Name of the program **ft_ls.**
- [ ]  Allowed functions: write, opendir, readdir, closedir, stat, lstat, getpwuid, getgrgid, listxattr, time, ctime, readlink, malloc, free, perror, strerror, exit.

## Man ls

ls — list directory contents.

The following options are needed:

- -l: List in long format. A total sum for all the file sizes is output on a line before the long listing. The following information is displayed for each file: file mode, number of links, owner name, group name, number of bytes in the file, abbreviated month, day-of-month file was last modified, hour file last modified, minute file last modified, and the pathname.
- -R: Recursively list subdirectories encountered.
- -a: Include directory entries whose names begin with a dot (.).
- -r: Reverse the order of the sort to get reverse lexicographical order or the oldest entries first (or largest files last, if combined with sort by size).
- -t: Sort by time modified (most recently modified first) before sorting the operands by lexicographical order.

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

## Links

https://www.cyberciti.biz/faq/linux-ls-command-sort-by-file-size/