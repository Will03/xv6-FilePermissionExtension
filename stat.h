#define T_DIR  1   // Directory
#define T_FILE 2   // File
#define T_DEV  3   // Device

#define P_read 1
#define P_write 2
#define P_execute 3

struct stat {
  short type;  // Type of file
  int dev;     // File system's disk device
  uint ino;    // Inode number
  short nlink; // Number of links to file
  uint size;   // Size of file in bytes
  uint premission;
  uint ownerid;
  uint groupid;
};
