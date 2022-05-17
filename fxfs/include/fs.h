#ifndef FXFS_FS_H
#define FXFS_FS_H

#define FUSE_USE_VERSION 30

#include <fuse.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

#define BLOCKSIZE 1024


typedef struct superblock
{
	char datablocks[BLOCKSIZE * 100]; // total number of data blocks
	char data_bitmap[105];			   // array of data block numbers that are available
	char inode_bitmap[105];			   // array of inode numbers that are available
} superblock;

typedef superblock *lpsuperblock;
int *p;

typedef struct inode
{
	int datablocks[16]; // data block number that the inode points to
	int number;
	int blocks; //==number of blocks the particular inode points to
	// int link;                    //==number of links
	int size; //==size of file/directory
} inode;

typedef struct filetype
{
	int valid;
	char test[10];
	char path[100];
	char name[100];				// name
	inode *inum;				// inode number
	struct filetype **children; //??
	int num_children;
	int num_links;
	struct filetype *parent; //?
	char type[20];			 //==file extension
	mode_t permissions;		 // Permissions
	uid_t user_id;			 // userid
	gid_t group_id;			 // groupid
	time_t a_time;			 // Access time
	time_t m_time;			 // Modified time
	time_t c_time;			 // Status change time
	time_t b_time;			 // Creation time
	off_t size;				 // Size of the node

	int datablocks[16];
	int number;
	int blocks;

} filetype;


typedef struct fxfs_context {
	superblock* superblock;
	filetype*   root;
	filetype*   file_array;
} fxfs_context;

// superblock spblock;
// filetype * root;
// filetype file_array[50];

//initialize superblock
void initialize_superblock();

// transfer tree to array structure
void tree_to_array(filetype *, int *, int *, int *);

//save 
void save_contents();

//initialize root
void initialize_root_directory();

//input the path and return the corrent node's filetype
filetype *filetype_from_path(char *);

//find a free inode location in superblock and return the location
int find_free_inode();

//find a free data location in superblock and return the location
int find_free_db();

//input the parent node and the children node to add the children to the parent
void add_child(filetype *, filetype *);

// FUSE operations
//mkdir input the path and mode return success or fail
int mymkdir(const char *, mode_t);

//mkdir input the path and mode return success or fail
int myreaddir(const char *, void *, fuse_fill_dir_t, off_t, struct fuse_file_info *);

//Get file attributes.input path and struct stat to save info
int mygetattr(const char *, struct stat *);

//Remove a directory.input the path
int myrmdir(const char *);

//rm a file .input the path
int myrm(const char *);

//Create and open a file. input path 
int mycreate(const char *, mode_t, struct fuse_file_info *);

//Open a file
int myopen(const char *, struct fuse_file_info *);

//Read data from an open file，inputs are: path ,buf,size,offsize,fuse file struct pointer
int myread(const char *, char *, size_t, off_t, struct fuse_file_info *);

// Check file access permissions,inputs are: path and mask
int myaccess(const char *, int);

//Rename a file.input the oldname and the new one.
int myrename(const char *, const char *);

// Change the size of a file, input the path and the size.On success, zero is returned.
int mytruncate(const char *, off_t);

//Write data to an open file, inputs are: path ,buf,size,offsize,fuse file struct pointer
int mywrite(const char *, const char *, size_t, off_t, struct fuse_file_info *);


fxfs_context* fxfs_get_context();

// 
void          fxfs_init_context();

#endif