/*----------------------------------------------------------------------------
 * File:  FS_bridge.c
 *
 * Description:
 * Methods for bridging to an external entity.
 *
 * External Entity:  File_System (FS)
 * 
 * Copyright 2017 John Törnblom
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *--------------------------------------------------------------------------*/

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#include "FS_bridge.h"


/*
 * Bridge:  Open
 */
i_t
FS_Open( c_t p_filename[ESCHER_SYS_MAX_STRING_LEN], const mc_stdlib_testing_File_Mode_t p_mode )
{
  int flags = 0;
  int mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

  switch(p_mode) {
  case mc_stdlib_testing_File_Mode_Read_e:
    flags = O_RDONLY;
    break;
  case mc_stdlib_testing_File_Mode_Write_e:
    flags = O_CREAT | O_WRONLY | O_TRUNC;
    break;
  case mc_stdlib_testing_File_Mode_Append_e:
    flags = O_CREAT | O_WRONLY | O_APPEND;
    break;
  default:
    flags = O_CREAT | O_RDWR | O_TRUNC;
  }

  return open(p_filename, flags, mode);
}


/*
 * Bridge:  Close
 */
bool
FS_Close( const i_t p_fd )
{
  return close(p_fd) == 0;
}


/*
 * Bridge:  Read
 */
c_t *
FS_Read( c_t A0xtumlsret[ESCHER_SYS_MAX_STRING_LEN], const i_t p_fd, const i_t p_length )
{
  int length = p_length;

  if(p_length > ESCHER_SYS_MAX_STRING_LEN-1 || p_length <= 0) {
    length = ESCHER_SYS_MAX_STRING_LEN-1;
  }

  if((length = read(p_fd, A0xtumlsret, length)) < 0) {
    length = 0;
  }
 
  A0xtumlsret[length] = '\0';

  return A0xtumlsret;
}


/*
 * Bridge:  Read_Line
 */
c_t *
FS_Read_Line( c_t A0xtumlsret[ESCHER_SYS_MAX_STRING_LEN], const i_t p_fd )
{
  A0xtumlsret[0] = '\0';
  for(size_t i=0; i<ESCHER_SYS_MAX_STRING_LEN; ++i) {
    if(read(p_fd, &A0xtumlsret[i], 1) != 1) {
      A0xtumlsret[i] = '\0';
      break;
    }

    if(A0xtumlsret[i] == '\n') {
      A0xtumlsret[i] = '\0';
      break;
    }
  }

  return A0xtumlsret;
}


/*
 * Bridge:  Write
 */
bool
FS_Write( const i_t p_fd, c_t p_str[ESCHER_SYS_MAX_STRING_LEN] )
{
  size_t length = strlen(p_str);
  return write(p_fd, p_str, length) == length;
}


/*
 * Bridge:  Write_Line
 */
bool
FS_Write_Line( const i_t p_fd, c_t p_str[ESCHER_SYS_MAX_STRING_LEN] )
{
  size_t length = strlen(p_str);
  if(write(p_fd, p_str, length) != length) {
    return false;
  }

  return write(p_fd, "\n", 1) == 1;
}


/*
 * Bridge:  Remove
 */
bool
FS_Remove( c_t p_filename[ESCHER_SYS_MAX_STRING_LEN] )
{
  return remove(p_filename) == 0;
}


/*
 * Bridge:  Exists
 */
bool
FS_Exists( c_t p_filename[ESCHER_SYS_MAX_STRING_LEN] )
{
  return !!realpath(p_filename, NULL);
}


/*
 * Bridge:  Mk_Temp
 */
c_t *
FS_Mk_Temp( c_t A0xtumlsret[ESCHER_SYS_MAX_STRING_LEN], c_t prefix[ESCHER_SYS_MAX_STRING_LEN], c_t suffix[ESCHER_SYS_MAX_STRING_LEN] )
{
  int fd;
  char const *tempdir = getenv("TMPDIR");
  if(!tempdir) {
	  tempdir = "/tmp";
  }

  snprintf(A0xtumlsret, ESCHER_SYS_MAX_STRING_LEN, "%s/%sXXXXXX%s", tempdir, prefix, suffix);
  if((fd = mkstemp(A0xtumlsret)) < 0) {
	  A0xtumlsret[0] = '\0';
	  return A0xtumlsret;
  }

  close(fd);

  return A0xtumlsret;
}

