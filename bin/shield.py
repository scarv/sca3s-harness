#!/usr/bin/python3

# Copyright (C) 2019 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which
# can be found at https://opensource.org/licenses/MIT (or should be included
# as LICENSE.txt within the associated archive or repository).

import json, os, re, shutil, subprocess, urllib.parse

if ( __name__ == '__main__' ) :
  repo_url    = subprocess.check_output( [ 'git', 'config', '--get', 'remote.origin.url' ] ).decode().strip()
  repo_branch = subprocess.check_output( [ 'git', 'rev-parse', '--abbrev-ref', 'HEAD'    ] ).decode().strip()
  
  repo_url    = re.match( '/?(?P<repo_owner>[-\w]+)/?(?P<repo_name>[-\w]+)(.git)?', urllib.parse.urlparse( repo_url ).path )

  if ( repo_url == None ) :
    exit( 0 )

  repo =  { 'repo_branch' : repo_branch, 'repo_owner' : repo_url.group( 'repo_owner' ),
                                         'repo_name'  : repo_url.group( 'repo_name'  ) }
  
  if ( not os.path.isfile( 'README.md' ) ) :
    exit( 0 )
  
  fd_readme_old = open(       'README.md', 'r' )
  fd_readme_new = open( 'build/README.md', 'w' )

  marker_flag = False  
  marker_line = '<!--- SCA3S shields -->'
  
  for line in fd_readme_old.readlines() :
    line = line.rstrip( '\n' )
  
    if   ( ( marker_flag == False ) and ( line != marker_line ) ) :
      print( line, file = fd_readme_new )
  
    elif ( ( marker_flag == False ) and ( line == marker_line ) ) :
      marker_flag =  True
    elif ( ( marker_flag == True  ) and ( line == marker_line ) ) :
      marker_flag = False
  
      def shield( x ) :
        print( x.format( **repo ), file = fd_readme_new )
  
      print( marker_line, file = fd_readme_new )
      shield( '[![SCA3S acquire data](https://lab.scarv.org/api/shields/acquisition/{repo_owner}/{repo_name}.svg?branch={repo_branch})](...)' )
      shield( '[![SCA3S analyse data](https://lab.scarv.org/api/shields/analysis/{repo_owner}/{repo_name}.svg?branch={repo_branch})](...)' )
      print( marker_line, file = fd_readme_new )
  
  fd_readme_old.close()
  fd_readme_new.close()
  
  shutil.move( 'build/README.md', 'README.md' )
