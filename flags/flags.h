#ifndef FLAGS_H
#define FLAGS_H

// Define bitmask flags for options
#define A_FLAG                                                                 \
  0x1 // List all entries except for '.' and '..' Always set for superuser -
      // DONE

#define a_FLAG                                                                 \
  0x2 // include directories entries whose name begins with a dot - DONE
#define c_FLAG                                                                 \
  0x4 // Use time when file status was last changed, instead of time of last
      // modification of the file for sorting ( −t ) or printing ( −l ) .
#define d_FLAG                                                                 \
  0x8 // Directories are listed as plain files (not searched recursively) and
      // symbolic links in the argument list are not indirected through.
#define F_FLAG                                                                 \
  0x10 // Display a slash ( ‘/’ ) immediately after each pathname that is a
       // directory, an asterisk ( ‘∗’) after each that is executable, an at
       // sign ( ‘@’ ) after each symbolic link, a percent sign ( ‘%’ ) after
       // each whiteout, an equal sign ( ‘=’ ) after each socket, and a vertical
       // bar ( ‘|’ ) after each that is a FIFO.
#define f_FLAG 0x20 // Output is not sorted
#define h_FLAG                                                                 \
  0x40 // Modifies the −s and −l options, causing the sizes to be reported in
       // bytes displayed in a human readable format. Overrides −k.
#define i_FLAG                                                                 \
  0x80 // For each file, print the file’s file serial number (inode number).
#define k_FLAG                                                                 \
  0x100 // Modifies the −s option, causing the sizes to be reported in
        // kilobytes. The rightmost of the −k and −h flags overrides the
        // previous flag. See also −h.
#define l_FLAG 0x200 // List in long format
#define n_FLAG                                                                 \
  0x400 // The same as −l, except that the owner and group IDs are displayed
        // numerically rather than converting to a owner or group name.
#define o_FLAG 0x80000
// for checking the archive status of the file
#define q_FLAG                                                                 \
  0x800 // Force printing of non-printable characters in file names as the
        // character ‘?’; this is the default when output is to a terminal.
#define R_FLAG 0x1000 // Recursively list subdirectories encountered
#define r_FLAG                                                                 \
  0x2000 // Reverse the order of the sort to get reverse lexicographical order
         // or the smallest or oldest entries first.
#define S_FLAG 0x4000 // Sort by size, largest file first
#define s_FLAG                                                                 \
  0x8000 // Display the number of file system blocks actually used by each file,
         // in units of 512 bytes or BLOCKSIZE
#define t_FLAG                                                                 \
  0x10000 // Sort by time modified (most recently modified first) before sorting
          // the operands by lexicographical order
#define u_FLAG                                                                 \
  0x20000 // Use time of last access, instead of last modification of the file
          // for sorting ( −t ) or printing ( −l ) .
#define w_FLAG                                                                 \
  0x40000 // w Force raw printing of non-printable characters. This is the
          // default when output is not to a terminal.

#endif
